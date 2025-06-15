#include "Weapon.hpp"

Weapon::Weapon(const std::string& name, const uint32_t weapon_health, const uint32_t damage)
	: name(name), weapon_health(weapon_health), weapon_damage(damage) {}

std::string Weapon::getName() const
{
	return this->name;
}

uint32_t Weapon::getDamage() const
{
	return this->weapon_damage;  // 🔧 Fixed: Was incorrectly returning health
}

uint32_t Weapon::getHealth() const
{
	return this->weapon_health;
}

void Weapon::useWeapon(uint32_t damage)
{
	auto saturating_sub = [](uint32_t a, uint32_t b) {
		return (a < b) ? 0u : (a - b);
	};
	this->weapon_health = saturating_sub(this->weapon_health, damage);
}

void Weapon::repairWeapon(uint32_t health)
{
	this->weapon_health += health;
}

void Weapon::enhanceWeapon(uint32_t damage)
{
	this->weapon_damage += damage;
}