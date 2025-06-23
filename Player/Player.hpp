#pragma once

#include <optional>
#include <functional>
#include <vector>

#include "Armor.hpp"
#include "Weapon.hpp"

/**
* @class Player
* @brief Represents a player in the game, with attributes such as name, health, weapons, and armor.
*/
class Player
{
private:
	/// @brief List of all players in the game.
	std::vector<Weapon> weapons = {};
	/// @brief Indicates whether the player is currently wearing armor.
	bool isWearingArmor = false;

protected:
	/// @brief Static vector to hold all players in the game.
	static std::vector<std::reference_wrapper<const Player>> players;

public:
	/// @brief Player's name.
	std::string plrName = "";
	/// @brief Player's health, initialized to 0.
	uint32_t health = 0;
	/// @brief Player's armor, initialized to a default Armor object.
	Armor currentArmor = Armor("", 0, 1, 0);
	/**
	* @brief Constructs a Player object with the specified name, health, weapons, and armor.
	* 
	* @param[in] plrName: The name of the player.
	* @param[in] health:  The initial health of the player.
	* @param[in] weapons: A vector of Weapon objects representing the player's weapons.
	* @param[in] armor:   An Armor object representing the player's armor.
	* 
	* @return A Player object initialized with the provided parameters.
	*/
	Player(const std::string& plrName, const uint32_t health, const std::vector<Weapon>& weapons, const Armor& armor);
	/**
	* @brief Removes a player from the static list of players.
	* 
	* @param[in] plr: The Player object to be removed.
	*/
	void static removePlayer(const Player& plr);
	/**
	* @brief Retrieves the list of weapons owned by the player.
	* 
	* @return A vector of Weapon objects representing the player's weapons.
	*/
	std::vector<Weapon> getWeapons() const;
	/**
	* @brief Prints the player's details.
	*/
	void getStats() const;
	/**
	* @brief Gets the total number of players currently in the game.
	*/
	static size_t getTotalPlayers();
	/**
	* @brief Updates the player's weapons with a new weapon of a specified type.
	* 
	* @param[in] type:   The type of weapon to update (e.g., "sword", "bow").
	* @param[in] weapon: The Weapon object to be added or updated.
	*/
	void updateWeapons(const std::string_view& type, const Weapon& weapon);
	/**
	* @brief Attacks a target player using a specified weapon.
	* 
	* @param[in] target:     The Player object representing the target of the attack.
	* @param[in] weaponName: The name of the weapon to be used for the attack.
	*/
	void attack(Player& target, const std::string& weaponName);
	/**
	* @brief Heals a target player by a specified amount.
	* 
	* @param[in] target: The Player object to be healed.
	* @param[in] amount: The amount of health to restore to the target player.
	*/
	void heal(Player& target, const int amount) const;
	/**
	* @brief Equips the player with a specified armor.
	* 
	* @param[in] armor: The Armor object to be equipped by the player.
	*/
	void equipArmor(const Armor& armor);
	/**
	* @brief Operator overload for adding two Player objects together, which combines their stats.
	*/
	friend Player operator+(const Player& lhs, const Player& rhs);
	/**
	* @brief Retrieves the winner of the game, if there is one.
	* 
	* @return An optional reference to the Player object representing the winner, or an empty optional if no winner exists.
	*/
	static std::optional<std::reference_wrapper<const Player>> getWinner();
	/**
	* @brief Destructor for the Player class.
	*/
	~Player();
};