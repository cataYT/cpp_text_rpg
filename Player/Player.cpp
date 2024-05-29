#include "Player.hpp"
#include "PlayerExceptions.hpp"

#include <sstream>
#include <iostream>
#include <unordered_map>
#include <stdexcept>
#include <algorithm>


std::string PlayerExceptions::_msg = "";
std::vector<Player*> Player::players = {};

Player::Player(std::string plrName, int health, std::unordered_map<std::string, int> weapons) {
    this->plrName = plrName;
    if (health > 0) {
        this->health = health;
    } else {
        throw std::invalid_argument("Health must be greater than 0");
    }
    this->weapons = weapons;
    for (const std::pair<std::string, int> &weapon : weapons) {
        std::cout << "Created class Player with the attributes: " << plrName << ", " << health << ", " << weapon.first << " : " << weapon.second << std::endl;
    }
    players.push_back(this);
}

void Player::getStats() const {
    std::cout << "----GETTING STATS FOR " << plrName << "----" << std::endl;
    std::cout << "Name: " << plrName << ", Health: " << health << ", Weapons:\n\n";
    for (std::pair<std::string, int> pair : weapons) {
        std::cout << pair.first << " : " << pair.second << std::endl;
    }
    std::cout << "\nTotal weapons count: " << weapons.size() << std::endl;
    std::cout << "----STATS END----" << std::endl;
}

size_t Player::getTotalPlayers() {
    return players.size();
}

void Player::updateWeapons(std::string type, std::pair<std::string, int> value) {
    if (type == "add") {
        weapons.insert(value);
        std::cout << "Added \"" << value.first << "\" to weapons with damage " << value.second << " to the player " << plrName << std::endl;
    } else if (type == "remove") {
        if (weapons.find(value.first) != weapons.end()) {
            weapons.erase(value.first);
            std::cout << "Removed \"" << value.first << "\" from weapons from the player " << plrName << std::endl;
        }
        else {
            std::stringstream eMessage;
            eMessage << "There is no \"" << value.first << "\" to remove from the weapons";
            throw PlayerExceptions::weapon_not_found(eMessage.str());
        }
    } else {
        throw std::invalid_argument("Invalid type, type can only be 'add' or 'remove'");
    }
}

void Player::attack(Player& target, std::string weaponName) {
    if (target.health > 0) {
        std::unordered_map<std::string, int>::iterator it = weapons.find(weaponName);
        if (it != weapons.end()) {
            if (it->second > 0) {
                target.health -= it->second;
                std::cout << "Dealt " << it->second << " damage by " << plrName << " to " << target.plrName << " using \"" << weaponName << "\"" << std::endl;
                if (target.health < 0) {
                    int actualHealth = target.health;
                    target.health = 0;
                    std::cout << target.plrName << " is defeated by " << plrName << " using " << "\"" << weaponName << "\"" << std::endl;
                }
                std::cout << "New health of " << target.plrName << ": " << target.health << std::endl;
            } else {
                std::stringstream eMessage;
                eMessage << "Weapon: \"" << weaponName << "\" has negative damage";
                throw std::invalid_argument(eMessage.str());
            }
        } else {
            std::stringstream eMessage;
            eMessage << "Weapon \"" << weaponName << "\" not found in weapons";
            throw PlayerExceptions::weapon_not_found(eMessage.str());
        }
    } else {
        std::cout << target.plrName << " is already defeated and cannot be attacked" << std::endl;
    }
}

void Player::heal(Player& target, int amount) {
    if (amount > 0) {
        target.health += amount;
        std::cout << target.plrName << " healed by: " << amount << std::endl;
        std::cout << "New health of " << target.plrName << ": " << target.health << std::endl;
    } else {
        throw std::invalid_argument("Amount cannot be negative");
    }
}

Player* Player::checkWin() {
    if (players.size() == 1) {
        return players[0];
    } else {
        return nullptr;
    }
}

Player Player::operator+(const Player &other) const {
    std::string newName = this->plrName + ":" + other.plrName;
    int newHealth = this->health + other.health;
    std::unordered_map<std::string, int> newWeapons = this->weapons;
    for (const auto& pair : other.weapons) {
        newWeapons[pair.first] = pair.second;
    }
    return Player(newName, newHealth, newWeapons);
}

Player::~Player() {
    players.erase(std::remove(players.begin(), players.end(), this), players.end());
}