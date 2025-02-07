#include "GameField.h"
#include "CustomExceptions.h"
#include <random>
#include <algorithm>
#include <iostream>

GameField::GameField(int width, int height) {
    this->width = width;
    this->height = height;
    this->cells = std::vector<std::vector<Cell>>(height, std::vector<Cell>(width, Cell{CellState::unknown, nullptr}));
}

GameField::GameField(const GameField& other) {
    this->width = other.width;
    this->height = other.height;
    this->cells = other.cells;
}

GameField& GameField::operator=(const GameField& other) {
    if (this != &other) {
        this->width = other.width;
        this->height = other.height;
        this->cells = other.cells;
    }
    return *this;
}

GameField::GameField(GameField&& other) {
    this->width = other.width;
    this->height = other.height;
    this->cells = std::move(other.cells);
}

GameField& GameField::operator=(GameField&& other) {
    if (this != &other) {
        this->width = other.width;
        this->height = other.height;
        this->cells = std::move(other.cells);
    }
    return *this;
}

void GameField::placeShip(Ship& ship, int x, int y, Direction direction) {
    int length = ship.getLength();

    int dx = direction == Direction::horizontal ? 1 : 0;
    int dy = direction == Direction::vertical ? 1 : 0;

    if (x < 0 || x + length * dx > width || y < 0 || y + length * dy > height) {
        throw InvalidShipPlacement("Invalid ship placement");
    }

    int mn_x = std::max(x - 1, 0);
    int mx_x = std::min(x + length * dx + 1, width);
    int mn_y = std::max(y - 1, 0);
    int mx_y = std::min(y + length * dy + 1, height);

    for (int i = mn_y; i < mx_y; i++) {
        for (int j = mn_x; j < mx_x; j++) {
            if (cells[i][j].segmentState != nullptr) {
                throw InvalidShipPlacement("Invalid ship placement");
            }
        }
    }
    

    for (int i = 0; i < length; i++) {
        cells[y + i * dy][x + i * dx].segmentState = ship.getSegmentState(i);
    }
}

void GameField::attackCellWithoutVision(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw OutOfBounds("Invalid cell coordinates");
    }
    if (cells[y][x].segmentState == nullptr) {
        return;
    }

    SegmentState* segmentState = cells[y][x].segmentState;
    
    if (doubleDamage) {
        *segmentState = SegmentState::destroyed;
        doubleDamage = false;
        return;
    }
    switch (*segmentState)
    {
        case SegmentState::intact:
            *segmentState = SegmentState::damaged;
            break;
        case SegmentState::damaged:
            *segmentState = SegmentState::destroyed;
            break;
        default:
            break;
    }
}
void GameField::attackCell(int x, int y) {

    attackCellWithoutVision(x, y);
    
    if (cells[y][x].segmentState == nullptr) {
        cells[y][x].cellState = CellState::empty;
    }
    else {
        cells[y][x].cellState = CellState::ship;
    }
}

std::vector<std::pair<int, int>> GameField::getOccupiedCells() {
    std::vector<std::pair<int, int>> occupiedSectors;
    for (int x = 0; x < width; ++x) {
        for (int y = 0; y < height; ++y) {
            if (!isCellEmpty(x, y) && *cells[y][x].segmentState != SegmentState::destroyed) {
                occupiedSectors.emplace_back(x, y);
            }
        }
    }

    return occupiedSectors;
}

void GameField::activateDoubleDamage() {
    doubleDamage = true;
}

SegmentState GameField::getSegmentState(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw OutOfBounds("Invalid cell coordinates");
    }
    return *cells[y][x].segmentState;
}

CellState GameField::getCellState(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw OutOfBounds("Invalid cell coordinates");
    }
    return cells[y][x].cellState;
}

void GameField::setCellState(int x, int y, CellState state) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw OutOfBounds("Invalid cell coordinates");
    }
    cells[y][x].cellState = state;  
}
bool GameField::isCellEmpty(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return true;
    }
    return cells[y][x].segmentState == nullptr;
}

void GameField::printFieldVision() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            switch (cells[y][x].cellState)
            {
            case CellState::unknown:
                std::cout << ".";
                break;
            case CellState::empty:
                std::cout << " ";
                break;
            case CellState::ship:
                switch (*cells[y][x].segmentState)
                {
                case SegmentState::intact:
                    std::cout << "2";
                    break;
                case SegmentState::damaged:
                    std::cout << "1";
                    break;
                case SegmentState::destroyed:
                    std::cout << "0";
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
        }
        std::cout << std::endl;
    }
}

void GameField::printField() {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (cells[y][x].segmentState == nullptr) {
                std::cout << ".";
                continue;
            }
            switch (*cells[y][x].segmentState) {
                case SegmentState::intact:
                    std::cout << "2";
                    break;
                case SegmentState::damaged:
                    std::cout << "1";
                    break;
                case SegmentState::destroyed:
                    std::cout << "0";
                    break;
                default:
                    break;
            }
        }
        std::cout << std::endl;
    }
}

std::pair<int, int> GameField::getSize() {
    return std::make_pair(width, height);
}