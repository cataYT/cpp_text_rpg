#pragma once

#include <optional>
#include <functional>
#include <vector>

#include "Armor.hpp"
#include "Weapon.hpp"

class Player
{
private:
	std::vector<Weapon> weapons = {};
	bool isWearingArmor = false;

protected:
	static std::vector<std::reference_wrapper<const Player>> players;

public:
	std::string plrName = "";
	uint32_t health = 0;
	Armor currentArmor = Armor("", 0, 1, 0);
	Player(const std::string& plrName, const uint32_t health, const std::vector<Weapon>& weapons, const Armor& armor);
	void static removePlayer(const Player& plr);
	std::vector<Weapon> getWeapons() const;
	void getStats() const;
	static size_t getTotalPlayers();
	void updateWeapons(const std::string_view& type, const Weapon& weapon);
	void attack(Player& target, const std::string& weaponName);
	void heal(Player& target, const int amount) const;
	void equipArmor(const Armor& armor);
	friend Player operator+(const Player& lhs, const Player& rhs);
	static std::optional<std::reference_wrapper<const Player>> getWinner();
	~Player();
};