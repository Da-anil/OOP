#pragma once
#include "GameField.h"
#include "Skill.h"

class Scanner : public Skill {
public:
    void use(GameField& field) override;
    std::string getName() override;
};