//
//  mapTower.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 11/7/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef Teleporter_hpp
#define Teleporter_hpp

#include <stdio.h>
#include "detailParent.hpp"
#include "effectsController.hpp"

class Teleporter : public detailParent {
public:
    Teleporter(float, float, sf::Sprite*, sf::Sprite, int, float, float);
    sf::Sprite* getShadow();
    bool smokeReady();
    sf::Sprite* getSprite();
    void update(float, float, sf::Time &);
    sf::Sprite glowSprite;
    sf::Sprite* getGlow();
    
private:
    unsigned int smokeTimer;
    sf::Sprite TeleporterSprites[2];
};

#endif /* mapTower_hpp */
