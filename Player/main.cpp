#include "Player.hpp"
#include "Armor.hpp"
#include "Weapon.hpp"
#include "PlayerExceptions.hpp"

/**
* @brief Main function that initializes a player and an enemy, allowing them to attack each other using weapons.
* 
* @return 0 on successful execution, or 1 if an error occurs.
*/
int main(void) 
{
	std::string playerName = "";
	std::print("Enter your player name: ");
	std::getline(std::cin, playerName);

	std::string weaponName = "";
	std::print("Enter weapon name: ");
	std::getline(std::cin, weaponName);

	uint32_t weaponDamageInt = 0;
	std::string weaponDamage = "";
	std::print("Enter weapon damage: ");
	std::cin >> weaponDamage;

	try {
		weaponDamageInt = std::stoi(weaponDamage);
	} catch (std::invalid_argument&) {
		std::println(std::cerr, "Invalid input. Please enter a valid integer.");
		return 1;
	} catch (std::out_of_range&) {
		std::println(std::cerr, "Input out of range for integer.");
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
		std::println("Caught exception on attack: {}", e.what());
	}

	std::string weaponUse = "";
	std::print("Enter the name of the weapon you want to use: ");
	std::getline(std::cin, weaponUse);

	try {
		cata.attack(enemy, weaponUse);
		if (enemy.health <= 0) {
			Player::removePlayer(enemy);
		}
	} catch (PlayerExceptions::weapon_not_found& e) {
		std::println("Caught exception on attack: {}", e.what());
	}

	if (auto winner = Player::getWinner()) {  // simpler than .has_value()
		std::println("{} has won!", winner->get().plrName);
	} else {
		std::println("No one won!");
	}

	return 0;
}