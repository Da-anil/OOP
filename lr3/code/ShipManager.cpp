#include "ShipManager.h"
#include "CustomExceptions.h"
#include <stdexcept>
#include <iostream>

ShipManager::ShipManager(std::vector<int> &lenghts) {
    for (int length : lenghts) {
        addShip(length);
    }
}

void ShipManager::addShip(int length) {
    aliveShips.push_back(ships.size());
    ships.push_back(std::make_shared<Ship>(length));
}

bool ShipManager::isAllDestroyed() {
    return aliveShips.empty();
}

int ShipManager::update() {
    int count = 0;
    for (int i = 0; i < aliveShips.size(); i++) {
        if (ships[aliveShips[i]]->isDestroyed()) {
            count++;
            aliveShips.erase(aliveShips.begin() + i--);
        }
    }
    return count;
}

std::shared_ptr<Ship> ShipManager::getShip(int index) {
    if (index < 0 || index >= ships.size()) {
        throw std::invalid_argument("Invalid ship index");
    }
    return ships[index];
}

int ShipManager::getShipsCount() {
    return ships.size();
}

void ShipManager::printShips() {
    for (int i = 0; i < ships.size(); i++) {
        std::cout << "Ship: " << i << " length: " << ships[i]->getLength() << " State:";
        for (int j = 0; j < ships[i]->getLength(); j++) {
            std::cout << " " << (int)*ships[i]->getSegmentState(j);
        }
        std::cout << std::endl;
    }
}