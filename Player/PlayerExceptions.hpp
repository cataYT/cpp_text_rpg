#pragma once

#include <exception>
#include <string>

/**
* @class PlayerExceptions
* @brief Custom exception class for player-related errors, such as weapon not found.
*/
class PlayerExceptions : public std::exception 
{
private:
	/// @brief Static message to be used in exceptions.
    static std::string _msg;

public:
    /**
	* @class weapon_not_found
	* @brief Exception thrown when a weapon is not found in the player's inventory.
    */
    class weapon_not_found
    {
    private:
		/// @brief Message to be displayed when the exception is thrown.
        std::string msg = _msg = "";

    public:
        /**
		* @brief Constructs a weapon_not_found exception with a specific message.
        * 
		* @param[in] message: The message to be displayed when the exception is thrown.
        */
        explicit weapon_not_found(std::string_view message);
        /**
		* @brief Returns the message associated with the exception.
        * 
		* @return A string containing the exception message.
        */
        virtual std::string what() const noexcept;
    };
};