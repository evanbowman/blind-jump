//
//  enemyParent.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 1/21/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef enemyParent_hpp
#define enemyParent_hpp

#include <stdio.h>
#include "sfml/graphics.hpp"
#include "wall.hpp"

class EnemyParent {
public:
    void setInitPosition(float, float);
    void setPosition(float, float);
    void setPlayerPos(float, float);
    bool getKillFlag() const;
    EnemyParent(sf::Sprite*);
    float getXinit() const;
    float getYinit() const;
    float getXpos() const;
    float getYpos() const;
    bool checkCollisionWall(std::vector<wall>, float);
    float xInit;
    float yInit;
    float xPos;
    float yPos;
    float playerPosX;
    float playerPosY;
    float xOffset;
    float yOffset;
    unsigned char frameIndex;
    bool killFlag;
    bool isColored;
    unsigned int colorTimer;
    float colorAmount;
    unsigned char health;
    bool colored();
    
};
#endif /* enemyParent_hpp */
