//
//  scoot.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 1/21/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#ifndef scoot_hpp
#define scoot_hpp

#include <stdio.h>
#include "enemyParent.hpp"
#include <vector>
#include "wall.hpp"
#include "effectsController.hpp"


class Scoot : public EnemyParent {
public:
    // This calls the parent constructor, which initializes common values like initial position
    Scoot(sf::Sprite*);
    // A function to update all of the enemy's values
    void update(float, float, std::vector<wall>, effectsController&, FontController&, sf::Time &);
    sf::Sprite* getSprite();
    sf::Sprite* getShadow();
    void softUpdate(float, float);
    void checkBulletCollision(effectsController& ef, FontController&);
    void randDir();
    bool colored();
    
private:
    sf::Sprite sprites[3];
    float speedScale;
    unsigned int frameTimer;
    float hSpeed;
    float vSpeed;
    unsigned int changeDirTimer;
    unsigned int shotCountdownTimer;
};

#endif /* scoot_hpp */
