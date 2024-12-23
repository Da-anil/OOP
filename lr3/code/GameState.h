#include <memory>
#include "GameField.h"
#include "ShipManager.h"
#include "SkillManager.h"

class GameState {
    public:
        GameState() = default;

        int roundCount; 
        std::unique_ptr<GameField> playerField, enemyField;
        std::unique_ptr<ShipManager> playerShips, enemyShips;
        std::unique_ptr<SkillManager> skillManager;

        friend std::istream& operator>>(std::istream& is, GameState& gameState);
        friend std::ostream& operator<<(std::ostream& os, const GameState& gameState);
};