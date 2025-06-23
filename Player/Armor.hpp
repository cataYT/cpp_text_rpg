#pragma once

#include <iostream>

/**
* @class Armor
* @brief Represents an armor with properties such as resistance, health points (HP), and maximum HP.
*/
class Armor 
{
private:
	/// @brief The resistance force of the armor, which determines how much damage it can absorb.
	uint32_t resistanceForce = 0;
	/// @brief The current health points (HP) of the armor.
	uint32_t hp = 0;
	/// @brief The maximum health points (HP) of the armor. 
	uint32_t maxHp = 1;

public:
	/// @brief The name of the armor.
	std::string armorName = "";
	/**
	* @brief Constructs an Armor object with specified properties.
	* 
	* @param[in] armorName:		  The name of the armor.
	* @param[in] hp:			  The current health points (HP) of the armor.
	* @param[in] maxHp:			  The maximum health points (HP) of the armor.
	* @param[in] resistanceForce: The resistance force of the armor, which determines how much damage it can absorb.
	* 
	* @return An instance of the Armor class initialized
	*/
	Armor(const std::string& armorName, const uint32_t hp, const uint32_t maxHp, const uint32_t resistanceForce);
	/**
	* @brief Enhances the armor's resistance force.
	* 
	* @param[in] newResistanceForce: The new resistance force to be set for the armor.
	*/
	void enhanceArmor(const uint32_t newResistanceForce);
	/**
	* @brief Gets the current health points (HP) of the armor.
	* 
	* @return The current health points (HP) of the armor.
	*/
	uint32_t checkHP() const;
	/**
	* @brief Gets the resistance force of the armor.
	* 
	* @return The resistance force of the armor, which determines how much damage it can absorb.
	*/
	uint32_t getResistance() const;
	/**
	* @brief Repairs the armor by a specified amount.
	* 
	* @param[in] repairAmount: The amount of health to restore to the armor.
	*/
	void repairArmor(const uint32_t repairAmount);
	/**
	* @brief Prints all the details of armor.
	*/
	void printStats() const;
	/**
	* @brief Compares two Armor objects for inequality.
	* 
	* @param[in] other: The other Armor object to compare with.
	* 
	* @return True if the two Armor objects are not equal, false otherwise.
	*/
	bool operator!=(const Armor& other) const;
	/**
	* @brief Compares two Armor objects for equality.
	* 
	* @param[in] other: The other Armor object to compare with.
	* 
	* @return True if the two Armor objects are equal, false otherwise.
	*/
	bool operator==(const Armor& other) const;
	/**
	* @brief Combines the properties of two Armor objects.
	* 
	* @param[in] other: The other Armor object to combine with.
	* 
	* @return A new Armor object that represents the combination of the two Armor objects.
	*/
	Armor operator+(const Armor& other) const;
	/**
	* @brief Destructor for the Armor class.
	* @brief Destructor for the Armor class.
	*/
	~Armor();
};