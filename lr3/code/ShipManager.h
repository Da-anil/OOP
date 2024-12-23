#pragma once
#include <memory>
#include <vector>
#include "Ship.h"

class ShipManager {
private:
    std::vector<int> aliveShips;
    std::vector<std::shared_ptr<Ship>> ships;
public:
    ShipManager() = default;
    ShipManager(std::vector<int> &lengths);
    std::shared_ptr<Ship> getShip(int index);
    int getShipsCount();
    void addShip(int length);
    bool isAllDestroyed();
    int update();
    void printShips();
};
