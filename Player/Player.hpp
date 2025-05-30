#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <random>

#include "Armor.hpp"
#include "Weapon.hpp"

class Player 
{
private:
	std::vector<Weapon> weapons;
	bool isWearingArmor;
protected:
	static std::vector<Player*> players;
public:
	std::string plrName;
	uint32_t health;
	Armor currentArmor;
	Player(std::string const& plrName, uint32_t health, std::vector<Weapon> const& weapons, Armor const& armor);
	void static removePlayer(Player* plr);
	std::vector<Weapon> getWeapons() const;
	void getStats() const;
	static size_t getTotalPlayers();
	void updateWeapons(std::string_view const& type, Weapon const& weapon);
	void attack(Player& target, const std::string& weaponName);
	void heal(Player const& target, int const& amount) const;
	void equipArmor(Armor const& armor);
	friend Player operator+(const Player& lhs, const Player& rhs);
	static Player* getWinner();
	~Player();
};