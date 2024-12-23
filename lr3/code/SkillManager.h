#pragma once
#include "Skill.h"
#include <random>
#include <vector>
#include <memory>

class SkillManager {
    private:
        std::mt19937 gen;
        std::uniform_int_distribution<> dis;
        std::vector<std::shared_ptr<Skill>> skills;
        std::vector<std::shared_ptr<Skill>> skillsCopy;

        void initializeSkills();
    public:
        SkillManager();
        void addRandomSkill();
        void printSkills();
        void useSkill(GameField& field);
        void addSkill(int index);
        int getSkillIndex(int index);
        int getSkillsCount();
        void clear();
};