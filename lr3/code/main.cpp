#include <iostream>
#include <vector>
#include "Game.h"
#include "Ship.h"
#include "ShipManager.h"
#include "GameField.h"
#include "SkillManager.h"

int main() {
    // std::vector<int> lengths = {1, 2, 3, 4};
    // ShipManager shipManager(lengths);
    // GameField gameField(10, 10);
    // // 1
    // Ship* ship = shipManager.getShip(0);
    // gameField.placeShip(*ship, 0, 0, Direction::horizontal);
    // // 2
    // ship = shipManager.getShip(1);
    // gameField.placeShip(*ship, 3, 8, Direction::vertical);
    // // 3
    // ship = shipManager.getShip(2);
    // gameField.placeShip(*ship, 0, 2, Direction::horizontal);
    // // 4
    // ship = shipManager.getShip(3);
    // gameField.placeShip(*ship, 0, 4, Direction::horizontal);

    // gameField.attackCell(1, 2);
    // gameField.attackCell(1, 2);
    // gameField.attackCell(1, 2);
    // gameField.attackCell(0, 0);

    // gameField.printField();
    // gameField.printFieldVision();
    // shipManager.printShips();

    // SkillManager skillManager;

    // skillManager.printSkills();
    // skillManager.useSkill(gameField);
    // skillManager.useSkill(gameField);
    // skillManager.useSkill(gameField);

    // skillManager.addRandomSkill();

    // int x, y;
    // while (true) {
    //     std::cout << "Enter coordinates to attack (x, y): ";
    //     std::cin >> x >> y;
    //     if (std::cin.fail()) {
    //         std::cin.clear();
    //         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    //         std::cout << "Invalid input. Please try again." << std::endl;
    //         continue;
    //     }
    //     break;
    // }

    // gameField.attackCell(x, y);

    // gameField.printField();
    // gameField.printFieldVision();
    // shipManager.printShips();
    // skillManager.printSkills();

    // return 0;


    Game game;
    game.startGame();
    game.startGameLoop();
    
    return 0;
}