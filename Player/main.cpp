#include <iostream>
#include <string>
#include <chrono>
#include <filesystem>
#include <fstream>

#include "Player.hpp"
#include "PlayerExceptions.hpp"

int main() {
	std::chrono::steady_clock::time_point startTime = std::chrono::high_resolution_clock::now();

	std::filesystem::path dirPath = "C:/Users/firzt/source/repos/Project1/Project1";
	std::filesystem::path filePath = dirPath / "executionTime.txt";

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
		exit(1);
	} catch (std::out_of_range) {
		std::cerr << "Input out of range for integer." << std::endl;
		exit(1);
	}

	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::unordered_map<std::string, int> weapons;
	weapons[weaponName] = *weaponDamageIntPtr;
	delete weaponDamageIntPtr;
	Player* cata = new Player(playerName, 100, weapons);

	// cata->updateWeapons("add", {"Chain of Thousand Miles", 100});

	Player* enemy = new Player("Enemy", 50, { {"Sword", 10} });

	try {
		enemy->attack(*cata, "Sword");
		if (cata->health == 0) {
			delete cata;
			cata = nullptr;
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
		if (enemy->health == 0) {
			delete enemy;
			enemy = nullptr;
		}
	} catch (PlayerExceptions::weapon_not_found& e) {
		std::cout << "Caught exception on attack: " << e.what() << std::endl;
	}

	Player* winner = Player::checkWin();
	std::cout << winner->plrName << " has won!" << std::endl;

	if (cata != nullptr) {
		delete cata;
		cata = nullptr;
	}
	if (enemy != nullptr) {
		delete enemy;
		enemy = nullptr;
	}

	std::chrono::steady_clock::time_point endTime = std::chrono::high_resolution_clock::now();
	std::chrono::nanoseconds duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);

	std::ofstream outFile(filePath);
	if (outFile.is_open()) {
		outFile << "Execution time: " << duration.count() << "ns";
		outFile.close();
	} else {
		std::cout << "Failed to write execution time" << std::endl;
	}

	return 0;
}