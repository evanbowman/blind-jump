//
//  dasher.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 2/11/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef dasher_hpp
#define dasher_hpp

#include <stdio.h>
#include "enemyParent.hpp"
#include "effectsController.hpp"

class DasherBlur {
public:
    DasherBlur(sf::Sprite*, float, float);
    sf::Sprite* getSprite();
    bool getKillFlag();
    float xInit;
    float yInit;
    sf::Sprite spr;
    bool killflag;
};

class Dasher : public EnemyParent {
public:
    Dasher(sf::Sprite*);
    sf::Sprite* getSprite();
    sf::Sprite* getShadow();
    void update(float, float, std::vector<wall>, effectsController&, FontController&, sf::Time &);
    void softUpdate(float, float);
    std::vector<DasherBlur>* getBlurEffects();
    void checkBulletCollision(effectsController&, FontController&);
    bool shakeReady();
    bool dying();
    bool scrapReady();
    bool colored();
    
private:
    float health;
    sf::Sprite sprs[21];
    unsigned short dashCnt;
    bool isDashing;
    unsigned char frameIndex;
    unsigned int timer;
    float hspeed;
    float vspeed;
    unsigned char blurCountDown;
    std::vector<DasherBlur> blurEffects;
    bool checkWallCollision(std::vector<wall> , float);
    bool deathSeq;
};

#endif /* dasher_hpp */
