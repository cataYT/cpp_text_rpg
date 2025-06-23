#pragma once

#include <iostream>
#include <string>

/**
* @class Weapon
* @brief Represents a weapon with properties such as name, health, and damage.
*/
class Weapon
{
private:
	/// @brief Name of the weapon.
	std::string name;
	/// @brief Health of the weapon, representing its durability.
	uint32_t weapon_health = 0;
	/// @brief Damage of the weapon.
	uint32_t weapon_damage = 0;

public:
	/**
	* @brief Constructs a Weapon object with specified properties.
	* 
	* @param[in] name:          The name of the weapon.
	* @param[in] weapon_health: The health of the weapon, representing its durability.
	* @param[in] damage:        The damage of the weapon.
	* 
	* @return An instance of the Weapon class initialized.
	*/
	Weapon(const std::string& name, const uint32_t weapon_health, const uint32_t damage);
	/**
	* @brief Gets the name of the weapon.
	* 
	* @return The name of the weapon.
	*/
	std::string getName() const;
	/**
	* @brief Gets the health of the weapon.
	* 
	* @return The health of the weapon, representing its durability.
	*/
	uint32_t getHealth() const;
	/**
	* @brief Gets the damage of the weapon.
	* 
	* @return The damage of the weapon.
	*/
	uint32_t getDamage() const;
	/**
	* @brief Uses the weapon to inflict damage.
	* 
	* @param[in] damage: The amount of damage to inflict using the weapon.
	*/
	void useWeapon(uint32_t damage);
	/**
	* @brief Repairs the weapon.
	* 
	* @param[in] health: The amount of health to restore to the weapon.
	*/
	void repairWeapon(uint32_t health);
	/**
	* @brief Enhances the weapon's damage.
	* 
	* @param[in] damage: The amount of damage to enhance the weapon with.
	*/
	void enhanceWeapon(uint32_t damage);
	/**
	* @brief Comares two Weapon objects for inequality.
	* 
	* @param[in] other: The other Weapon object to compare with.
	* 
	* @return true if the two Weapon objects are equal, false otherwise.
	*/
	bool operator==(const Weapon& other) const = default;
	/**
	* @brief Deconstructs the Weapon object.
	*/
	~Weapon() = default;
};