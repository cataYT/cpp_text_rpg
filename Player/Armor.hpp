#pragma once

#include <iostream>

class Armor 
{
private:
	uint32_t resistanceForce = 0;
	uint32_t hp = 0;
	uint32_t maxHp = 1;

public:
	std::string armorName = "";
	Armor(const std::string& armorName, const uint32_t hp, const uint32_t maxHp, const uint32_t resistanceForce);
	void enhanceArmor(const uint32_t newResistanceForce);
	uint32_t checkHP() const;
	uint32_t getResistance() const;
	void repairArmor(const uint32_t repairAmount);
	void printStats() const;
	bool operator!=(const Armor& other) const;
	bool operator==(const Armor& other) const;
	Armor operator+(const Armor& other) const;
	~Armor();
};