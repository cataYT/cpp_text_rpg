#pragma once

#include <iostream>

class Armor 
{
private:
	uint32_t resistanceForce;
	uint32_t hp;
	uint32_t maxHp;
public:
	std::string armorName;
	Armor(std::string armorName, uint32_t hp, uint32_t maxHp, uint32_t resistanceForce);
	void enhanceArmor(uint32_t const& newResistanceForce);
	uint32_t checkHP() const;
	uint32_t getResistance() const;
	void repairArmor(uint32_t const& repairAmount);
	void printStats() const;
	bool operator!=(const Armor& other) const;
	bool operator==(const Armor& other) const;
	Armor operator+(const Armor& other) const;
	~Armor();
};