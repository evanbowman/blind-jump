//
//  heavyBot.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/10/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef heavyBot_hpp
#define heavyBot_hpp

#include <stdio.h>
#include "enemyParent.hpp"
#include "effectsController.hpp"
#include "fontController.hpp"
#include "aStar.hpp"

// Forward declaration for tilecontroller
class tileController;

class HeavyBot : public EnemyParent {
    
    enum class State { dormant, run, shoot, overheat };
    
private:
    sf::Sprite sprites[17];
    float currentDir;
    char frameIndex, frameRate, health;
    State state;
    bool runShootAnim;
    std::vector<aStrCoordinate> path;
    int recalc;
    short (*map)[61];
    aStrCoordinate previous;
    float shotDir;
    float shotLen;
    
public:
    HeavyBot(sf::Sprite*, short map[61][61]);
    void update(float, float, effectsController&, FontController&, tileController*);
    sf::Sprite* getSprite();
    sf::Sprite* getShadow();
    void checkBulletCollision(effectsController&, FontController&);
};

#endif /* heavyBot_hpp */
