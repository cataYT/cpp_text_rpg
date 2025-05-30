#include "Player.hpp"
#include "PlayerExceptions.hpp"

std::string PlayerExceptions::_msg = "";
std::vector<Player*> Player::players = {};

Player::Player(std::string const& plrName, uint32_t health, std::vector<Weapon> const& weapons, Armor const& armor) :
    weapons(weapons),
    isWearingArmor(!(armor == Armor("", 0, 1, 0))),
    plrName(plrName),
    health(health),
    currentArmor(armor)
{
    for (Weapon weapon : weapons)
    {
        std::cout << "Created class Player with the attributes: " << this->plrName << ", " << this->health << ", "
            << weapon.getName() << " : " << weapon.getDamage() << std::endl;
    }
    players.emplace_back(this);
}

void Player::removePlayer(Player* player) 
{
    auto it = std::remove(players.begin(), players.end(), player);
    if (it != players.end()) 
    {
        players.erase(it, players.end());
    }
}

std::vector<Weapon> Player::getWeapons() const
{
    return this->weapons;
}

inline void Player::getStats() const
{
    std::cout << "----GETTING STATS FOR " << this->plrName << "----" << std::endl;
    std::cout << "Name: " << this->plrName << ", Health: " << this->health << ", Weapons:\n\n";
    for (Weapon weapon : this->weapons) 
    {
        std::cout << weapon.getName() << " : " << weapon.getDamage() << std::endl;
    }
    std::cout << "\nTotal weapons count: " << this->weapons.size() << std::endl;
    std::cout << "----STATS END----" << std::endl;
}

inline size_t Player::getTotalPlayers()
{
    return players.size();
}

void Player::updateWeapons(std::string_view const& type, Weapon const& weapon)
{
	std::string w_name = weapon.getName();
	uint32_t w_dmg = weapon.getDamage();
    if (type == "add") 
    {
        this->weapons.emplace_back(weapon);
        std::cout << "Added \"" << weapon.getName() << "\" to weapons with damage " << w_dmg << " to the player " << this->plrName << std::endl;
    } 
    else if (type == "remove") 
    {
        auto it = std::find(this->weapons.begin(), this->weapons.end(), weapon);
        if (it != this->weapons.end())
        {
            this->weapons.erase(it);
            std::cout << "Removed \"" << w_name << "\" from weapons from the player " << this->plrName << std::endl;
        }
        else 
        {
            std::stringstream eMessage;
            eMessage << "There is no \"" << w_name << "\" to remove from the weapons";
            throw PlayerExceptions::weapon_not_found(eMessage.str());
        }
    } 
    else 
    {
        throw std::invalid_argument("Invalid type, type can only be 'add' or 'remove'");
    }
}

static double crit(int const& weaponDmg, int const& armorResistance)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution distr(1, 4);

    int random_number = distr(gen);
    double damage = 0;
    if (random_number == 1) 
    {
        damage = (weaponDmg / armorResistance) * 1.5;
    } 
    else 
    {
        damage = weaponDmg / armorResistance;
    }
    return damage;
}

void Player::attack(Player& target, const std::string& weaponName)
{
    if (target.health <= 0) 
    {
        std::cout << target.plrName << " is already defeated and cannot be attacked.\n";
        return;
    }

    // Find the weapon by name in the vector
    auto it = std::find_if(this->weapons.begin(), this->weapons.end(),
        [&](const Weapon& w) 
        {
            return w.getName() == weaponName;
        });

    if (it == this->weapons.end()) 
    {
        std::cerr << "Weapon \"" << weaponName << "\" not found in weapons.\n";
        return;
    }

    Weapon& weapon = *it;
    int weaponDmg = weapon.getDamage();

    if (weaponDmg <= 0) 
    {
        std::cerr << "Weapon \"" << weaponName << "\" has non-positive damage.\n";
        return;
    }

    int armorResistance = target.currentArmor.getResistance();
    double damage = crit(weaponDmg, armorResistance);
    auto intDamage = static_cast<uint32_t>(damage);

    target.health -= intDamage;
    target.health = 0;

    weapon.useWeapon(intDamage / 10); // Reduce weapon durability

    std::cout << this->plrName << " attacks " << target.plrName
        << " with \"" << weaponName << "\", dealing "
        << intDamage << " damage.\n";

    if (target.health == 0) 
    {
        std::cout << target.plrName << " is defeated by "
            << this->plrName << " using \"" << weaponName << "\".\n";
        removePlayer(&target);
    }

    std::cout << target.plrName << "'s new health: " << target.health << "\n";
}


void Player::heal(Player const& target, int const& amount) const
{
    std::string name = target.plrName;
    uint32_t hhealth = target.health;
    if (amount > 0) 
    {
        hhealth += amount;
        std::cout << name << " healed by: " << amount << std::endl;
        std::cout << "New health of " << name << ": " << hhealth << std::endl;
    } 
    else 
    {
        throw std::invalid_argument("Amount cannot be negative");
    }
}

void Player::equipArmor(Armor const& armor) 
{
    if (!isWearingArmor) 
    {
        this->currentArmor = armor;
        this->isWearingArmor = true;
    } 
    else 
    {
        std::cout << this->plrName << " is already wearing armor" << std::endl;
    }
}

Player* Player::getWinner()
{
    if (players.size() == 1) 
    {
        return players[0];
    }
    return nullptr;
}

Player operator+(const Player& lhs, const Player& rhs)
{
    std::string newNameStr = lhs.plrName + ":" + rhs.plrName;
    int newHealth = lhs.health + rhs.health;

    std::vector<Weapon> newWeapons = lhs.getWeapons();
    for (const Weapon& w : rhs.getWeapons())
    {
        newWeapons.emplace_back(w);
    }

    Armor newArmor = lhs.currentArmor + rhs.currentArmor;

    // Assumes Player constructor copies the name string
    return Player(newNameStr, newHealth, newWeapons, newArmor);
}

Player::~Player() 
{
    removePlayer(this); // Ensure player is removed from the list upon destruction
}