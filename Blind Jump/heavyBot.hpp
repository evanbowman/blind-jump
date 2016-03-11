//
//  heavyBot.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/10/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#ifndef heavyBot_hpp
#define heavyBot_hpp

#include <stdio.h>
#include "enemyParent.hpp"
#include "effectsController.hpp"
#include "fontController.hpp"
#include "aStar.hpp"

// Define states for the state machine
#define DORMANT 'd'
#define RUN 'r'
#define SHOOT 's'
#define OVERHEAT 'o'

// Forward declaration for tilecontroller
class tileController;

class HeavyBot : public EnemyParent {
private:
    sf::Sprite sprites[17];
    float currentDir;
    char frameIndex, frameRate, state;
    bool runShootAnim;
    std::vector<aStrCoordinate> path;
    int recalc;
    short (*map)[61];
    aStrCoordinate previous;
    
public:
    HeavyBot(sf::Sprite*, short map[61][61]);
    void update(float, float, effectsController&, FontController&, tileController*);
    sf::Sprite* getSprite();
    sf::Sprite* getShadow();
};

#endif /* heavyBot_hpp */
