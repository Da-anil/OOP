#include "Barrage.h"
#include <random>
#include <iostream>

void Barrage::use(GameField& field) {
    std::vector<std::pair<int, int>> occupied = field.getOccupiedCells();
    if (occupied.size() == 0) {
        std::cout << "No ships left" << std::endl;
        return;
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, occupied.size() - 1);

    int index = dis(gen);

    field.attackCellWithoutVision(occupied[index].first, occupied[index].second);
    std::cout << "Barrage used" << std::endl;
}

std::string Barrage::getName() {
    return "Barrage";
}