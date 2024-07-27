#include "Player.hpp"
#include "PlayerExceptions.hpp"

int main() {
	std::ios::sync_with_stdio(false);

	std::string playerName;
	std::cout << "Enter your player name: ";
	std::getline(std::cin, playerName);

	std::string weaponName;
	std::cout << "Enter weapon name: ";
	std::getline(std::cin, weaponName);

	std::string weaponDamage;
	int* weaponDamageIntPtr = new int;
	std::cout << "Enter weapon damage: ";
	std::cin >> weaponDamage;

	try {
		*weaponDamageIntPtr = std::stoi(weaponDamage);
	} catch (std::invalid_argument) {
		std::cerr << "Invalid input. Please enter a valid integer." << std::endl;
		delete weaponDamageIntPtr;
		exit(1);
	} catch (std::out_of_range) {
		std::cerr << "Input out of range for integer." << std::endl;
		delete weaponDamageIntPtr;
		exit(1);
	}

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::unordered_map<std::string, int> playerWeapons;
	playerWeapons[weaponName] = *weaponDamageIntPtr;
	delete weaponDamageIntPtr;
	Armor basicArmor("BASIC", 10, 100, 1);
	std::unique_ptr<Player> cata = std::make_unique<Player>(playerName.c_str(), 100, playerWeapons, basicArmor);

	// cata->updateWeapons("add", {"Chain of Thousand Miles", 100});

	std::unordered_map<std::string, int> enemyWeapons;
	enemyWeapons["Sword"] = 10;
	std::unique_ptr<Player> enemy = std::make_unique<Player>("Enemy", 50, enemyWeapons, basicArmor);

	try {
		enemy->attack(*cata, "Sword");
		if (cata->health <= 0) {
			Player::removePlayer(cata.get());
		}
	}
	catch (PlayerExceptions::weapon_not_found& e) {
		std::cout << "Caught exception on attack: " << e.what() << std::endl;
	}

	std::string weaponUse;
	std::cout << "Enter the name of the weapon you want to use: ";
	std::getline(std::cin, weaponUse);

	try {
		cata->attack(*enemy, weaponUse);
		if (enemy->health <= 0) {
			Player::removePlayer(enemy.get());
		}
	} catch (PlayerExceptions::weapon_not_found& e) {
		std::cout << "Caught exception on attack: " << e.what() << std::endl;
	}
	
	Player* winner = Player::getWinner();
	if (winner != nullptr) {
		std::cout << winner->plrName << " has won!" << std::endl;
	} else {
		std::cout << "No one won!" << std::endl;
	}

	return 0;
}