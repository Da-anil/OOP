#include <iostream>
#include <vector>
#include "Ship.h"
#include "ShipManager.h"
#include "GameField.h"

int main() {
    std::vector<int> lengths = {1, 2, 3, 4};
    ShipManager shipManager(lengths);
    GameField gameField(10, 10);
    // 1
    Ship* ship = shipManager.getShip(0);
    gameField.placeShip(*ship, 0, 0, Direction::horizontal);
    // 2
    ship = shipManager.getShip(1);
    gameField.placeShip(*ship, 0, 8, Direction::horizontal);
    // 3
    ship = shipManager.getShip(2);
    gameField.placeShip(*ship, 0, 2, Direction::horizontal);
    // 4
    ship = shipManager.getShip(3);
    gameField.placeShip(*ship, 0, 4, Direction::horizontal);

    gameField.attackCell(1, 2);
    gameField.attackCell(1, 2);
    gameField.attackCell(1, 2);
    gameField.attackCell(0, 0);

    gameField.printField();
    shipManager.printShips();

    return 0;
}