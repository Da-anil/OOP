#pragma once
#include <iostream>
#include "GameField.h"
#include "Skill.h"

class Barrage : public Skill {
public:
    void use(GameField& field) override;
    std::string getName() override;
};
