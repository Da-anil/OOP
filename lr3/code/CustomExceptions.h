#pragma once
#include <stdexcept>

class NoSkillAvailable : public std::runtime_error {
public:
    explicit NoSkillAvailable(const std::string& message) : std::runtime_error(message) {}
};

class InvalidShipPlacement : public std::runtime_error {
public:
    explicit InvalidShipPlacement(const std::string& message) : std::runtime_error(message) {}
};

class OutOfBounds : public std::runtime_error {
public:
    explicit OutOfBounds(const std::string& message) : std::runtime_error(message) {}
};