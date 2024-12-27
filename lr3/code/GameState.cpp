#include "GameState.h"
#include <iostream>
#include <sstream>

std::string GameState::serializeField(std::shared_ptr<GameField> field) const {
    std::stringstream os;
    std::pair<int, int> size = field->getSize();
    int length = 0;
    int dx, dy;
    std::vector<std::vector<int>> segments;
    for (int i = 0; i < size.second; i++) {
        for (int j = 0; j < size.first; j++) {

            switch (field->getCellState(j, i))
            {
            case (CellState::empty):
                os << "1 ";
                break;
            case (CellState::ship):
                os << "2 ";
                break;
            case (CellState::unknown):
                os << "0 ";
                break;
            default:
                os << "3 ";
                break;
            }

            if (!field->isCellEmpty(j, i)) {
                if (!field->isCellEmpty(j - 1, i) || !field->isCellEmpty(j, i - 1)) {
                    continue;
                }
                segments.push_back({j, i});
                length = 0;
                dx = !field->isCellEmpty(j + 1, i) ? 1 : 0;
                dy = !field->isCellEmpty(j, i + 1) ? 1 : 0;

                if (dx == 0 && dy == 0) {
                    dx = 1;
                }

                while (!field->isCellEmpty(j + dx * length, i + dy * length)) {
                    switch(field->getSegmentState(j + dx * length, i + dy * length)) {
                        case (SegmentState::destroyed):
                            segments.back().push_back(0);
                            break;
                        case (SegmentState::damaged):
                            segments.back().push_back(1);
                            break;
                        case (SegmentState::intact):
                            segments.back().push_back(2);
                            break;
                        default:
                            break;
                    }
                    length++;
                }

                segments.back().push_back(dy);
            }
        }
        os << std::endl;
    }

    os << segments.size() << std::endl;

    for (int i = 0; i < segments.size(); i++) {
        os << segments[i].size() - 3 << " ";
        for (int j = 0; j < segments[i].size(); j++) {
            os << segments[i][j] << " ";
        }
        os << std::endl;
    }

    return os.str();
}

std::string GameState::serializeSkills() const {
    std::stringstream os;
    int count = skillManager->getSkillsCount();
    os << count << " ";

    for (int i = 0; i < count; i++) {
        os << skillManager->getSkillIndex(i) << " ";
    }

    os << std::endl;

    return os.str();
}

std::ostream& operator<<(std::ostream& os, const GameState& gameState) {
    os << gameState.roundCount << std::endl;
    std::pair<int, int> size = gameState.playerField->getSize();
    os << size.first << " " << size.second << std::endl;

    os << gameState.serializeField(gameState.playerField);

    os << gameState.serializeSkills();

    os << gameState.serializeField(gameState.enemyField);

    return os;
}

std::istream& operator>>(std::istream& is, GameState& gameState) {

    GameState newGameState;
    int roundCount;
    int width, height;

    if (!(is >> roundCount >> width >> height) || roundCount <= 0 || width <= 0 || height <= 0) {
        throw std::invalid_argument("Invalid width or height");
    };
    newGameState.roundCount = roundCount;

    newGameState.playerField = std::make_shared<GameField>(width, height);
    int cellState;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (!(is >> cellState) || cellState < 0 || cellState > 2) {
                throw std::invalid_argument("Invalid player field input");
            };
            newGameState.playerField->setCellState(j, i, static_cast<CellState>(cellState));
        }
    }

    int shipCount;
    if (!(is >> shipCount) || shipCount < 0) {
        throw std::invalid_argument("Invalid player ship count");
    };

    newGameState.playerShips = std::make_shared<ShipManager>();

    std::pair<int, int> shipPosition;
    int shipLength;
    int shipDirection;
    int segmentState;

    for (int i = 0; i < shipCount; i++) {
        if (!(is >> shipLength >> shipPosition.first >> shipPosition.second) || shipLength <= 0 || shipPosition.first < 0 || shipPosition.second < 0) {
            throw std::invalid_argument("Invalid player ship input");
        };
        try {
            newGameState.playerShips->addShip(shipLength);
            for (int j = 0; j < shipLength; j++) {
                if (!(is >> segmentState) || segmentState < 0 || segmentState > 2) {
                    std::cout << "segmentState: " << segmentState << std::endl;
                    throw std::invalid_argument("Invalid player ship input");
                }

                newGameState.playerShips->getShip(i)->setSegmentState(j, static_cast<SegmentState>(segmentState));
            }
            if (!(is >> shipDirection) || shipDirection < 0 || shipDirection > 1) {
                throw std::invalid_argument("Invalid player ship input");
            }
            newGameState.playerField->placeShip(*newGameState.playerShips->getShip(i), shipPosition.first, shipPosition.second, static_cast<Direction>(shipDirection));
        }
        catch (std::invalid_argument& e) {
            throw std::invalid_argument("Invalid player ship input: " + std::string(e.what()));
        }
    }

    int skillCount;
    if (!(is >> skillCount) || skillCount < 0) {
        throw std::invalid_argument("Invalid skill count");
    };

    newGameState.skillManager = std::make_shared<SkillManager>();
    newGameState.skillManager->clear();

    int skillIndex;
    for (int i = 0; i < skillCount; i++) {
        if (!(is >> skillIndex) || skillIndex < 0) {
            throw std::invalid_argument("Invalid skill index");
        };
        newGameState.skillManager->addSkill(skillIndex);
    }

    newGameState.enemyField = std::make_shared<GameField>(width, height);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (!(is >> cellState) || cellState < 0 || cellState > 2) {
                throw std::invalid_argument("Invalid enemy field input");
            };
            newGameState.enemyField->setCellState(j, i, static_cast<CellState>(cellState));
        }
    }

    if (!(is >> shipCount) || shipCount < 0) {
        throw std::invalid_argument("Invalid enemy ship count");
    };

    newGameState.enemyShips = std::make_shared<ShipManager>();

    for (int i = 0; i < shipCount; i++) {
        if (!(is >> shipLength >> shipPosition.first >> shipPosition.second) || shipLength <= 0 || shipPosition.first < 0 || shipPosition.second < 0) {
            throw std::invalid_argument("Invalid enemy ship input");
        };

        try {
            newGameState.enemyShips->addShip(shipLength);
            for (int j = 0; j < shipLength; j++) {
                if (!(is >> segmentState) || segmentState < 0 || segmentState > 2) {
                    throw std::invalid_argument("Invalid enemy ship input");
                }
                newGameState.enemyShips->getShip(i)->setSegmentState(j, static_cast<SegmentState>(segmentState));
            }
            if (!(is >> shipDirection) || shipDirection < 0 || shipDirection > 1) {
                throw std::invalid_argument("Invalid enemy ship input");
            }
            newGameState.enemyField->placeShip(*newGameState.enemyShips->getShip(i), shipPosition.first, shipPosition.second, static_cast<Direction>(shipDirection));
        }
        catch (std::invalid_argument& e) {
            throw std::invalid_argument("Invalid enemy ship input: " + std::string(e.what()));
        }
    }

    gameState.enemyField = std::move(newGameState.enemyField);
    gameState.playerField = std::move(newGameState.playerField);
    gameState.playerShips = std::move(newGameState.playerShips);
    gameState.enemyShips = std::move(newGameState.enemyShips);
    gameState.skillManager = std::move(newGameState.skillManager);
    gameState.roundCount = newGameState.roundCount;

    return is;
}