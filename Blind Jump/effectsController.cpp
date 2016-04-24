//
//  effectsController.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/20/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#include "effectsController.hpp"
#include "ResourcePath.hpp"
#include "screenShakeController.hpp"


effectsController::effectsController() {
    //Begin by loading all of the effects images (and there are plenty!)
    const std::string fileExt1[5] = {"turretFlash1.png", "turretFlash2.png", "turretFlash3.png", "turretFlash4.png", "turretFlash5.png"};
    for (int i = 0; i < 5; i++) {
        turretFlashTextures[i].loadFromFile(resourcePath() + fileExt1[i]);
        turretFlashSprites[i].setTexture(turretFlashTextures[i]);
    }
    
    const std::string fileExt2[2] = {"hBullet.png", "vBullet.png"};
    for (int i = 0; i < 2; i++) {
        bulletTexture[i].loadFromFile(resourcePath() + fileExt2[i]);
        bulletSprites[i].setTexture(bulletTexture[i]);
        powerupTxtr[i].loadFromFile(resourcePath() + "powerups.png", sf::IntRect(i * 13, 0, 13, 13));
        powerupSpr[i].setTexture(powerupTxtr[i]);
        powerupSpr[i].setOrigin(7, 7);
    }
    
    for (int i = 0; i < 8; i++) {
        dashSmokeTextures[i].loadFromFile(resourcePath() + "dashSmokeSheet.png", sf::IntRect(i * 64, 0, 64, 32));
        dashSmokeSprites[i].setTexture(dashSmokeTextures[i]);
    }
    
    bulletGlow[0].loadFromFile(resourcePath() + "whiteFloorGlow.png");
    bulletSprites[2].setTexture(bulletGlow[0]);
    redGlowTexture.loadFromFile(resourcePath() + "redFloorGlow.png");
    redGlowSprite.setTexture(redGlowTexture);
    redGlowSprite.setOrigin(22.5, 22.5);
    blueGlowTexture.loadFromFile(resourcePath() + "blueFloorGlow.png");
    blueGlowSprite.setTexture(blueGlowTexture);
    blueGlowSprite.setOrigin(22.5, 22.5);
    
    const std::string fileExt3[4] = {"poof1.png", "poof2.png", "poof3.png", "poof4.png"};
    const std::string fileExt7[4] = {"EnemyOrbShot1.png", "EnemyOrbShot2.png", "EnemyOrbShot3.png", "EnemyOrbShot4.png"};
    for (int i = 0; i < 4; i++) {
        puffTexture[i].loadFromFile(resourcePath() + fileExt3[i]);
        puffSprites[i].setTexture(puffTexture[i]);
        orbShotTextures[i].loadFromFile(resourcePath() + fileExt7[i]);
        orbShotSprites[i].setTexture(orbShotTextures[i]);
    }
    
    newItemText.loadFromFile(resourcePath() + "newItemText.png");
    newItemSpr.setTexture(newItemText);
    
    for (int i = 0; i < 9; i++) {
        fireExplosionTxtr[i].loadFromFile(resourcePath() + "fireExplosionSheet.png", sf::IntRect(i * 58, 0, 58, 51));
        fireExplosionSpr[i].setTexture(fireExplosionTxtr[i]);
        blueExplosionTxtr[i].loadFromFile(resourcePath() + "blueExplosion.png", sf::IntRect(i * 51, 0, 51, 80));
        blueExplosionSpr[i].setTexture(blueExplosionTxtr[i]);
    }
    
    fireExplosionGlowTxtr.loadFromFile(resourcePath() + "fireExplosionGlow.png");
    fireExplosionGlowSpr.setTexture(fireExplosionGlowTxtr);
    blueFireGlowTxtr.loadFromFile(resourcePath() + "blueFireGlow.png");
    blueFireGlowSpr.setTexture(blueFireGlowTxtr);
    
    const std::string fileExt4[6] = {"exp32_1.png", "exp32_2.png", "exp32_3.png", "exp32_4.png", "exp32_5.png", "exp32_6.png"};
    const std::string fileExt5[6] = {"teleporterSmoke1.png", "teleporterSmoke2.png", "teleporterSmoke3.png", "teleporterSmoke4.png", "teleporterSmoke5.png", "teleporterSmoke6.png"};
    const std::string fileExt6[6] = {"Smoke1.png", "Smoke2.png", "Smoke3.png", "Smoke4.png", "Smoke5.png", "Smoke6.png"};
    for (int i = 0; i < 6; i++) {
        smallExplosionTxtr[i].loadFromFile(resourcePath() + "smallExplosion.png", sf::IntRect(i * 36, 0, 36, 36));
        smallExplosionSpr[i].setTexture(smallExplosionTxtr[i]);
        smokeTextures[i].loadFromFile(resourcePath() + fileExt6[i]);
        smokeSprites[i].setTexture(smokeTextures[i]);
        warpEffectTextures[i].loadFromFile(resourcePath() + fileExt5[i]);
        warpEffectSprites[i].setTexture(warpEffectTextures[i]);
        exp32Texture[i].loadFromFile(resourcePath() + fileExt4[i]);
        exp32Sprites[i].setTexture(exp32Texture[i]);
        energyBeamTextures[i].loadFromFile(resourcePath() + "beamStart.png", sf::IntRect(i * 64, 0, 64, 32));
        energyBeamSprites[i].setTexture(energyBeamTextures[i]);
    }
    
    healthRestoredTex.loadFromFile(resourcePath() + "healthRestored.png");
    healthRestoredSpr.setTexture(healthRestoredTex);
    
    bubbleShotTex[0].loadFromFile(resourcePath() + "OrbShot1.png");
    bubbleShotTex[1].loadFromFile(resourcePath() + "OrbShot2.png");
    bubbleShotSpr[0].setTexture(bubbleShotTex[0]);
    bubbleShotSpr[1].setTexture(bubbleShotTex[1]);
    
    for (int i = 0; i < 2; i++) {
        turretShotText[i].loadFromFile(resourcePath() + "turretShot.png", sf::IntRect(i * 7, 0, 7, 12));
        turretShotSpr[i].setTexture(turretShotText[i]);
        turretShotSpr[i].setOrigin(sf::Vector2f(4, 4));
    }
    
    for (int i = 0; i < 5; i++) {
        healthEffectTextures[i].loadFromFile(resourcePath() + "healthEffect.png", sf::IntRect(24 * i, 0, 24, 16));
        healthEffectSprites[i].setTexture(healthEffectTextures[i]);
    }
    
    for (int i = 0; i < 2; i++) {
        dasherShotTextures[i].loadFromFile(resourcePath() + "dasherShot.png", sf::IntRect(i * 22, 0, 22, 22));
        dasherShotSprites[i].setTexture(dasherShotTextures[i]);
    }
}

// In the process of shortening the code with template functions
template<typename T>
void updateVector(std::vector<T>& vec, float xOffset, float yOffset, sf::Time & elapsedTime) {
    if (!vec.empty()) {
        for (typename std::vector<T>::iterator it = vec.begin(); it != vec.end();) {
            it->update(xOffset, yOffset, elapsedTime);
            if (it->getKillFlag()) {
                it = vec.erase(it);
            }
            else {
                ++it;
            }
        }
    }
}

template<typename T>
void updateVectorGlow(std::vector<T>& vec, float xOffset, float yOffset, std::vector<sf::Sprite*>& glowSprs, sf::Time & elapsedTime) {
    if (!vec.empty()) {
        for (typename std::vector<T>::iterator it = vec.begin(); it != vec.end();) {
            it->update(xOffset, yOffset, elapsedTime);
            glowSprs.push_back(it->getGlow());
            if (it->getKillFlag()) {
                it = vec.erase(it);
            }
            else {
                ++it;
            }
        }
    }
}

//This function updates the positions of all of the effect objects whenever called
void effectsController::update(float xOffset, float yOffset, ScreenShakeController* scrn, sf::Time & elapsedTime) {
    // Begin by clearing out the outdated glow sprites for the effects
    //glowSprs.clear();
    //Only attempt to loop through the vector and update or delete elements if the vector is not empty
    if (!turretFlashes.empty()) {
        for (auto & element : turretFlashes) {
            //Update the elements position and decrement it's timeout variable
            element.update(xOffset, yOffset);
        }
        //Loop through based on index...
        for (auto it = turretFlashes.begin(); it != turretFlashes.end();) {
            //If the timeout for an element has reached 0
            if (it->getKillFlag()) {
                //Erase it from the vector
                it = turretFlashes.erase(it);
            }
            else {
                //Go to the next element of the vector
                ++it;
            }
        }
    }
    
    updateVectorGlow(smallExplosions, xOffset, yOffset, glowSprs, elapsedTime);
    updateVector(healthEffects, xOffset, yOffset, elapsedTime);
    updateVector(dodgeEffects, xOffset, yOffset, elapsedTime);
    updateVectorGlow(hearts, xOffset, yOffset, glowSprs, elapsedTime);
    updateVectorGlow(coins, xOffset, yOffset, glowSprs, elapsedTime);
    updateVectorGlow(turretShots, xOffset, yOffset, glowSprs, elapsedTime);
    updateVectorGlow(dasherShots, xOffset, yOffset, glowSprs, elapsedTime);
    updateVectorGlow(enemyShots, xOffset, yOffset, glowSprs, elapsedTime);
    
    //Only attempt to loop through the vector and update or delete elements if the vector is not empty
    if (!bullets.empty()) {
        for (std::vector<bulletType1>::iterator it = bullets.begin(); it != bullets.end();) {
            //If the duration has reached 0 or the object's kill flag is high
            if (it->getKillFlag()) {
                // Don't always want to add in additional effect where it could make the screen look cluttered, so check a condition first
                if (it->checkCanPoof()) {
                    //Create another effect for bullet death
                    shotPuff p(puffSprites, it->getXpos() - xOffset, it->getYpos() - yOffset, it->getDirection(), 0);
                    //Push it back
                    puffs.push_back(p);
                }
                //Erase the bullet
                it = bullets.erase(it);
            }
            else {
                //Update the position
                it->update(xOffset, yOffset);
                glowSprs.push_back(it->getGlow());
                ++it;
            }
        }
    }
    
    //Only attempt to loop through the vector and update or delete elements if the vector is not empty
    if (!bulletLowerLayer.empty()) {
        for (std::vector<bulletType1>::iterator it = bulletLowerLayer.begin(); it != bulletLowerLayer.end();) {
            if (it->getKillFlag()) {
                if (it->checkCanPoof()) {
                shotPuff p(puffSprites, it->getXpos() - xOffset, it->getYpos() - yOffset, it->getDirection(), 0);
                puffs.push_back(p);
                }
                it = bulletLowerLayer.erase(it);
            }
            else {
                it->update(xOffset, yOffset);
                glowSprs.push_back(it->getGlow());
                ++it;
            }
        }
    }
    
    updateVector(puffs, xOffset, yOffset, elapsedTime);
    
    if (!energyBeams.empty()) {
        for (auto it = energyBeams.begin(); it != energyBeams.end();) {
            if (it->getKillFlag()) {
                it = energyBeams.erase(it);
            }
            
            else {
                it->update(xOffset, yOffset);
                if (it->isValid()) {
                    addBlueExplosion(it->getX2() - xOffset, it->getY2() - yOffset);
                    it->invalidate();
                    scrn->shake();
                }
                ++it;
            }
        }
    }
    
    updateVectorGlow(fireExplosions, xOffset, yOffset, glowSprs, elapsedTime);
    
    if (!bigExplosions.empty()) {
        for (std::vector<Explosion32effect>::iterator it = bigExplosions.begin(); it != bigExplosions.end();) {
            if (it->imFinished == 1) {
                it = bigExplosions.erase(it);
            }
            else {
                // Throughout the duration of the explosion, throw in some fire effects for good measure
                if (it->spriteIndex == 1 || it->spriteIndex == 2 || it->spriteIndex == 4) {
                    TeleporterSmoke t(smokeSprites, it->getXpos() - xOffset + 6, it->getYpos() - yOffset + 4);
                    warpEffects.push_back(t);
                }
                it->positionUpdateF(xOffset, yOffset);
                ++it;
            }
        }
    }
    
    updateVector(warpEffects, xOffset, yOffset, elapsedTime);
}

//A function for adding a turret flash animation
void effectsController::addTurretFlash(float x, float y) {
    turretFlashEffect t(turretFlashSprites, x, y);
    turretFlashes.push_back(t);
}

//A function for adding a turret shot effect
void effectsController::addTurretShot(float x, float y, short dir) {
    turretShot t(turretShotSpr, redGlowSprite, x, y, dir);
    turretShots.push_back(t);
}

void effectsController::addHearts(float x, float y) {
    Powerup h(&powerupSpr[0], redGlowSprite, x, y);
    hearts.push_back(h);
}

void effectsController::addCoins(float x, float y) {
    Powerup c(&powerupSpr[1], blueGlowSprite, x, y);
    coins.push_back(c);
}

void effectsController::addEnemyShot(float x, float y, short dir) {
    Enemyshot e(bubbleShotSpr, redGlowSprite, x, y, dir);
    enemyShots.push_back(e);
}

void effectsController::addBlueExplosion(float x, float y) {
    FireExplosion f(blueExplosionSpr, blueFireGlowSpr, x, y);
    f.setOrigin(25, 80);
    fireExplosions.push_back(f);
}

void effectsController::addDasherShot(float x, float y, short dir) {
    DasherShot d(dasherShotSprites, redGlowSprite, x, y, dir);
    dasherShots.push_back(d);
}

void effectsController::addDodgeEffect(float x, float y, int dir, int scale) {
    DashSmoke d(dashSmokeSprites, x, y, dir, scale);
    dodgeEffects.push_back(d);
}

// A function for adding puffs
void effectsController::addPuff(float x, float y) {
    shotPuff p(puffSprites, x, y, 0, 0);
    puffs.push_back(p);
}

void effectsController::addHealthEffect(float x, float y) {
    HealthEffect h(healthEffectSprites[0], x, y + 8);
    healthEffects.push_back(h);
}

void effectsController::addLvP1(float x, float y, FontController& font) {
    HealthEffect h(healthEffectSprites[1], x, y + 8);
    //font.updateScore(font.getScore() + 1);
    healthEffects.push_back(h);
}

void effectsController::addFireExplosion(float x, float y) {
    FireExplosion f(fireExplosionSpr, fireExplosionGlowSpr, x, y);
    fireExplosions.push_back(f);
}

void effectsController::addSmallExplosion(float x, float y) {
    SmallExplosion s(smallExplosionSpr, fireExplosionGlowSpr, x, y);
    smallExplosions.push_back(s);
}

void effectsController::addLvP3(float x, float y, FontController& font) {
    HealthEffect h(healthEffectSprites[2], x, y + 8);
    //font.updateScore(font.getScore() + 3);
    healthEffects.push_back(h);
}

void effectsController::addLvP30(float x, float y, FontController& font) {
    HealthEffect h(healthEffectSprites[3], x, y + 8);
    //font.updateScore(font.getScore() + 30);
    healthEffects.push_back(h); 
}

void effectsController::addLvP10(float x, float y, FontController &font) {
    HealthEffect h(healthEffectSprites[4], x, y + 8);
    //font.updateScore(font.getScore() + 10);
    healthEffects.push_back(h);
}

void effectsController::addEnergyBeam(float x, float y, float dir, float length) {
    EnergyBeam en(x, y, energyBeamSprites, dir, length);
    energyBeams.push_back(en);
}

void effectsController::addHpRestored(float x, float y) {
    HealthEffect h(healthRestoredSpr, x, y);
    healthEffects.push_back(h);
}

void effectsController::addScootShot(float x, float y, short dir, float playerPosX, float playerPosY) {
    turretShot t(turretShotSpr, redGlowSprite, x, y, dir);
    t.speedFactor(2.8);
    t.enableTracking(playerPosX, playerPosY);
    turretShots.push_back(t);
}

void effectsController::addNewItem(float x, float y, FontController &font) {
    HealthEffect h(newItemSpr, x - 30, y);
    healthEffects.push_back(h);
}

// A function to add the trail sprites that follow enemy orbshots
void effectsController::addOrbshotTrail(float x, float y) {
    shotPuff p(orbShotSprites, x, y, 0, 0);
    puffs.push_back(p);
}

//A function for adding a bullet
void effectsController::addBullet(bool select, char sprIndex, float xPos, float yPos) {
    if (select) {   //Horizontal case
        bulletType1 bullet(bulletSprites[0], bulletSprites[2], sprIndex, xPos, yPos);
        bullets.push_back(bullet);
    }
    else {  //Vertical case
        bulletType1 bullet(bulletSprites[1], bulletSprites[2], sprIndex, xPos, yPos);
            bullets.push_back(bullet);
    }
}

void effectsController::addWarpEffect(float x, float y) {
    // Construct a teleporter smoke effect with the desired sprites and position
    TeleporterSmoke t(warpEffectSprites, x, y);
    // Push it back to the proper vector
    warpEffects.push_back(t);
}

void effectsController::addSmokeEffect(float x, float y) {
    TeleporterSmoke t(smokeSprites, x, y);
    warpEffects.push_back(t);
}

void effectsController::addExplosion(float x, float y) {
    Explosion32effect e(exp32Sprites, x, y);
    bigExplosions.push_back(e);
}

template <typename T>
void drawEffect(T& inpVec, sf::RenderTexture& window, std::vector<std::tuple<sf::Sprite, float, int>>& gameObjects) {
    // Create an effect object to pust to the gameObjects vector
    std::tuple<sf::Sprite, float, int> effectObject;
    // All effects are assigned the same identifier tag so that the drawing code can identify them
    std::get<2>(effectObject) = 10;
    if (!inpVec.empty()) {
        for (auto & element : inpVec) {
            std::get<0>(effectObject) = element.getSprite();
            std::get<1>(effectObject) = element.getYpos();
            gameObjects.push_back(effectObject);
        }
    }
}

template <typename T>
void directDraw(T& inpVec, sf::RenderTexture& window, std::vector<std::tuple<sf::Sprite, float, int>>& gameObjects) {
    if (!inpVec.empty()) {
        for (auto & element : inpVec) {
            window.draw(element.getSprite());
        }
    }
}

//Draw the sprites for all of the effect objects
void effectsController::draw(sf::RenderTexture& window, std::vector<std::tuple<sf::Sprite, float, int>>& gameObjects) {
    drawEffect(hearts, window, gameObjects);
    drawEffect(coins, window, gameObjects);
    drawEffect(turretFlashes, window, gameObjects);
    drawEffect(bullets, window, gameObjects);
    drawEffect(puffs, window, gameObjects);
    drawEffect(turretShots, window, gameObjects);
    drawEffect(dasherShots, window, gameObjects);
    drawEffect(fireExplosions, window, gameObjects);
    drawEffect(smallExplosions, window, gameObjects);
    
    if (!energyBeams.empty()) {
        for (auto element : energyBeams) {
            element.draw(window);
        }
    }
    
    if (!dodgeEffects.empty()) {
        for (auto & element : dodgeEffects) {
            gameObjects.push_back(std::make_tuple(element.getSprite(), element.getYpos(), (int) 0));
        }
    }
    
    if (!warpEffects.empty()) {
        for (auto & element : warpEffects) {
            if (element.getDrawOrder() == 0) {
                window.draw(element.getSprite());
            }
        }
    }
    drawEffect(bigExplosions, window, gameObjects);
    drawEffect(enemyShots, window, gameObjects);
    drawEffect(healthEffects, window, gameObjects);
}

void effectsController::drawLower(sf::RenderTexture& window) {
    if (!bulletLowerLayer.empty()) {
        for (auto & element : bulletLowerLayer) {
            window.draw(element.getSprite());  //Get the sprite, and update based on the overworld offset
        }
    }
    if (!warpEffects.empty()) {
        for (auto & element : warpEffects) {
            if (element.getDrawOrder() == 1) {
                window.draw(element.getSprite());
            }
        }
    }
}

std::vector<sf::Sprite*>* effectsController::getGlowSprs() {
    return &glowSprs;
}

void effectsController::clear() {
    bulletLowerLayer.clear();
    turretFlashes.clear();
    bullets.clear();
    puffs.clear();
    bigExplosions.clear();
    warpEffects.clear();
    enemyShots.clear();
    healthEffects.clear();
    turretShots.clear();
    dasherShots.clear();
    dodgeEffects.clear();
    energyBeams.clear();
    smallExplosions.clear();
    fireExplosions.clear();
    hearts.clear();
    coins.clear();
}

std::vector<bulletType1>& effectsController::getBulletLayer1() {
    return bullets;
}

std::vector<bulletType1>& effectsController::getBulletLayer2() {
    return bulletLowerLayer;
}

std::vector<turretShot>* effectsController::getTurretShots() {
    return &turretShots;
}

std::vector<Enemyshot>* effectsController::getEnemyShots() {
    return &enemyShots;
}

std::vector<DasherShot>* effectsController::getDasherShots() {
    return &dasherShots;
}

void effectsController::condClearGlowSpr(sf::Sprite * inpSpr) {
    glowSprs.clear();
    glowSprs.push_back(inpSpr);
}

std::vector<FireExplosion>* effectsController::getExplosions() {
    return &fireExplosions;
}

std::vector<sf::Sprite*>* effectsController::getGlowSprs2() {
    return &glowSprs2;
}

std::vector<Powerup>* effectsController::getHearts() {
    return &hearts;
}

std::vector<Powerup>* effectsController::getCoins() {
    return &coins;
}
