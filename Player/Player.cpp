#include <random>
#include <optional>
#include <algorithm>
#include <print>
#include "Armor.hpp"
#include "Weapon.hpp"
#include "Player.hpp"
#include "PlayerExceptions.hpp"

/// @brief Static vector to hold all players
std::vector<std::reference_wrapper<const Player>> Player::players;
/// @brief Static message for PlayerExceptions 
std::string PlayerExceptions::_msg = "";

Player::Player(const std::string& plrName, const uint32_t health, const std::vector<Weapon>& weapons, const Armor& armor)
    : weapons(weapons),
    isWearingArmor(!(armor == Armor("", 0, 1, 0))),
    plrName(plrName),
    health(health),
    currentArmor(armor)
{
    for (const Weapon& weapon : weapons) {
        std::println("Created class Player with the attributes: {}, {}, {} : {}", this->plrName, this->health, weapon.getName(), weapon.getDamage());
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
    std::println("----GETTING STATS FOR {}----", this->plrName);
    std::println("Name: {}, Health: {}, Weapons: \n", this->plrName, this->health);
    for (const Weapon& weapon : this->weapons) {
        std::println("{} : {}", weapon.getName(), weapon.getDamage());
    }
    std::println("\nTotal weapons count: {}", this->weapons.size());
    std::println("----STATS END----");
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
        std::println("Added \"{}\" to weapons with damage {} to the player {}", w_name, w_dmg, this->plrName);
    } else if (type == "remove") {
        auto it = std::find(this->weapons.begin(), this->weapons.end(), weapon);
        if (it != this->weapons.end()) {
            this->weapons.erase(it);
            std::println("Removed \"{}\" from weapons from the player {}", w_name, this->plrName);
        } else {
            std::string eMessage = std::format("There is no \"{}\" to remove from the weapons", w_name);
            throw PlayerExceptions::weapon_not_found(eMessage);
        }
    } else {
        throw std::invalid_argument("Invalid type, type can only be 'add' or 'remove'");
    }
}

/**
* @brief Calculates the critical hit damage based on weapon damage and armor resistance.
* 
* @param[in] weaponDmg:       The damage of the weapon being used.
* @param[in] armorResistance: The resistance of the target's armor.
* 
* @return The calculated damage, which may be increased by a critical hit factor.
*/
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
        std::println("{} is already defeated and cannot be attacked.", target.plrName);
        return;
    }

    auto it = std::find_if(this->weapons.begin(), this->weapons.end(), [&](const Weapon& w) {
        return w.getName() == weaponName;
    });

    if (it == this->weapons.end()) {
		throw PlayerExceptions::weapon_not_found("Weapon not found: " + weaponName);
    }

    Weapon& weapon = *it;
    const int weaponDmg = weapon.getDamage();

    if (weaponDmg <= 0) {
        std::println(std::cerr, "Weapon \"{}\" has non-positive damage.", weaponName);
        return;
    }

    const int armorResistance = target.currentArmor.getResistance();
    const double damage = crit(weaponDmg, armorResistance);
    const auto intDamage = static_cast<uint32_t>(damage);

    target.health = (target.health > intDamage) ? target.health - intDamage : 0;

    weapon.useWeapon(intDamage / 10); // Reduce weapon durability

    std::println("{} attacks {} with \"{}\" dealing {} damage", this->plrName, target.plrName, weaponName, intDamage);

    if (target.health == 0) {
        std::println("{} is defeated by {} using \"{}\".", target.plrName, this->plrName, weaponName);
        removePlayer(target);
    }

    std::println("{}'s new health: {}", target.plrName, target.health);
}

void Player::heal(Player& target, const int amount) const
{
    if (amount <= 0) {
        throw std::invalid_argument("Amount must be positive");
    }

    target.health += amount;
    std::println("{} healed by: {}", target.plrName, amount);
    std::println("New health of {}: {}", target.plrName, target.health);
}

void Player::equipArmor(const Armor& armor)
{
    if (!isWearingArmor) {
        this->currentArmor = armor;
        this->isWearingArmor = true;
    }
    else {
        std::println("{} is already wearing armor", this->plrName);
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