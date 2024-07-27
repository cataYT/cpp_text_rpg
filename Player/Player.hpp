#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <random>

#include "Armor.hpp"

class Player {
private:
	std::unordered_map<std::string, int> weapons;
	bool isWearingArmor;
protected:
	static std::vector<Player*> players;
public:
	const char* plrName;
	int health;
	Armor currentArmor;
	Player(const char* plrName, int health, std::unordered_map<std::string, int> weapons, Armor armor);
	void static removePlayer(Player* plr);
	inline void getStats() const;
	inline static size_t getTotalPlayers();
	void updateWeapons(const char* type, std::pair<std::string, int> &value);
	void attack(Player &target, std::string weaponName);
	void heal(Player &target, int &amount);
	void equipArmor(Armor &armor);
	static Player* getWinner();
	Player operator+(const Player &other) const;
	~Player();
};