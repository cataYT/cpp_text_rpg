#include "Player.hpp"
#include "Armor.hpp"
#include "Weapon.hpp"
#include "PlayerExceptions.hpp"

int main(void) 
{
	std::ios::sync_with_stdio(false);

	std::string playerName = "";
	std::cout << "Enter your player name: ";
	std::getline(std::cin, playerName);

	std::string weaponName = "";
	std::cout << "Enter weapon name: ";
	std::getline(std::cin, weaponName);

	uint32_t weaponDamageInt = 0;
	std::string weaponDamage = "";
	std::cout << "Enter weapon damage: ";
	std::cin >> weaponDamage;

	try {
		weaponDamageInt = std::stoi(weaponDamage);
	} catch (std::invalid_argument&) {
		std::cerr << "Invalid input. Please enter a valid integer." << std::endl;
		return 1;
	} catch (std::out_of_range&) {
		std::cerr << "Input out of range for integer." << std::endl;
		return 1;
	}

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::vector<Weapon> playerWeapons = {};
	playerWeapons.emplace_back(weaponName, 100, weaponDamageInt);
	Armor basicArmor("BASIC", 10, 100, 1);

	auto cata = Player(playerName, 100, playerWeapons, basicArmor);
	std::vector<Weapon> enemyWeapons = {};
	enemyWeapons.emplace_back("Sword", 100, 10);
	auto enemy = Player("Enemy", 50, enemyWeapons, basicArmor);

	try {
		enemy.attack(cata, "Sword");
		if (cata.health <= 0) {
			Player::removePlayer(cata);
		}
	} catch (PlayerExceptions::weapon_not_found& e) {
		std::cout << "Caught exception on attack: " << e.what() << std::endl;
	}

	std::string weaponUse = "";
	std::cout << "Enter the name of the weapon you want to use: ";
	std::getline(std::cin, weaponUse);

	try {
		cata.attack(enemy, weaponUse);
		if (enemy.health <= 0) {
			Player::removePlayer(enemy);
		}
	} catch (PlayerExceptions::weapon_not_found& e) {
		std::cout << "Caught exception on attack: " << e.what() << std::endl;
	}

	if (auto winner = Player::getWinner()) {  // simpler than .has_value()
		std::cout << winner->get().plrName << " has won!" << std::endl;
	} else {
		std::cout << "No one won!" << std::endl;
	}

	return 0;
}