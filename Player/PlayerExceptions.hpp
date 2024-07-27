#pragma once

#include <exception>
#include <string>

class PlayerExceptions : public std::exception {
private:
    static const char* _msg;
public:
    class weapon_not_found {
    private:
        const char* msg = _msg;
    public:
        weapon_not_found(const char* message);
        virtual const char* what() const noexcept;
    };
};