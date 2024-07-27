#include "Player.hpp"
#include "PlayerExceptions.hpp"

#include "Armor.hpp"

const char* PlayerExceptions::_msg = "";
std::vector<Player*> Player::players = {};

Player::Player(const char* plrName, int health, std::unordered_map<std::string, int> weapons, Armor armor) :
    plrName(plrName),
    health(health > 0 ? health : throw std::invalid_argument("Health must be greater than 0")),
    weapons(weapons),
    currentArmor(armor),
    isWearingArmor(!(armor == Armor("", 0, 1, 0))) 

{
    for (const auto& weapon : weapons) {
        std::cout << "Created class Player with the attributes: " << this->plrName << ", " << this->health << ", "
            << weapon.first << " : " << weapon.second << std::endl;
    }
    players.push_back(this);
}

void Player::removePlayer(Player* player) {
    auto it = std::remove(players.begin(), players.end(), player);
    if (it != players.end()) {
        players.erase(it, players.end());
    }
}

void Player::getStats() const {
    std::cout << "----GETTING STATS FOR " << this->plrName << "----" << std::endl;
    std::cout << "Name: " << this->plrName << ", Health: " << this->health << ", Weapons:\n\n";
    for (std::pair<std::string, int> pair : this->weapons) {
        std::cout << pair.first << " : " << pair.second << std::endl;
    }
    std::cout << "\nTotal weapons count: " << this->weapons.size() << std::endl;
    std::cout << "----STATS END----" << std::endl;
}

size_t Player::getTotalPlayers() {
    return players.size();
}

void Player::updateWeapons(const char* type, std::pair<std::string, int> &value) {
    std::string first = value.first;
    int second = value.second;
    if (type == "add") {
        this->weapons.insert(value);
        std::cout << "Added \"" << first << "\" to weapons with damage " << second << " to the player " << this->plrName << std::endl;
    } else if (type == "remove") {
        if (this->weapons.find(first) != weapons.end()) {
            this->weapons.erase(first);
            std::cout << "Removed \"" << first << "\" from weapons from the player " << this->plrName << std::endl;
        }
        else {
            std::stringstream eMessage;
            eMessage << "There is no \"" << first << "\" to remove from the weapons";
            throw PlayerExceptions::weapon_not_found(eMessage.str().c_str());
        }
    } else {
        throw std::invalid_argument("Invalid type, type can only be 'add' or 'remove'");
    }
}

double crit(int &weaponDmg, int &armorResistance) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(1, 4);

    int random_number = distr(gen);
    double damage = 0;
    if (random_number == 1) {
        damage = (weaponDmg / armorResistance) * 1.5;
    } else {
        damage = weaponDmg / armorResistance;
    }
    return damage;
}

void Player::attack(Player& target, std::string weaponName) {
    if (target.health > 0) {
        auto it = this->weapons.find(weaponName);
        if (it != this->weapons.end()) {
            int weaponDmg = it->second;
            if (weaponDmg > 0) {
                int armorResistance = target.currentArmor.getResistance();
                double damage = crit(weaponDmg, armorResistance);
                target.health -= static_cast<int>(damage);
                if (target.health < 0) {
                    target.health = 0;
                }
                std::cout << "Dealt " << weaponDmg << " damage to " << target.plrName << " using \"" << weaponName << "\"" << std::endl;
                if (target.health == 0) {
                    std::cout << target.plrName << " is defeated by " << this->plrName << " using \"" << weaponName << "\"" << std::endl;
                    removePlayer(&target); // Remove the defeated player
                }
                std::cout << "New health of " << target.plrName << ": " << target.health << std::endl;
            }
            else {
                std::cerr << "Weapon: \"" << weaponName << "\" has negative damage" << std::endl;
            }
        }
        else {
            std::cerr << "Weapon \"" << weaponName << "\" not found in weapons" << std::endl;
        }
    }
    else {
        std::cout << target.plrName << " is already defeated and cannot be attacked" << std::endl;
    }
}


void Player::heal(Player& target, int &amount) {
    std::string name = target.plrName;
    int health = target.health;
    if (amount > 0) {
        health += amount;
        std::cout << name << " healed by: " << amount << std::endl;
        std::cout << "New health of " << name << ": " << health << std::endl;
    } else {
        throw std::invalid_argument("Amount cannot be negative");
    }
}

void Player::equipArmor(Armor &armor) {
    if (!isWearingArmor) {
        this->currentArmor = armor;
        this->isWearingArmor = true;
    } else {
        std::cout << this->plrName << " is already wearing armor" << std::endl;
    }
}

Player* Player::getWinner() {
    if (players.size() == 1) {
        return players[0];
    }
    return nullptr;
}

Player Player::operator+(const Player &other) const {
    std::string newName = std::string(this->plrName) + ":" + other.plrName;
    int newHealth = this->health + other.health;
    std::unordered_map<std::string, int> newWeapons = this->weapons;
    Armor newArmor = this->currentArmor + other.currentArmor;
    for (const auto& pair : other.weapons) {
        newWeapons[pair.first] = pair.second;
    }
    return Player(newName.c_str(), newHealth, newWeapons, newArmor);
}

Player::~Player() {
    removePlayer(this); // Ensure player is removed from the list upon destruction
}