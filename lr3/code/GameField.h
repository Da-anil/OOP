#pragma once
#include <vector>
#include "Ship.h"

enum class CellState {unknown = 0, empty = 1, ship = 2};

struct Cell {
    CellState cellState;
    SegmentState* segmentState;
};

class GameField {
    private:
        int width;
        int height;
        std::vector<std::vector<Cell>> cells;
        bool doubleDamage = false;
    public:
        GameField(int width, int height);
        GameField(const GameField& other);
        GameField& operator=(const GameField& other);
        GameField(GameField&& other);
        GameField& operator=(GameField&& other);

        void placeShip(Ship& ship, int x, int y, Direction direction);
        void attackCellWithoutVision(int x, int y);
        void attackCell(int x, int y);
        std::vector<std::pair<int, int>> getOccupiedCells();
        void activateDoubleDamage();

        SegmentState getSegmentState(int x, int y);
        CellState getCellState(int x, int y);
        void setCellState(int x, int y, CellState state);
        bool isCellEmpty(int x, int y);

        std::pair<int, int> getSize();
        
        void printFieldVision();
        void printField();
};