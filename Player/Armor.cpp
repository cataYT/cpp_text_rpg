#include "Armor.hpp"

Armor::Armor(const std::string& armorName, const uint32_t hp, const uint32_t maxHp, const uint32_t resistanceForce) :
	resistanceForce(resistanceForce),
	hp(hp),
	maxHp(maxHp),
	armorName(armorName)

{
	if (hp > maxHp) {
		throw std::invalid_argument("Hp cannot be larger than maxHp");
	}

	if (maxHp <= 0) {
		throw std::invalid_argument("maxHp must be positive");
	}
}

void Armor::enhanceArmor(const uint32_t newResistanceForce)
{
	this->resistanceForce += newResistanceForce;
}

inline uint32_t Armor::checkHP() const
{
	return this->hp;
}

inline uint32_t Armor::getResistance() const
{
	return this->resistanceForce;
}

void Armor::repairArmor(const uint32_t repairAmount)
{
	if (this->hp != maxHp) {
		this->hp += repairAmount;
		if (this->hp > maxHp) {
			this->hp = maxHp;
		}
	} else {
		std::cout << "Armor is already at its best health" << std::endl;
	}
}

inline void Armor::printStats() const
{
	std::cout << "Armor name: " << this->armorName << std::endl;
	std::cout << "Armor hp: " << this->hp << std::endl;
	std::cout << "Armor max hp: " << this->maxHp << std::endl;
	std::cout << "Armor resistance: " << this->resistanceForce << std::endl;
}

bool Armor::operator!=(const Armor& other) const
{
	if (this->armorName == other.armorName
		&& this->checkHP() == other.checkHP()
		&& this->maxHp == other.maxHp
		&& this->getResistance() == other.getResistance()) {
		return false;
	} else {
		return true;
	}
}

bool Armor::operator==(const Armor& other) const 
{
	if (this->armorName == other.armorName
		&& this->checkHP() == other.checkHP()
		&& this->maxHp == other.maxHp
		&& this->getResistance() == other.getResistance()) {
		return true;
	} else {
		return false;
	}
}

Armor Armor::operator+(const Armor& other) const 
{
	const std::string newName = this->armorName + ":" + other.armorName;
	const int newHp = this->checkHP() + other.checkHP();
	const int newMaxHp = this->maxHp + other.maxHp;
	const int newResistanceForce = this->getResistance() + other.getResistance();
	return Armor(newName, newHp, newMaxHp, newResistanceForce);
}

Armor::~Armor() = default;