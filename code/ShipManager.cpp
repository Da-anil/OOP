#include "ShipManager.h"
#include <stdexcept>
#include <iostream>

ShipManager::ShipManager(std::vector<int> &lenghts) {
    for (int length : lenghts) {
        addShip(length);
    }
}

void ShipManager::addShip(int length) {
    ships.push_back(Ship(length));
}

Ship* ShipManager::getShip(int index) {
    if (index < 0 || index >= ships.size()) {
        throw std::invalid_argument("Invalid ship index");
    }
    return &ships[index];
}

int ShipManager::getShipsCount() {
    return ships.size();
}

void ShipManager::printShips() {
    for (int i = 0; i < ships.size(); i++) {
        std::cout << "Ship: " << i << " length: " << ships[i].getLength() << " State:";
        for (int j = 0; j < ships[i].getLength(); j++) {
            std::cout << " " << (int)*ships[i].getSegmentState(j);
        }
        std::cout << std::endl;
    }
}