//
//  player.cpp
//  BlindJump
//
//  Created by Evan Bowman on 10/9/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//
/*
 Take note of the sprite indeces:
 0: Face down
 1: Face up
 2: Face left
 3: Face right
 4: Walk down
 5: Walk up
 6: Walk left
 7: Walk right
 8: Death
 */
//The code in this section looks long, but it's mostly importing textures and repeated condition checking that cannot easily be looped.

#include "player.hpp"
#include "ResourcePath.hpp"
#include "playerAnimationFunctions.hpp"
#include <cmath>
#include "playerCollisionFunctions.hpp"
#include "wall.hpp"
#include <tuple>

Player::Player() {
    health = 4;
    imageIndex = 0;
    spriteIndex = 0;
    posX = 0;
    posY = 0;
    active = 1;
    visible = true;
    speed = 2.2;
    worldOffsetX = 0;
    worldOffsetY = 0;
    animationCounter = 6;
    leftPrevious = (sf::Keyboard::isKeyPressed(sf::Keyboard::Left));
    rightPrevious = (sf::Keyboard::isKeyPressed(sf::Keyboard::Right));
    upPrevious = (sf::Keyboard::isKeyPressed(sf::Keyboard::Up));
    downPrevious = (sf::Keyboard::isKeyPressed(sf::Keyboard::Down));
    weapon.setPosition(posX, posY);
    CollisionLeft = 0;
    CollisionRight = 0;
    slowSpeed = 1.5;
    previousCheckOffsetX = 0;
    previousCheckOffsetY = 0;
    sortCounter = 40;
    scrShakeState = 0;
    dodging = false;
    dodgeTimer = 4;
    state = NOMINAL;
    gotHeart = false;
    gotCoin = false;
    redTimer = 10;
    
    hurtCounter = 30;
    canhurt = true;
    
    if (!shadowTexture.loadFromFile(resourcePath() + "player_shadow.png")) {
        //return EXIT_FAILURE;
    }
    shadowSprite.setTexture(shadowTexture);
    shadowSprite.setPosition(posX + 7, posY + 24);
    //First load all of the textures from files, and apply them to corresponging sprite objects
    const std::string fileExt1[6] = {"player_face_down.png", "walk_down1.png", "walk_down2.png", "walk_down4.png", "walk_down5.png", "player_still_down.png"};
    const std::string fileExt2[6] = {"player_face_up.png", "walk_up3.png", "walk_up4.png", "walk_up1.png", "walk_up2.png", "player_still_up.png"};
    const std::string fileExt3[7] = {"player_face_left.png", "walk_left1.png", "walk_left2.png", "walk_left3.png", "walk_left4.png", "walk_left5.png", "player_still_left.png"};
    const std::string fileExt4[7] = {"player_face_right.png", "walk_right1.png", "walk_right2.png", "walk_right3.png", "walk_right4.png", "walk_right5.png", "player_still_right.png"};

    for (int i = 0; i < 12; i++) {
        dashTexture[i].loadFromFile(resourcePath() + "playerDashSheet.png", sf::IntRect(i * 32, 0, 32, 33));
        dashSprites[i].setTexture(dashTexture[i]);
        dashSprites[i].setOrigin(0, 1);
    }
    
    for (int i = 0; i < 6; i++) {
        if (!textureDown[i].loadFromFile(resourcePath() + fileExt1[i])) {
            //return EXIT_FAILURE;
        }
        spriteDown[i].setTexture(textureDown[i]);
        spriteDown[i].setPosition(posX, posY);
    }
    for (int i = 0; i < 6; i++) {
        if (!textureUp[i].loadFromFile(resourcePath() + fileExt2[i])) {
            //return EXIT_FAILURE;
        }
        spriteUp[i].setTexture(textureUp[i]);
        spriteUp[i].setPosition(posX, posY);
    }
    
    for (int i = 0; i < 7; i++) {
        if (!textureLeft[i].loadFromFile(resourcePath() + fileExt3[i])) {
            //return EXIT_FAILURE;
        }
        spriteLeft[i].setTexture(textureLeft[i]);
        spriteLeft[i].setPosition(posX, posY);
    }
    for (int i = 0; i < 7; i++) {
        if (!textureRight[i].loadFromFile(resourcePath() + fileExt4[i])) {
            //
        }
        spriteRight[i].setTexture(textureRight[i]);
        spriteRight[i].setPosition(posX, posY);
    }
    
    // Load the death animation textures and apply them to sprites
    // You can tell I added this much later because I'm using more advanced functions from the sf namespace to load everything from a sheet
    for (int i = 0; i < 11; i++) {
        deathTextures[i].loadFromFile(resourcePath() + "player_death_animation.png", sf::IntRect(i * 40, 0, 40, 38));
        deathSprites[i].setTexture(deathTextures[i]);
    }
}

void Player::setPosition(float X, float Y) {
    posX = X;
    posY = Y;
    int i;
    for (i = 0; i < 6; i++) {
        spriteDown[i].setPosition(posX, posY);
        spriteUp[i].setPosition(posX, posY);
        spriteLeft[i].setPosition(posX, posY);
        spriteRight[i].setPosition(posX, posY);
        deathSprites[i].setPosition(posX - 13, posY - 1);
    }
    for (i = 6; i < 11; i++) {
        deathSprites[i].setPosition(posX - 13, posY - 1);
    }
    spriteLeft[6].setPosition(posX, posY);
    spriteRight[6].setPosition(posX, posY);
    shadowSprite.setPosition(posX + 7, posY + 24);
    weapon.setPosition(posX, posY);
    for (int i = 0; i < 12; i++) {
        dashSprites[i].setPosition(posX, posY);
    }
}

float Player::getPosX() const {
    return posX;
}

float Player::getPosY() const {
    return posY;
}

//The following code gets repeated several times, so I gave it its own function
inline void compareSpriteIndex(char& spriteIndex) {
    switch (spriteIndex) {
        case 4: spriteIndex = 0;
            break;
        case 5: spriteIndex = 1;
            break;
        case 6: spriteIndex = 2;
            break;
        case 7: spriteIndex = 3;
            break;
        default: //spriteIndex = 0;
            break;
    }
}

//This function updates the player's sprite index, resets the animation counter, and if the collision state is low, adjusts the world offset to move the player
inline void updateWorldOffset(char& spriteIndex, int& animationCounter, bool collisionState, char externalNum, float& offset, float speed) {
    if (spriteIndex != externalNum) {
        spriteIndex = externalNum;
        animationCounter = 10;
    }
    if (collisionState == 0) {
        offset += speed;
    }
}

//Sets imageIndex and spriteIndex based on keyboard button presses, and also controls movement
//Add conditions for collisions later
void Player::drawController(InputController* pInput, effectsController& ef) {
    
    // If the player has no health and the death sequence isn't running, start it
    if (health == 0 && !deathSeq) {
        deathSeq = true;
        state = NOMINAL;
        spriteIndex = 8;
        imageIndex = 0;
        animationCounter = 6;
    }
    bool left, right, up, down, x, z;
    
    z = pInput->zPressed();
    x = pInput->xPressed();
    // If the player isn't in dodge mode, get left, right, etc from the input controller
    if (state == NOMINAL) {
        left = pInput->leftPressed();
        right = pInput->rightPressed();
        up = pInput->upPressed();
        down = pInput->downPressed();
    }
    // If the player is dodging, continue in the same direction regardless of button press, simply retrieve the stored state from the previous button press
    else {
        left = leftPrevious;
        right = rightPrevious;
        up = upPrevious;
        down = downPrevious;
    }
    
    if (active && !deathSeq) {
    if (!x && state == NOMINAL) {      //Holding the x key strafes the player and changes the animation, so account for that condition
        if (up) {
            if (!down && !left && !right && spriteIndex != 5)  {
                spriteIndex = 5;
                //imageIndex = 0;
                animationCounter = 6;
            }
            
            if (CollisionUp == 0) {
                if (left || right) {
                    worldOffsetY += speed * 0.85;
                }
                
                else {
                    worldOffsetY += speed;
                }
            }
        }
        
        if (down) {
            if (!up && !left && !right && spriteIndex != 4) {
                spriteIndex = 4;
                //imageIndex = 0;
                animationCounter = 6;
            }
            if (CollisionDown == 0) {
                if (right || left) {
                    worldOffsetY -= speed * 0.85;
                }
                
                else {
                    worldOffsetY -= speed;
                }
            }
        }
        
        if (right) {
            if (!left && !down && !up && spriteIndex != 7) {
                spriteIndex = 7;
                if (imageIndex > 5) {
                    imageIndex = 0;
                }
                animationCounter = 6;
            }
            if (CollisionRight == 0) {
                if (up || down) {
                    worldOffsetX -= speed * 0.85;
                }
                
                else {
                    worldOffsetX -= speed;
                }
            }
        }
        
        if (left) {
            if (!right && !up && !down && spriteIndex != 6) {
                spriteIndex = 6;
                if (imageIndex > 5) {
                    imageIndex = 0;
                }
                animationCounter = 6;
            }
            if (CollisionLeft == 0) {
                if (up || down) {
                    worldOffsetX += speed * 0.85;
                }
                
                else {
                    worldOffsetX += speed;
                }
            }
        }
    }
    
    else if (x && state == NOMINAL) {
        //The user is holding the x key, so set the gun timeout to max value
        if (weapon.getTimeout() == 0) {
        weapon.setTimeout(100);
        }
        if (weapon.getTimeout() < 90 && weapon.getTimeout() > 0) {
            weapon.setTimeout(90);
        }
        //Now we want the player to stay facing the same direction and strafe while the user holds the x key, which requires a lot more condition checking
        
        //Regardless of which direction key(s) active, the player needs to face the direction it was facing when x was pressed
        if (spriteIndex == 0 || spriteIndex == 4) {
            if (down) {
                updateWorldOffset(spriteIndex, animationCounter, CollisionDown, 4, worldOffsetY, -slowSpeed);
            }
            
            if (up) {
                updateWorldOffset(spriteIndex, animationCounter, CollisionUp, 4, worldOffsetY, slowSpeed);
            }
            
            if (left) {
                updateWorldOffset(spriteIndex, animationCounter, CollisionLeft, 4, worldOffsetX, slowSpeed);
            }
            
            if (right) {
                updateWorldOffset(spriteIndex, animationCounter, CollisionRight, 4, worldOffsetX, -slowSpeed);
            }
        }
        if (spriteIndex == 1 || spriteIndex == 5) {
            if (down) {
                updateWorldOffset(spriteIndex, animationCounter, CollisionDown, 5, worldOffsetY, -slowSpeed);
            }
            
            if (up) {
                updateWorldOffset(spriteIndex, animationCounter, CollisionUp, 5, worldOffsetY, slowSpeed);
            }
            
            if (left) {
                updateWorldOffset(spriteIndex, animationCounter, CollisionLeft, 5, worldOffsetX, slowSpeed);
            }
            
            if (right) {
                updateWorldOffset(spriteIndex, animationCounter, CollisionRight, 5, worldOffsetX, -slowSpeed);
            }
        }
        if (spriteIndex == 2 || spriteIndex == 6) {
            if (down) {
                updateWorldOffset(spriteIndex, animationCounter, CollisionDown, 6, worldOffsetY, -slowSpeed);
            }
            
            if (up) {
                updateWorldOffset(spriteIndex, animationCounter, CollisionUp, 6, worldOffsetY, slowSpeed);
            }
            
            if (left) {
                updateWorldOffset(spriteIndex, animationCounter, CollisionLeft, 6, worldOffsetX, slowSpeed);
            }
            
            if (right) {
                updateWorldOffset(spriteIndex, animationCounter, CollisionRight, 6, worldOffsetX, -slowSpeed);
            }
        }
        if (spriteIndex == 3 || spriteIndex == 7) {
            if (down) {
                updateWorldOffset(spriteIndex, animationCounter, CollisionDown, 7, worldOffsetY, -slowSpeed);
            }
            
            if (up) {
                updateWorldOffset(spriteIndex, animationCounter, CollisionUp, 7, worldOffsetY, slowSpeed);
            }
            
            if (left) {
                updateWorldOffset(spriteIndex, animationCounter, CollisionLeft, 7, worldOffsetX, slowSpeed);
            }
            
            if (right) {
                updateWorldOffset(spriteIndex, animationCounter, CollisionRight, 7, worldOffsetX, -slowSpeed);
            }
        }
        
        if (pInput->zPressed() && z != zprevious) {
            if (((spriteIndex == 6 && !left) || (spriteIndex == 7 && !right) || (spriteIndex == 4 && !down) || (spriteIndex == 5  && !up))) {
                state = PREP_DASH;
                if (spriteIndex == 7) {
                    if (up) {
                        if (left)
                            ef.addDodgeEffect(posX - worldOffsetX + 27, posY - worldOffsetY + 6, 45, 1);
                        //else
                            //
                    }
                    
                    else if (down) {
                        if (left)
                            ef.addDodgeEffect(posX - worldOffsetX - 4, posY - worldOffsetY + 16, -45, 1);
                    }
                    
                    else
                        ef.addDodgeEffect(posX - worldOffsetX + 9, posY - worldOffsetY + 5, 0, 1);
                }
                else if (spriteIndex == 6) {
                    if (up) {
                        if (right)
                            ef.addDodgeEffect(posX - worldOffsetX + 2, posY - worldOffsetY + 6, -45, -1);
                        //else
                            //
                    }
                    
                    else if (down) {
                        if (right)
                            ef.addDodgeEffect(posX - worldOffsetX  + 32, posY - worldOffsetY + 16, 45, -1);
                    }
                    
                    else
                        ef.addDodgeEffect(posX - worldOffsetX + 23, posY - worldOffsetY + 5, 0, -1);
                }
                
                else if (spriteIndex == 4) {
                    if (left) {
                        if (up)
                            ef.addDodgeEffect(posX - worldOffsetX + 29, posY - worldOffsetY + 6, 45, 1);
                        else
                            ef.addDodgeEffect(posX - worldOffsetX + 9, posY - worldOffsetY + 5, 0, 1);
                    }
                    
                    else if (right) {
                        if (up)
                            ef.addDodgeEffect(posX - worldOffsetX + 2, posY - worldOffsetY + 6, -45, -1);
                        
                        else
                            ef.addDodgeEffect(posX - worldOffsetX + 23, posY - worldOffsetY + 5, 0, -1);
                    }
                }
                
                else if (spriteIndex == 5) {
                    if (left) {
                        if (down)
                            ef.addDodgeEffect(posX - worldOffsetX - 4, posY - worldOffsetY + 16, -45, 1);
                        
                        else
                            ef.addDodgeEffect(posX - worldOffsetX + 9, posY - worldOffsetY + 5, 0, 1);
                    }
                    
                    else if (right) {
                        if (down)
                            ef.addDodgeEffect(posX - worldOffsetX  + 32, posY - worldOffsetY + 16, 45, -1);
                        
                        else
                            ef.addDodgeEffect(posX - worldOffsetX + 23, posY - worldOffsetY + 5, 0, -1);
                    }
                }
            }
        }
    }
        
        if (state == PREP_DASH) {
            if (--dodgeTimer == 0) {
                dodgeTimer = 5;
                state = DASHING;
            }
            if (left && !CollisionLeft) {
                worldOffsetX += 1;
            }
            if (right && !CollisionRight) {
                worldOffsetX -= 1;
            }
            if (up && !CollisionUp) {
                worldOffsetY += 1;
            }
            if (down && !CollisionDown) {
                worldOffsetY -= 1;
            }
        }
        
        else if (state == DASHING) {
            if (--dodgeTimer == 0) {
                state = COOLDOWN;
                dodgeTimer = 12;
            }
            if (left && !CollisionLeft) {
                if (up || down)
                    worldOffsetX += 5;
                else
                    worldOffsetX += 7;
            }
            if (right && !CollisionRight) {
                if (up || down)
                    worldOffsetX -= 5;
                else
                    worldOffsetX -= 7;
            }
            if (up && !CollisionUp) {
                if (left || right)
                    worldOffsetY += 5;
                else
                    worldOffsetY += 7;
            }
            if (down && !CollisionDown) {
                if (left || right)
                    worldOffsetY -= 5;
                else
                    worldOffsetY -= 7;
            }
        }
        
        else if (state == COOLDOWN) {
            if (--dodgeTimer == 0) {
                dodgeTimer = 3;
                state = NOMINAL;
                imageIndex = 4;
            }
            if (left && !CollisionLeft) {
                worldOffsetX += 1;
            }
            if (right && !CollisionRight) {
                worldOffsetX -= 1;
            }
            if (up && !CollisionUp) {
                worldOffsetY += 1;
            }
            if (down && !CollisionDown) {
                worldOffsetY -= 1;
            }
        }

    //Code making the player stand still after key releases
    if (!left && leftPrevious == 1) {
        if (!left && !right && !up && !down) {
            if (!x) {
                spriteIndex = 2;
                imageIndex = 0;
            }
            else if (x) {
                compareSpriteIndex(spriteIndex);
            }
        }
    }
    
    if (!right && rightPrevious == 1) {
        if (!left && !right && !up && !down) {
            if (!x) {
            spriteIndex = 3;
            imageIndex = 0;
            }
            else if (x) {
                compareSpriteIndex(spriteIndex);
            }
        }
    }
    
    if (!up && upPrevious == 1) {
        if (!left && !right && !up && !down) {
            if (!x) {
                spriteIndex = 1;
                imageIndex = 0;
            }
            else if (x) {
                compareSpriteIndex(spriteIndex);
            }
        }
    }
    
    if (!down && downPrevious == 1) {
        if (!left && !right && !up && !down) {
            if (!x) {
                spriteIndex = 0;
                imageIndex = 0;
            }
            else if (x) {
                compareSpriteIndex(spriteIndex);
            }
        }
    }
        
    }
    
    // Keep track of the previous key presses to the character can stop moving after a key release
    leftPrevious = left;
    rightPrevious = right;
    upPrevious = up;
    downPrevious = down;
    zprevious = z;
}

//This part of the code was getting called repeatedly, so I'll let the compiler do the copy-pasting for me
inline void updateVAnimCount(int& animationCounter, char& imageIndex, bool x) {
    //We don't want to go through a 10 frame animation 6 times a second, only go to the next frame when the animation counter reaches 0
    if (--animationCounter == 0) {
        if (imageIndex < 10) {
            imageIndex += 1;
        }
        if (imageIndex == 10) {
            imageIndex = 0;
        }
        if (!x) {
            animationCounter = 6;
        }
        else {
            animationCounter = 8;
        }
        if (imageIndex == 6) {
            animationCounter += 2;
        }
    }
}

inline void updateHAnimCount(int& animationCounter, char& imageIndex, bool x) {
    //We don't want to go through a 10 frame animation 6 times a second, only go to the next frame when the animation counter reaches 0
    if (--animationCounter == 0) {
        if (imageIndex < 10) {
            imageIndex += 1;
        }
        if (imageIndex == 6) {
            imageIndex = 0;
        }
        if (!x) {
            animationCounter = 6;
        }
        else {
            animationCounter = 8;
        }
    }
}

// Define a function to check for collisions with enemy shots
template<typename T>
bool checkShotCollision(std::vector<T>* shotVec, double playerXpos, double playerYpos) {
    // If the vector is not empty
    if (!shotVec->empty()) {
        // Loop through the vector and check whether the enemy shot objects are close to the player
        for (auto & element : *shotVec) {
            if (std::abs(playerXpos + 16 - element.getXpos()) < 8 && std::abs(playerYpos + 16 - element.getYpos()) < 8) {
                // Set a flag within the element that tells its controller to remove it from its vector
                element.setKillFlag();
                return true;
            }
        }
    }
    // Nothing hit the player, so return false
    return false;
}

//Returns the current sprite based on the values of imageIndex and spriteIndex
void Player::draw(std::vector<std::tuple<sf::Sprite, float, int>>& gameObjects, std::vector<std::tuple<sf::Sprite, float, int>>& gameShadows, tileController& tiles, effectsController& ef, detailController& details, SoundController& sounds, userInterface& UI, InputController* pInput, sf::RenderTexture& window, FontController& fonts, sf::Time& elapsedTime) {
    checkCollision(tiles, details);//, details);
    drawController(pInput, ef);
    std::tuple<sf::Sprite, float, int> tPlayer, tGun, tShadow;
    
    std::get<1>(tPlayer) = posY;
    
    speed = 2.2 * (elapsedTime.asMilliseconds() / 17.6);
    slowSpeed = 1.5 * (elapsedTime.asMilliseconds() / 17.6);
    
    // If the death sequence isn't running, draw the player's shadow
    if (!deathSeq) {
        std::get<0>(tShadow) = shadowSprite;
        gameShadows.push_back(tShadow);
    }
    // Allow the player's weapon to push created instances to the effects controller
    weapon.updateShotVector(spriteIndex, ef, worldOffsetX, worldOffsetY, UI, pInput, sounds, state);
    scrShakeState = false;
    
    // First check for collisions with enemy shot objects, as long as the death sequence isn't running
    if (checkShotCollision(ef.getEnemyShots(), posX, posY) && !deathSeq && canhurt) {
        // Decrement health
        health--;
        fonts.resetHPText();
        scrShakeState = true;
        canhurt = false;
    }
    
    if (checkShotCollision(ef.getTurretShots(), posX, posY) && !deathSeq && canhurt) {
        health--;
        fonts.resetHPText();
        scrShakeState = true;
        canhurt = false;
    }
    
    if (checkShotCollision(ef.getDasherShots(), posX, posY) && !deathSeq && canhurt) {
        health--;
        fonts.resetHPText();
        scrShakeState = true;
        canhurt = false;
    }
    
    // Don't bother doing all this if health is empty!
    if (health < fonts.getMaxHealth()) {
        std::vector<Powerup>* pHearts = ef.getHearts();
        for (auto & element : *pHearts) {
            if (fabsf(posX + 16 - element.getXpos()) < 8 && fabsf(posY + 4 - element.getYpos()) < 8) {
                health = fmin(fonts.getMaxHealth(), health + 1);
                element.setKillFlag(true);
                gotHeart = true;
                // Display the UI element for health text
                fonts.resetHPText();
            }
        }
    }
    
    std::vector<Powerup>* pCoins = ef.getCoins();
    for (auto & element : *pCoins) {
        if (fabsf(posX + 16 - element.getXpos()) < 8 && fabsf(posY + 4 - element.getYpos()) < 8) {
            element.setKillFlag(true);
            gotCoin = true;
            gotHeart = false;
        }
    }
    
    if (gotHeart) {
        std::get<2>(tPlayer) = 4;
        std::get<2>(tGun) = 4;
        if (--redTimer == 0) {
            redTimer = 10;
            ////float initDir = rand() % 120;
            ////ef.addPowerupParticle(posX, posY, initDir);
            ////ef.addPowerupParticle(posX, posY, initDir + 120);
            ////ef.addPowerupParticle(posX, posY, initDir + 240);
            gotHeart = false;
        }
    } else if (gotCoin) {
        std::get<2>(tPlayer) = 5;
        std::get<2>(tGun) = 5;
        if (--redTimer == 0) {
            gotCoin = 0;
            ////float initDir = rand() % 120;
            ////ef.addPowerupParticle(posX, posY, initDir);
            ////ef.addPowerupParticle(posX, posY, initDir + 120);
            ////ef.addPowerupParticle(posX, posY, initDir + 240);
            redTimer = 10;
        }
    }
    
    if (health < 0) {
        state = NOMINAL;
        health = 0;
    }
    
    if (!canhurt) {
        if (--hurtCounter == 0) {
            hurtCounter = 30;
            canhurt = true;
        }
        
        if (hurtCounter < 24 && hurtCounter > 18) {
            // Shade the player red
            std::get<2>(tPlayer) = 3;
            std::get<2>(tGun) = 3;
        }
        
        else if (hurtCounter >= 24 && hurtCounter != 30) {
            // Shade the player blue
            std::get<2>(tPlayer) = 1;
            std::get<2>(tGun) = 1;
        }
    }
    
    if (state == NOMINAL) {
        switch (spriteIndex) {
            // Common cases first!
            case 4:
                updateVAnimCount(animationCounter, imageIndex, pInput->xPressed());
                if (imageIndex == 4 || imageIndex == 8) {
                    sounds.playEffect(0);
                }
                std::get<0>(tPlayer) = spriteDown[verticalAnimationDecoder(imageIndex)];
                gameObjects.push_back(tPlayer);
                if (weapon.getTimeout() != 0) {
                    std::get<0>(tGun) = *weapon.getSprite(spriteIndex);
                    std::get<1>(tGun) = weapon.getYpos() + 2;
                    gameObjects.push_back(tGun);
                }
                break;
                
            case 5:
                updateVAnimCount(animationCounter, imageIndex, pInput->xPressed());
                if (imageIndex == 4 || imageIndex == 8) {
                    sounds.playEffect(0);
                }
                weapon.getTimeout();
                std::get<0>(tPlayer) = spriteUp[verticalAnimationDecoder(imageIndex)];
                gameObjects.push_back(tPlayer);
                break;
                
            case 6:
                if (weapon.getTimeout() != 0) {
                    std::get<0>(tGun) = *weapon.getSprite(spriteIndex);
                    std::get<1>(tGun) = weapon.getYpos() - 1;
                    gameObjects.push_back(tGun);
                }
                updateHAnimCount(animationCounter, imageIndex, pInput->xPressed());
                if (imageIndex == 1) {
                    sounds.playEffect(0);
                }
                std::get<0>(tPlayer) = spriteLeft[horizontalAnimationDecoder(imageIndex)];
                gameObjects.push_back(tPlayer);
                break;
                
            case 7:
                if (weapon.getTimeout() != 0) {
                    std::get<0>(tGun) = *weapon.getSprite(spriteIndex);
                    std::get<1>(tGun) = weapon.getYpos() - 1;
                    gameObjects.push_back(tGun);
                }
                updateHAnimCount(animationCounter, imageIndex, pInput->xPressed());
                if (imageIndex == 1) {
                    sounds.playEffect(0);
                }
                std::get<0>(tPlayer) = spriteRight[horizontalAnimationDecoder(imageIndex)];
                gameObjects.push_back(tPlayer);
                break;
            
            case 0:
                std::get<0>(tPlayer) = spriteDown[5];
                gameObjects.push_back(tPlayer);
                if (weapon.getTimeout() != 0) {
                    std::get<0>(tGun) = *weapon.getSprite(spriteIndex);
                    std::get<1>(tGun) = weapon.getYpos() + 2;
                    gameObjects.push_back(tGun);
                }
                break;
            
            case 1:
                std::get<0>(tPlayer) = spriteUp[5];
                gameObjects.push_back(tPlayer);
                weapon.getTimeout();
                break;
                
            case 2:
                if (weapon.getTimeout() != 0) {
                    std::get<0>(tGun) = *weapon.getSprite(spriteIndex);
                    std::get<1>(tGun) = weapon.getYpos() - 1;
                    gameObjects.push_back(tGun);
                }
                std::get<0>(tPlayer) = spriteLeft[6];
                gameObjects.push_back(tPlayer);
                break;
            
            case 3:
                if (weapon.getTimeout() != 0) {
                    std::get<0>(tGun) = *weapon.getSprite(spriteIndex);
                    std::get<1>(tGun) = weapon.getYpos() - 1;
                    gameObjects.push_back(tGun);
                }
                std::get<0>(tPlayer) = spriteRight[6];
                gameObjects.push_back(tPlayer);
                break;
                
            case 8:
                if (--animationCounter == 0) {
                    animationCounter = 4;
                    if (imageIndex < 9) {
                        imageIndex++;
                    }
                }
                std::get<0>(tPlayer) = deathSprites[imageIndex];
                gameObjects.push_back(tPlayer);
                break;
        }
    }
    else if (state == PREP_DASH) {
        if ((rightPrevious || upPrevious || downPrevious) && spriteIndex == 6) {
            if (weapon.getTimeout() != 0 && rightPrevious) {
                std::get<0>(tGun) = *weapon.getSprite(spriteIndex);
                std::get<1>(tGun) = weapon.getYpos() - 1;
                gameObjects.push_back(tGun);
            }
            std::get<0>(tPlayer) = dashSprites[0];
            gameObjects.push_back(tPlayer);
        }
        else if ((leftPrevious || upPrevious || downPrevious) && spriteIndex == 7) {
            if (weapon.getTimeout() != 0 && rightPrevious) {
                std::get<0>(tGun) = *weapon.getSprite(spriteIndex);
                std::get<1>(tGun) = weapon.getYpos() - 1;
                gameObjects.push_back(tGun);
            }
            std::get<0>(tPlayer) = dashSprites[2];
            gameObjects.push_back(tPlayer);
        }
        else if (spriteIndex == 4) {
            if (weapon.getTimeout() != 0) {
                sf::Sprite tempSpr = *weapon.getSprite(spriteIndex);
                tempSpr.setPosition(tempSpr.getPosition().x, tempSpr.getPosition().y - 1);
                std::get<0>(tGun) = tempSpr;
                std::get<1>(tGun) = weapon.getYpos() + 3;
                gameObjects.push_back(tGun);
            }
            std::get<0>(tPlayer) = dashSprites[6];
            gameObjects.push_back(tPlayer);
        }
        else if (spriteIndex == 5) {
            std::get<0>(tPlayer) = dashSprites[8];
            gameObjects.push_back(tPlayer);
        }
    }
    
    else if (state == DASHING || state == COOLDOWN) {
        if (rightPrevious && spriteIndex == 6) {
            if (weapon.getTimeout() != 0) {
                std::get<0>(tGun) = *weapon.getSprite(spriteIndex);
                std::get<1>(tGun) = weapon.getYpos() - 1;
                gameObjects.push_back(tGun);
            }
            std::get<0>(tPlayer) = dashSprites[1];
            gameObjects.push_back(tPlayer);
        }
        else if (leftPrevious && spriteIndex == 7) {
            if (weapon.getTimeout() != 0) {
                std::get<0>(tGun) = *weapon.getSprite(spriteIndex);
                std::get<1>(tGun) = weapon.getYpos() - 1;
                gameObjects.push_back(tGun);
            }
            std::get<0>(tPlayer) = dashSprites[3];
            gameObjects.push_back(tPlayer);
        }
        else if (upPrevious && spriteIndex == 6) {
            if (weapon.getTimeout() != 0) {
                std::get<0>(tGun) = *weapon.getSprite(spriteIndex);
                std::get<1>(tGun) = weapon.getYpos() - 1;
                gameObjects.push_back(tGun);
            }
            std::get<0>(tPlayer) = dashSprites[4];
            gameObjects.push_back(tPlayer);
        }
        
        else if (downPrevious && spriteIndex == 6) {
            std::get<0>(tPlayer) = dashSprites[11];
            gameObjects.push_back(tPlayer);
        }
        
        else if (downPrevious && spriteIndex == 7) {
            std::get<0>(tPlayer) = dashSprites[10];
            gameObjects.push_back(tPlayer);
        }
        
        else if (upPrevious && spriteIndex == 7) {
            if (weapon.getTimeout() != 0) {
                std::get<0>(tGun) = *weapon.getSprite(spriteIndex);
                std::get<1>(tGun) = weapon.getYpos() - 1;
                gameObjects.push_back(tGun);
            }
            std::get<0>(tPlayer) = dashSprites[5];
            gameObjects.push_back(tPlayer);
        }
        
        else if (spriteIndex == 4) {
            if (upPrevious) {
                if (weapon.getTimeout() != 0) {
                    sf::Sprite tempSpr = *weapon.getSprite(spriteIndex);
                    tempSpr.setPosition(tempSpr.getPosition().x, tempSpr.getPosition().y - 1);
                    std::get<0>(tGun) = tempSpr;
                    std::get<1>(tGun) = weapon.getYpos() + 2;
                    gameObjects.push_back(tGun);
                }
                std::get<0>(tPlayer) = dashSprites[7];
                gameObjects.push_back(tPlayer);
            }
            
            else if (leftPrevious) {
                if (weapon.getTimeout() != 0) {
                    sf::Sprite tempSpr = *weapon.getSprite(spriteIndex);
                    tempSpr.setPosition(tempSpr.getPosition().x, tempSpr.getPosition().y - 1);
                    std::get<0>(tGun) = tempSpr;
                    std::get<1>(tGun) = weapon.getYpos() + 2;
                    gameObjects.push_back(tGun);
                }
                std::get<0>(tPlayer) = dashSprites[5];
                gameObjects.push_back(tPlayer);
            }
            
            else if (rightPrevious) {
                if (weapon.getTimeout() != 0) {
                    sf::Sprite tempSpr = *weapon.getSprite(spriteIndex);
                    tempSpr.setPosition(tempSpr.getPosition().x, tempSpr.getPosition().y - 1);
                    std::get<0>(tGun) = tempSpr;
                    std::get<1>(tGun) = weapon.getYpos() + 2;
                    gameObjects.push_back(tGun);
                }
                std::get<0>(tPlayer) = dashSprites[4];
                gameObjects.push_back(tPlayer);
            }
        }
        
        else if (spriteIndex == 5) {
            if (downPrevious) {
                std::get<0>(tPlayer) = dashSprites[9];
                gameObjects.push_back(tPlayer);
            }
            
            else if (leftPrevious) {
                std::get<0>(tPlayer) = dashSprites[10];
                gameObjects.push_back(tPlayer);
            }
            
            else if (rightPrevious) {
                std::get<0>(tPlayer) = dashSprites[11];
                gameObjects.push_back(tPlayer);
            }
        }
    }
}

void Player::checkCollision(tileController& tiles, detailController& details) {
    // Re-initialize each of the collision variables each time to check the conditions again
    CollisionLeft = 0;
    CollisionRight = 0;
    CollisionUp = 0;
    CollisionDown = 0;
    
    checkCollisionWall(tiles.walls, CollisionDown, CollisionUp, CollisionRight, CollisionLeft, posY, posX);
    checkCollisionChest(details.getChests(), CollisionDown, CollisionUp, CollisionRight, CollisionLeft, posY, posX);
    checkCollisionTerminal(details.getTerms(), CollisionDown, CollisionUp, CollisionRight, CollisionLeft, posY, posX);
}

float Player::getWorldOffsetX() const {              // Accessor function to get the player's offset position relative to the overworld
    return worldOffsetX;
}

float Player::getWorldOffsetY() const {
    return worldOffsetY;
}

void Player::setWorldOffsetX(float x) {
    worldOffsetX = x;
}

void Player::setWorldOffsetY(float y) {
    worldOffsetY = y;
}

bool Player::isActive() {
    return active;
}

void Player::activate() {
    active = 1;
}

void Player::deActivate() {
    active = 0;
    spriteIndex = 0;
}

void Player::deActivateFaceUp() {
    active = false;
    spriteIndex = 1;
}

char Player::getSprIndex() const {
    return spriteIndex;
}

char Player::getHealth() const {
    return health;
}

bool Player::isdead() {
    return !deathSeq;
}

void Player::reset() {
    // Reinitialize player values to base values
    canhurt = 0;
    hurtCounter = 15;
    deathSeq = false;
    health = 4;
    spriteIndex = 0;
    canhurt = true;
}

void Player::fillHealth(char health) {
    this->health = health;
}
