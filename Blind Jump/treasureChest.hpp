//
//  treasureChest.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 11/14/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#ifndef treasureChest_hpp
#define treasureChest_hpp

#include <stdio.h>
#include "detailParent.hpp"

class TreasureChest : public detailParent {
public:
    TreasureChest(float, float, sf::Sprite*, int, float, float, char);
    using detailParent::detailParent;
    sf::Sprite* getShadow();
    sf::Sprite* getSprite();
    void update(float, float, char);
    sf::Sprite chestSprites[7];
    float getZY();
    char getFrameIndex();
    char getItem();
    
private:
    bool animationIsRunning;
    char frameLength;
    char frameIndex;
    // Boolean to keep track of opened or closed
    bool isOpen;
    char item;
};
#endif /* treasureChest_hpp */
