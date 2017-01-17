#include "enemyPlacementFn.hpp"
#include "Game.hpp"
#include <array>
#include <cmath>
#include <stdio.h>

void initEnemies(Game * gm) {
    enum EnemyId {
	Scoot, Critter, Dasher, Turret
    };
    constexpr static std::array<int, 4> targetLevel = {{
        4 /*Scoot*/, 5 /*Critter*/, 20 /*Dasher*/, 28 /*Turrets*/
    }};
    int currentLevel = gm->getLevel();
    enemyController & enemies = gm->getEnemyController();
    tileController & tiles = gm->getTileController();
    std::vector<std::pair<int, int>> enemySelectVec;
    if (currentLevel >= 1) {
        enemySelectVec.emplace_back(1, std::abs(currentLevel - targetLevel[0]));
        enemySelectVec.emplace_back(1, std::abs(currentLevel - targetLevel[1]));
        if (currentLevel >= 2) {
            enemySelectVec.emplace_back(2, currentLevel - targetLevel[2]);
            if (currentLevel >= 4) {
                enemySelectVec.emplace_back(3, currentLevel - targetLevel[3]);
            }
        }
    }
    size_t enemyVecLen = enemySelectVec.size();
    // Collect enemy weight terms under a variable and init to 0
    int collector = 0;
    int diff;
    std::vector<int> intervals(enemyVecLen);
    // First loop through all enemies and update their probability values based
    // on current level
    for (size_t i = 0; i < enemyVecLen; i++) {
        // Set the weight to 100 divided by the difference between the current
        // level and the ideal level
        // Max function to prevent divide by 0
        diff = (100 + currentLevel) /
               std::max(abs(currentLevel - targetLevel[i]), 1);
        enemySelectVec[i].second = diff;
        collector += diff;
        intervals[i] = collector;
    }
    int iters = 2 + pow(currentLevel, 1.1f);
    if (iters > 15) {
        iters = 15;
    }
    std::array<unsigned, 4> numPlaced = {};
    for (int i = 0; i < iters; i++) {
        // Generate a random number on the range of 0 to the sum of all enemy
        // weights
        int select = rng::random(std::max(collector, 1));
        // Find the interval that the selected value falls into in intervals[]
        int selectedIndex = 0;
        for (size_t i = 0; i < enemyVecLen; i++) {
            if (i == 0) {
                if (select < intervals[0]) {
                    selectedIndex = 0;
                    break;
                }
            } else {
                if (select < intervals[i]) {
                    selectedIndex = static_cast<int>(i);
                    break;
                }
            }
        }
        // Now place enemies based on the selected index
        switch (selectedIndex) {
        case Scoot:
            enemies.addScoot(&tiles);
            break;

        case Critter:
            enemies.addCritter(&tiles);
            break;

        case Dasher: {
            static const unsigned maxDashers(5);
            if (numPlaced[Dasher] < maxDashers) {
                enemies.addDasher(&tiles);
                ++numPlaced[Dasher];
            }
            else {
                --i;
            }
            break;
        }

        case Turret: {
            static const unsigned maxTurrets(3);
            if (numPlaced[Turret] < maxTurrets) {
                enemies.addTurret(&tiles);
                ++numPlaced[Turret];
            }
            else {
                --i;
            }
            break;
        }

        default:
            break;
        }
    }
}
