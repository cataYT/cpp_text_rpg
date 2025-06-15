#include <sstream>
#include <random>
#include <optional>
#include <functional>
#include <algorithm>
#include <iostream>
#include "Armor.hpp"
#include "Weapon.hpp"
#include "Player.hpp"
#include "PlayerExceptions.hpp"

std::vector<std::reference_wrapper<const Player>> Player::players;
std::string PlayerExceptions::_msg = "";

Player::Player(const std::string& plrName, const uint32_t health, const std::vector<Weapon>& weapons, const Armor& armor)
    : weapons(weapons),
    isWearingArmor(!(armor == Armor("", 0, 1, 0))),
    plrName(plrName),
    health(health),
    currentArmor(armor)
{
    for (const Weapon& weapon : weapons) {
        std::cout << "Created class Player with the attributes: " << this->plrName
            << ", " << this->health << ", "
            << weapon.getName() << " : " << weapon.getDamage() << std::endl;
    }
    players.emplace_back(std::cref(*this));
}

void Player::removePlayer(const Player& player)
{
    std::erase_if(players, [&](const std::reference_wrapper<const Player>& ref) {
        return &ref.get() == &player;
    });
}

std::vector<Weapon> Player::getWeapons() const
{
    return this->weapons;
}

inline void Player::getStats() const
{
    std::cout << "----GETTING STATS FOR " << this->plrName << "----" << std::endl;
    std::cout << "Name: " << this->plrName << ", Health: " << this->health << ", Weapons:\n\n";
    for (const Weapon& weapon : this->weapons) {
        std::cout << weapon.getName() << " : " << weapon.getDamage() << std::endl;
    }
    std::cout << "\nTotal weapons count: " << this->weapons.size() << std::endl;
    std::cout << "----STATS END----" << std::endl;
}

inline size_t Player::getTotalPlayers()
{
    return players.size();
}

void Player::updateWeapons(const std::string_view& type, const Weapon& weapon)
{
    const std::string w_name = weapon.getName();
    const uint32_t w_dmg = weapon.getDamage();

    if (type == "add") {
        this->weapons.emplace_back(weapon);
        std::cout << "Added \"" << w_name << "\" to weapons with damage " << w_dmg
            << " to the player " << this->plrName << std::endl;
    } else if (type == "remove") {
        auto it = std::find(this->weapons.begin(), this->weapons.end(), weapon);
        if (it != this->weapons.end()) {
            this->weapons.erase(it);
            std::cout << "Removed \"" << w_name << "\" from weapons from the player " << this->plrName << std::endl;
        } else {
            std::stringstream eMessage;
            eMessage << "There is no \"" << w_name << "\" to remove from the weapons";
            throw PlayerExceptions::weapon_not_found(eMessage.str());
        }
    } else {
        throw std::invalid_argument("Invalid type, type can only be 'add' or 'remove'");
    }
}

static double crit(const int weaponDmg, const int armorResistance)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution distr(1, 4);

    const int random_number = distr(gen);
    double damage = (random_number == 1) ? (weaponDmg / static_cast<double>(armorResistance)) * 1.5
        : weaponDmg / static_cast<double>(armorResistance);

    return damage;
}

void Player::attack(Player& target, const std::string& weaponName)
{
    if (target.health <= 0) {
        std::cout << target.plrName << " is already defeated and cannot be attacked.\n";
        return;
    }

    auto it = std::find_if(this->weapons.begin(), this->weapons.end(), [&](const Weapon& w) {
        return w.getName() == weaponName;
        });

    if (it == this->weapons.end()) {
        std::cerr << "Weapon \"" << weaponName << "\" not found in weapons.\n";
        return;
    }

    Weapon& weapon = *it;
    const int weaponDmg = weapon.getDamage();

    if (weaponDmg <= 0) {
        std::cerr << "Weapon \"" << weaponName << "\" has non-positive damage.\n";
        return;
    }

    const int armorResistance = target.currentArmor.getResistance();
    const double damage = crit(weaponDmg, armorResistance);
    const auto intDamage = static_cast<uint32_t>(damage);

    target.health = (target.health > intDamage) ? target.health - intDamage : 0;

    weapon.useWeapon(intDamage / 10); // Reduce weapon durability

    std::cout << this->plrName << " attacks " << target.plrName
        << " with \"" << weaponName << "\", dealing "
        << intDamage << " damage.\n";

    if (target.health == 0) {
        std::cout << target.plrName << " is defeated by "
            << this->plrName << " using \"" << weaponName << "\".\n";
        removePlayer(target);
    }

    std::cout << target.plrName << "'s new health: " << target.health << "\n";
}

void Player::heal(Player& target, const int amount) const
{
    if (amount <= 0) {
        throw std::invalid_argument("Amount must be positive");
    }

    target.health += amount;
    std::cout << target.plrName << " healed by: " << amount << std::endl;
    std::cout << "New health of " << target.plrName << ": " << target.health << std::endl;
}

void Player::equipArmor(const Armor& armor)
{
    if (!isWearingArmor) {
        this->currentArmor = armor;
        this->isWearingArmor = true;
    }
    else {
        std::cout << this->plrName << " is already wearing armor" << std::endl;
    }
}

// ✅ Fixed return type for better optional handling
std::optional<std::reference_wrapper<const Player>> Player::getWinner() 
{
    return (players.size() == 1) ? std::make_optional(players[0]) : std::nullopt;
}

Player operator+(const Player& lhs, const Player& rhs)
{
    const std::string newNameStr = lhs.plrName + ":" + rhs.plrName;
    const int newHealth = lhs.health + rhs.health;

    std::vector<Weapon> newWeapons = lhs.getWeapons();
    for (const Weapon& w : rhs.getWeapons()) {
        newWeapons.emplace_back(w);
    }

    const Armor newArmor = lhs.currentArmor + rhs.currentArmor;

    return Player(newNameStr, newHealth, newWeapons, newArmor);
}

Player::~Player()
{
    removePlayer(*this); // Ensure player is removed from the list upon destruction
}