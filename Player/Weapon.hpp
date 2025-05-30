#include <iostream>

class Weapon
{
private:
	std::string name;
	uint32_t weapon_health;
	uint32_t weapon_damage;

public:
	Weapon(std::string const& name, uint32_t weapon_health, uint32_t damage);
	std::string getName() const;
	uint32_t getDamage() const;
	void useWeapon(uint32_t damage);
	~Weapon() = default;
};