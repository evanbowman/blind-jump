//
//  gun.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/13/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#include "gun.hpp"
#include <ResourcePath.hpp>
#include "bulletType1.hpp"

sf::Sprite* decodeDirIndex(sf::Sprite* gunSprite, char playerSpriteIndex, int timeout) {
    switch (playerSpriteIndex) {
        case 0:
            if (timeout < 97 && timeout > 2) {
                return &gunSprite[0];
            }
            else {
                return &gunSprite[3];
            }
            break;
        case 2:
            if (timeout < 97 && timeout > 2) {
                return &gunSprite[2];
            }
            else {
                return &gunSprite[5];
            }
            break;
        case 3:
            if (timeout < 97 && timeout > 2) {
                return &gunSprite[1];
            }
            else {
                return &gunSprite[4];
            }
            break;
        case 4:
            if (timeout < 97 && timeout > 2) {
                return &gunSprite[0];
            }
            else {
                return &gunSprite[3];
            }
            break;
        case 6:
            if (timeout < 97 && timeout > 2) {
                return &gunSprite[2];
            }
            else {
                return &gunSprite[5];
            }
            break;
        case 7:
            if (timeout < 97 && timeout > 2) {
                return &gunSprite[1];
            }
            else {
                return &gunSprite[4];
            }
            break;
        default:
            if (timeout < 97 && timeout > 2) {
                return &gunSprite[0];
            }
            break;
    }
    return &gunSprite[0];
}

gun::gun() {
    timeout = 0;
    bulletTimer = 10;
    sprIndex = 0;
    xPos = 0;
    yPos = 0;
    selectedGun = 1;
    
    //First load all of the sprites
    const std::string fileExts[6] = {"gunDown.png", "gunRight.png", "gunLeft.png", "gunDown2.png", "gunRight2.png", "gunLeft2.png"};
    for (int i = 0; i < 6; i++) {
        gunTexture[i].loadFromFile(resourcePath() + fileExts[i]);
        gunSprite[i].setTexture(gunTexture[i]);
        
        heavyGunTexture[i].loadFromFile(resourcePath() + "heavyBlasterSheet.png", sf::IntRect(i * 11, 0, 11, 12));
        heavyGunSprite[i].setTexture(heavyGunTexture[i]);
        
        splitterTexture[i].loadFromFile(resourcePath() + "splitterSheet.png", sf::IntRect(i * 11, 0, 11, 12));
        splitterSprite[i].setTexture(splitterTexture[i]);
        
        firstLightTexture[i].loadFromFile(resourcePath() + "firstLightSheet.png", sf::IntRect(i * 11, 0, 11, 12));
        firstLightSprite[i].setTexture(firstLightTexture[i]);
    }
}

//Return a sprite of the gun based on the direction that the player is facing
sf::Sprite* gun::getSprite(char playerSpriteIndex) {
    switch (selectedGun) {
        case 1:
            return decodeDirIndex(gunSprite, playerSpriteIndex, timeout);
            break;
            
        case 2:
            return decodeDirIndex(splitterSprite, playerSpriteIndex, timeout);
            break;
            
        case 3:
            return decodeDirIndex(heavyGunSprite, playerSpriteIndex, timeout);
            break;
            
        case 6:
            return decodeDirIndex(firstLightSprite, playerSpriteIndex, timeout);
            break;
            
        default:
            // Default, just return the starting weapon image
            return decodeDirIndex(gunSprite, playerSpriteIndex, timeout);
            break;
    }
}

//A function to see whether the gun has timed out yet (if it reaches a timeout state it doesn't draw to the screen)
int gun::getTimeout() {
    if (timeout > 0) {
        timeout--;
    }
    return timeout;
}

//This updates the effects vector that holds all of the shots and hit animations
void gun::updateShotVector(char playerSpriteIndex, effectsController& ef, float xOffset, float yOffset, userInterface& UI, InputController* pInput, SoundController& sounds, int playerState) {
    sprIndex = playerSpriteIndex;
    if (bulletTimer == 0 && pInput->xPressed() && timeout < 95 && playerState != 0) {
        if (sprIndex == 0 || sprIndex == 4) {  //If the gun sprite is up or down, construct a bullet with a corresponding sprite
            ef.addBullet(0, playerSpriteIndex, xPos - xOffset, yPos - yOffset - 10);
            sounds.playEffect(1);
        }
        else if (sprIndex == 1 || sprIndex == 5) {
            ef.addBullet(0, playerSpriteIndex, xPos - xOffset + 3, yPos - yOffset - 14);
            sounds.playEffect(1);
        }
        
        else if (sprIndex == 2 || sprIndex == 6 || sprIndex == 3 || sprIndex == 7) {
            ef.addBullet(1, playerSpriteIndex, xPos - xOffset, yPos - yOffset - 10);
            sounds.playEffect(1);
        }
        
        bulletTimer += 1;
    }
    
    if (bulletTimer != 0 && playerState == 1) {
        if (++bulletTimer == 20) {  //If enough time has passed since the last shot, set the counter back down to shoot again
            bulletTimer = 0;
        }
    }
    
    if (playerState != 1) {
        timeout = 6;
        bulletTimer = 10;
    }
}

//A function to set the gun timout, once timeout hits 0 the player doesn't draw the gun sprites to the window anymore
void gun::setTimeout(int time) {
    timeout = time;
}

//The gun has a different position based on the player's sprite, because it's sprite changes when the player faces a different direction
void gun::setPosition(float x, float y) {
    gunSprite[2].setPosition(x + 2, y + 13);
    gunSprite[5].setPosition(x + 4, y + 13);
    gunSprite[1].setPosition(x + 19, y + 13);
    gunSprite[4].setPosition(x + 17, y + 13);
    gunSprite[0].setPosition(x + 12, y + 15);
    gunSprite[3].setPosition(x + 12, y + 15);
    
    xPos = x;
    yPos = y;
}

float gun::getXpos() {
    return xPos;
}

float gun::getYpos() {
    return yPos;
}
