#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>

#include "Armor.hpp"

class Player {
private:
	std::unordered_map<std::string, int> weapons;
	bool isWearingArmor;
protected:
	static std::vector<Player*> players;
public:
	std::string plrName;
	int health;
	Armor currentArmor;
	Player(std::string plrName, int health, std::unordered_map<std::string, int> weapons, Armor armor);
	inline void getStats() const;
	inline static size_t getTotalPlayers();
	void updateWeapons(std::string type, std::pair<std::string, int> value);
	void attack(Player &target, std::string weaponName);
	void heal(Player &target, int amount);
	void equipArmor(Armor armor);
	static Player* checkWin();
	Player operator+(const Player &other) const;
	~Player();
};