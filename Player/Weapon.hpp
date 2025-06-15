#pragma once

#include <iostream>
#include <string>

class Weapon
{
private:
	std::string name;
	uint32_t weapon_health = 0;
	uint32_t weapon_damage = 0;

public:
	Weapon(const std::string& name, const uint32_t weapon_health, const uint32_t damage);

	std::string getName() const;
	uint32_t getHealth() const;
	uint32_t getDamage() const;

	void useWeapon(uint32_t damage);
	void repairWeapon(uint32_t health);
	void enhanceWeapon(uint32_t damage);

	bool operator==(const Weapon& other) const = default;

	~Weapon() = default;
};