#pragma once

#include <exception>
#include <string>

class PlayerExceptions : public std::exception 
{
private:
    static std::string _msg;
public:
    class weapon_not_found 
    {
    private:
        std::string msg = _msg;
    public:
        explicit weapon_not_found(std::string message);
        virtual std::string what() const noexcept;
    };
};