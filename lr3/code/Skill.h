#pragma once
#include "GameField.h"
#include <string>

class Skill {
public:
    virtual void use(GameField& field) = 0;
    virtual std::string getName() = 0;
};