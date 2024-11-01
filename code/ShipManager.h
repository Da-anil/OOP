#pragma once
#include <vector>
#include "Ship.h"

class ShipManager {
private:
    std::vector<Ship> ships;
public:
    ShipManager(std::vector<int> &lengths);
    Ship* getShip(int index);
    int getShipsCount();
    void addShip(int length);
    void printShips();
};
