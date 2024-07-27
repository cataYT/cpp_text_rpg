#include "PlayerExceptions.hpp"

PlayerExceptions::weapon_not_found::weapon_not_found(const char* message) {
	this->msg = message;
}

const char* PlayerExceptions::weapon_not_found::what() const noexcept {
	return msg;
}