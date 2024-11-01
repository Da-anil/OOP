#pragma once
#include <vector>
#include "Ship.h"

enum class CellState {unknown, empty, ship};

struct Cell {
    CellState cellState;
    SegmentState* segmentState;
};

class GameField {
    private:
        int width;
        int height;
        std::vector<std::vector<Cell>> cells;
    public:
        GameField(int width, int height);
        GameField(const GameField& other);
        GameField& operator=(const GameField& other);
        GameField(GameField&& other);
        GameField& operator=(GameField&& other);

        void placeShip(Ship& ship, int x, int y, Direction direction);
        void attackCell(int x, int y);
        void printField();
};