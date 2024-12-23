#include <random>
#include <vector>
#include <algorithm>
#include <iostream>
#include "CustomExceptions.h"
#include "SkillManager.h"
#include "Barrage.h"
#include "DoubleDamage.h"
#include "Scanner.h"

void SkillManager::initializeSkills() {
    skillsCopy.push_back(std::make_shared<Barrage>());
    skillsCopy.push_back(std::make_shared<DoubleDamage>());
    skillsCopy.push_back(std::make_shared<Scanner>());
}

SkillManager::SkillManager() {
    initializeSkills();

    skills = skillsCopy;

    std::random_device rd;
    gen = std::mt19937(rd());
    dis = std::uniform_int_distribution<>(0,  skillsCopy.size() - 1);
    std::shuffle(skills.begin(), skills.end(), gen);
}

void SkillManager::addRandomSkill() {
    int index = dis(gen);
    skills.push_back(skillsCopy[index]);
}

void SkillManager::useSkill(GameField& field) {
    if (skills.size() == 0) {
        throw NoSkillAvailable("No skills available");
    }
    skills[0]->use(field);
    
    skills.erase(skills.begin(), skills.begin() + 1);
}

void SkillManager::printSkills() {
    if (skills.size() == 0) {
        std::cout << "No skills available" << std::endl;
        return;
    }
    std::cout << skills[0]->getName();
    for (int i = 1; i < skills.size(); i++) {
        std::cout << ", " << skills[i]->getName();
    }
    std::cout << std::endl;
}

void SkillManager::addSkill(int index) {
    skills.push_back(skillsCopy[index]);
}

int SkillManager::getSkillIndex(int index) {
    if (index < 0 || index >= skills.size()) {
        throw NoSkillAvailable("Invalid skill index");
    }
    for (int i = 0; i < skillsCopy.size(); i++) {
        if (skillsCopy[i] == skills[index]) {
            return i;
        }
    }
    return -1;
}
int SkillManager::getSkillsCount() {
    return skills.size();
}

void SkillManager::clear() {
    skills.clear();
}