#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>

class Player {
private:
	std::unordered_map<std::string, int> weapons;
protected:
	static std::vector<Player*> players;
public:
	std::string plrName;
	int health;
	Player(std::string plrName, int health, std::unordered_map<std::string, int> weapons);
	void getStats() const;
	static size_t getTotalPlayers();
	void updateWeapons(std::string type, std::pair<std::string, int> value);
	void attack(Player &target, std::string weaponName);
	void heal(Player &target, int amount);
	static Player* checkWin();
	Player operator+(const Player &other) const;
	~Player();
};