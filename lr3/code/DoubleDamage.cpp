#include <iostream>
#include "DoubleDamage.h"

void DoubleDamage::use(GameField& field) {
    field.activateDoubleDamage();
    std::cout << "Double damage activated" << std::endl;
}

std::string DoubleDamage::getName() {
    return "Double Damage";
}