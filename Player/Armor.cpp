#include "Armor.hpp"

Armor::Armor(const char* armorName = "", int hp = 0, int maxHp = 1, int resistanceForce = 0) :
	armorName(armorName),
	hp(hp),
	maxHp(maxHp),
	resistanceForce(resistanceForce)

{
	if (resistanceForce < 0) {
		throw std::invalid_argument("Resistance force cannot be negative");
	}

	if (hp < 0) {
		throw std::invalid_argument("Hp cannot be negative");
	}

	if (hp > maxHp) {
		throw std::invalid_argument("Hp cannot be larger than maxHp");
	}

	if (maxHp <= 0) {
		throw std::invalid_argument("maxHp must be positive");
	}
}

void Armor::enhanceArmor(int &newResistanceForce) {
	if (newResistanceForce > 0) {
		this->resistanceForce += newResistanceForce;
	} else {
		std::cout << "Armor cannot be enhanced with negative trait" << std::endl;
	}
}

int Armor::checkHP() const {
	return this->hp;
}

int Armor::getResistance() const {
	return this->resistanceForce;
}

void Armor::repairArmor(int &repairAmount) {
	if (repairAmount > 0) {
		if (this->hp != maxHp) {
			this->hp += repairAmount;
			if (this->hp > maxHp) {
				this->hp = maxHp;
			}
		} else {
			std::cout << "Armor is already at its best health" << std::endl;
		}
	} else {
		std::cout << "Repair amount cannot be negative" << std::endl;
	}
}

void Armor::printStats() {
	std::cout << "Armor name: " << this->armorName << std::endl;
	std::cout << "Armor hp: " << this->hp << std::endl;
	std::cout << "Armor max hp: " << this->maxHp << std::endl;
	std::cout << "Armor resistance: " << this->resistanceForce << std::endl;
}

bool Armor::operator!=(const Armor& other) const {
	if (this->armorName == other.armorName
		&& this->checkHP() == other.checkHP()
		&& this->maxHp == other.maxHp
		&& this->getResistance() == other.getResistance())
	{
		return false;
	} else {
		return true;
	}
}

bool Armor::operator==(const Armor& other) const {
	if (this->armorName == other.armorName
		&& this->checkHP() == other.checkHP()
		&& this->maxHp == other.maxHp
		&& this->getResistance() == other.getResistance())
	{
		return true;
	}
	else {
		return false;
	}
}

Armor Armor::operator+(const Armor& other) const {
	std::string newName = std::string(this->armorName) + ":" + other.armorName;
	int newHp = this->checkHP() + other.checkHP();
	int newMaxHp = this->maxHp + other.maxHp;
	int newResistanceForce = this->getResistance() + other.getResistance();
	return Armor(newName.c_str(), newHp, newMaxHp, newResistanceForce);
}

Armor::~Armor() {

}