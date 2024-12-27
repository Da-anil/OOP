#include <memory>
#include "GameField.h"
#include "ShipManager.h"
#include "SkillManager.h"

class GameState {
    private:
        std::string serializeSkills() const;
        std::string serializeField(std::shared_ptr<GameField> field) const;
    public:
        GameState() = default;

        int roundCount;
        std::shared_ptr<GameField> playerField, enemyField;
        std::shared_ptr<ShipManager> playerShips, enemyShips;
        std::shared_ptr<SkillManager> skillManager;

        friend std::istream& operator>>(std::istream& is, GameState& gameState);
        friend std::ostream& operator<<(std::ostream& os, const GameState& gameState);
};