#include "Weapon.hpp"

Weapon::Weapon(std::string const& name, uint32_t weapon_health, uint32_t damage)
	: name(name), weapon_health(weapon_health), weapon_damage(damage) {}

std::string Weapon::getName() const
{
	return this->name;
}

uint32_t Weapon::getDamage() const
{
	return this->weapon_health;
}

void Weapon::useWeapon(uint32_t damage)
{
	auto saturating_sub = [](uint32_t a, uint32_t b)
	{
		return (a < b) ? 0u : (a - b);
	};

	this->weapon_health = saturating_sub(this->weapon_health, damage);
}

Weapon::~Weapon() {}