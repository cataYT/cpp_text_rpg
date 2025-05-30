#include "PlayerExceptions.hpp"

PlayerExceptions::weapon_not_found::weapon_not_found(std::string message)
{
	this->msg = message;
}

std::string PlayerExceptions::weapon_not_found::what() const noexcept
{
	return msg;
}