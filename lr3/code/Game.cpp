#include "Game.h"
#include "CustomExceptions.h"
#include <iostream>
#include <vector>
#include <fstream>

void Game::startGame() {
    gameState.roundCount = 1;
    int width = 8;
    int height = 8;
    std::vector<int> lengths = {1, 2, 3, 4};
    playerInitialize(width, height, lengths);
    enemyInitialize(width, height, lengths);
}

void Game::printField() {
    std::cout << "Your field:" << std::endl;
    gameState.playerField->printField();
    std::cout << "Enemy field:" << std::endl;
    gameState.enemyField->printField();
}

void Game::startGameLoop() {
    bool gameOver = false;
    bool playerTurn = false;
    std::string fileName;

    int choice; 
    while (!gameOver) {
        // Player's turn
        playerTurn = true;

        while (playerTurn) {
            std::cout << "Your field:" << std::endl;
            gameState.playerField->printField();
            std::cout << "Enemy field:" << std::endl;
            gameState.enemyField->printFieldVision();
            std::cout << "Your skills: ";
            gameState.skillManager->printSkills();
            std::cout << "What do you want to do? (0 - attack, 1 - use skill, 2 - save, 3 - load, 4 - exit)" << std::endl;

            std::cin >> choice;
            if (std::cin.fail() || (choice < 0 || choice > 4)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please try again." << std::endl;
                continue;
            }
            switch (choice)
            {
            case 0:
                playerAttack();
                if (updateEnemyShips()) {
                    playerWin();
                    break;
                }
                playerTurn = false;
                break;
            case 1:
                playerUseSkill();
                if (updateEnemyShips()) {
                    playerWin();
                }
                break;
            case 2:
                std::cout << "Enter file name: ";
                if (!(std::cin >> fileName)) {
                    std::cout << "Invalid input. Please try again." << std::endl;
                    continue;
                }
                try {
                    save(fileName);
                }
                catch (std::invalid_argument& e) {
                    std::cout << e.what() << std::endl;
                }
                break;
            case 3:
                std::cout << "Enter file name: ";
                if (!(std::cin >> fileName)) {
                    std::cout << "Invalid input. Please try again." << std::endl;
                    continue;
                }
                try {
                    load(fileName);
                }
                catch (std::invalid_argument& e) {
                    std::cout << e.what() << std::endl;
                }
                break;
            case 4:
                playerTurn = false;
                gameOver = true;
                break;
            default:
                break;
            }
        }

        // Enemy's turn
        enemyAttack();
        if (updatePlayerShips()) {
            enemyWin();
        }
    }
}

void Game::playerAttack() {
    int x, y;
    bool playerTurn = true;
    while (playerTurn) {
        std::cout << "Enter coordinates for attack (x, y): ";
        std::cin >> x >> y;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please try again." << std::endl;
            continue;;
        }
        try {
            gameState.enemyField->attackCell(x, y);
        } 
        catch (OutOfBounds& e) {
            std::cout << e.what() << std::endl;
            continue;
        }
        playerTurn = false;
    }
}

void Game::playerUseSkill() {
    try {
        gameState.skillManager->useSkill(*gameState.enemyField);
    } 
    catch (NoSkillAvailable& e) {
        std::cout << e.what() << std::endl;
        return;
    }
}

bool Game::updateEnemyShips() {
    int count = gameState.enemyShips->update();
    if (count > 0) {
        gameState.skillManager->addRandomSkill();
        std::cout << "Enemy ship destroyed!"<< std::endl;
        if (gameState.enemyShips->isAllDestroyed()) {
            return true;
        }
    }
    return false;
}

bool Game::updatePlayerShips() {
    int count = gameState.playerShips->update();
    if (count > 0) {
        std::cout << "Your ship destroyed!" << std::endl;
        if (gameState.playerShips->isAllDestroyed()) {
            return true;
        }
    }
    return false;
}

void Game::playerWin() {
    std::cout << "You won!" << std::endl;
    std::cout << "Total rounds won: " << gameState.roundCount++ << std::endl;
    std::cout << "Enemy has been restarted" << std::endl;
    softReset();
}

void Game::enemyWin() {
    std::cout << "You lost!" << std::endl;
    std::cout << "Total rounds won: " << gameState.roundCount << std::endl;
    std::cout << "Game has been restarted" << std::endl;
    gameState.roundCount = 1;
    startGame();
}

void Game::playerInitialize(int width, int height, std::vector<int> lengths) {
    std::cout << "Game started, field size: " << height << " x " << width << ", ships:";
    for (int i = 0; i < lengths.size(); i++) {
        std::cout << " " << lengths[i];
    }
    std::cout << std::endl;


    gameState.playerField = std::make_unique<GameField>(8, 8);
    gameState.playerShips = std::make_unique<ShipManager>(lengths);
    gameState.skillManager = std::make_unique<SkillManager>();

    int x, y, direction;
    int shipIndex = 0;
    bool shipPlacement = true;
    while(shipPlacement) {
        std::cout << "Enter coordinates and direction(0 - horizontal, 1 - vertical) for ship " << shipIndex << " (x, y, dir): ";
        std::cin >> x >> y >> direction;
        if (std::cin.fail() || (direction != 0 && direction != 1)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please try again." << std::endl;
            continue;
        }
        try {
            gameState.playerField->placeShip(*gameState.playerShips->getShip(shipIndex), x, y, direction == 0 ? Direction::horizontal : Direction::vertical);
        } catch (InvalidShipPlacement& e) {
            std::cout << e.what() << std::endl;
            continue;
        }
        shipIndex += 1;
        if (shipIndex == 4) {
            shipPlacement = false;
        }
    }
}

void Game::enemyInitialize(int width, int height, std::vector<int> lengths) {

    gameState.enemyField = std::make_unique<GameField>(width, height);
    gameState.enemyShips = std::make_unique<ShipManager>(lengths);

    std::shared_ptr<Ship> ship = gameState.enemyShips->getShip(0);
    gameState.enemyField->placeShip(*ship, 0, 0, Direction::horizontal);
    ship = gameState.enemyShips->getShip(1);
    gameState.enemyField->placeShip(*ship, 2, 2, Direction::vertical);
    ship = gameState.enemyShips->getShip(2);
    gameState.enemyField->placeShip(*ship, 4, 4, Direction::horizontal);
    ship = gameState.enemyShips->getShip(3);
    gameState.enemyField->placeShip(*ship, 0, 7, Direction::horizontal);
}

void Game::softReset() {
    enemyInitialize(8, 8, {1, 2, 3, 4});
}

void Game::enemyAttack() {
    int x, y;
    x = 0;
    y = 0;
    gameState.playerField->attackCell(x, y);

    std::cout << "Enemy attacked " << x << ", " << y << std::endl;
}

void Game::save(std::string fileName) {
    std::ofstream file(fileName);
    if (!file.is_open()) {
        file.close();
        throw std::runtime_error("Failed to open file");
    }
    file << gameState;
    file.close();
}

void Game::load(std::string fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        file.close();
        throw std::runtime_error("Failed to open file");
    }
    file >> gameState;
    file.close();
}