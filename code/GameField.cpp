#include "GameField.h"
#include <stdexcept>
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

    if (x < 0 || x + length * dx >= width || y < 0 || y + length * dy >= height) {
        throw std::invalid_argument("Invalid ship placement");
    }

    int mn_x = std::max(x - 1, 0);
    int mx_x = std::min(x + length * dx + 1, width);
    int mn_y = std::max(y - 1, 0);
    int mx_y = std::min(y + length * dy + 1, height);

    for (int i = mn_y; i < mx_y; i++) {
        for (int j = mn_x; j < mx_x; j++) {
            if (cells[i][j].segmentState != nullptr) {
                throw std::invalid_argument("Invalid ship placement");
            }
        }
    }
    

    for (int i = 0; i < length; i++) {
        cells[y + i * dy][x + i * dx].segmentState = ship.getSegmentState(i);
    }
}

void GameField::attackCell(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        throw std::invalid_argument("Invalid cell coordinates");
    }
    if (cells[y][x].segmentState == nullptr) {
        cells[y][x].cellState = CellState::empty;
        return;
    }
    cells[y][x].cellState = CellState::ship;

    SegmentState* segmentState = cells[y][x].segmentState;
    
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