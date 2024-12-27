#pragma once
#include "GameState.h"
#include <iostream>
#include <limits>

class Game {
private:
    GameState gameState;

    void playerAttack();
    void enemyAttack();
    void playerUseSkill();
    void playerTurn(int x, int y, bool skillUsed = false, int skill_x = 0, int skill_y = 0);
    void enemyTurn();

    bool updateEnemyShips();
    bool updatePlayerShips();

    void playerInitialize(int width, int height, std::vector<int> lengths);
    void enemyInitialize(int width, int height, std::vector<int> lengths);

    void playerWin();
    void enemyWin();
    void softReset();

public:

    Game() = default;
    void startGame();
    void printField();
    void startGameLoop();

    void save(std::string fileName);
    void load(std::string fileName);
};

