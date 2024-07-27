#pragma once

#include <iostream>

class Armor {
private:
	int resistanceForce;
	int hp;
	int maxHp;
public:
	const char* armorName;
	Armor(const char* armorName, int hp, int maxHp, int resistanceForce);
	void enhanceArmor(int &newResistanceForce);
	inline int checkHP() const;
	inline int getResistance() const;
	void repairArmor(int &repairAmount);
	inline void printStats();
	bool operator!=(const Armor& other) const;
	bool operator==(const Armor& other) const;
	Armor operator+(const Armor& other) const;
	~Armor();
};