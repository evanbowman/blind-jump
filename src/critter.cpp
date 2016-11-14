//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#include "critter.hpp"
#include "math.h"
#include "player.hpp"
#include "tileController.hpp"
#include <cmath>

Critter::Critter(const sf::Texture & txtr, uint8_t _map[61][61], float _xInit,
                 float _yInit)
    : Enemy(_xInit, _yInit), xInit(_xInit), yInit(_yInit), currentDir(0.f),
      jumpTargetx(0.f), jumpTargety(0.f), spriteSheet(txtr), awake(false),
      active(true), recalc(4), map(_map) {
    health = 3;
    spriteSheet.setOrigin(9, 9);
    shadow.setOrigin(9, 9);
    shadow.setTexture(txtr);
    shadow.setTextureRect(sf::IntRect(54, 57, 18, 18));
    hitBox.setPosition(xPos, yPos);
}

const Critter::HBox & Critter::getHitBox() const { return hitBox; }

void Critter::updatePlayerDead() { frameIndex = 0; }

void Critter::update(const Player * player, EffectGroup & effects,
                     const sf::Time & elapsedTime, tileController & tiles) {
    xPos = xInit + 12;
    yPos = yInit;
    for (auto & element : effects.get<9>()) {
        if (element.getHitBox().overlapping(hitBox) && element.checkCanPoof()) {
            if (health == 1) {
                element.disablePuff();
                element.setKillFlag();
            }
            element.poof();
            health -= 1;
            colored = true;
            colorAmount = 1.f;
        }
    }
    if (health == 0) {
        onDeath(effects);
    }
    xPos -= 12; // Currently off-centered, this is just temporary work-around
    Enemy::updateColor(elapsedTime);
    hitBox.setPosition(xPos, yPos);
    float tilePosX = tiles.posX;
    float tilePosY = tiles.posY;

    if (awake) {
        float speed;
        if (active) {
            speed = 1.4;
        } else {
            speed = 0.7;
        }
        // If the enemy is finished following its path to the player
        if (path.empty() || recalc == 0) {
            recalc = 8;

            aStrCoordinate origin, target;
            origin.x = (xPos - tilePosX) / 32;
            origin.y = (yPos - tilePosY) / 26;
            target.x = (tilePosX - player->getXpos() - 12) / -32;
            target.y = (tilePosY - player->getYpos() - 32) / -26;
            if (map[target.x][target.y] == 3 || map[target.x][target.y] == 4 ||
                map[target.x][target.y] == 5 || map[target.x][target.y] == 11 ||
                map[target.x][target.y] == 8) {
                path = astar_path(target, origin, map);
                previous = path.back();
                path.pop_back();
                xInit = ((xPos - tilePosX) / 32) * 32 + tilePosX;
                yInit = ((yPos - tilePosY) / 26) * 26 + tilePosY;
                // Calculate the direction to move in, based on the coordinate
                // of the previous location and the coordinate of the next
                // location
                currentDir =
                    atan2(yInit - (((path.back().y * 26) + 4 + tilePosY)),
                          xInit - (((path.back().x * 32) + 4 + tilePosX)));
            }
        }

        // If the path is not empty
        else {
            // Add each component of the direction vector to the enemy's
            // position datafields
            xInit -= speed * cos(currentDir) *
                     (elapsedTime.asMicroseconds() * 0.00005f);
            yInit -= speed * sin(currentDir) *
                     (elapsedTime.asMicroseconds() * 0.00005f);
            // If the enemy is sufficiently close to the target point, pop it
            // and work on the next one
            if (fabs(xInit - (((path.back().x * 32) + 4 + tilePosX))) < 8 &&
                fabs(yInit - (((path.back().y * 26) + 4 + tilePosY))) < 8) {
                recalc--;
                previous = path.back();
                path.pop_back();
                // Calculate the direction to move in
                currentDir =
                    atan2(yInit - (((path.back().y * 26) + 4 + tilePosY)),
                          xInit - (((path.back().x * 32) + 4 + tilePosX)));
            }
        }

        // Process the animation
        frameTimer += elapsedTime.asMilliseconds();
        if (frameTimer > 140) {
            frameTimer -= 140;
            frameIndex++;
            if (frameIndex > 2) {
                frameIndex = 0;
            }
        }

        // Flip the sprite to face the player
        if (xPos > player->getXpos()) {
            spriteSheet.setScale(1.f, 1.f);
            shadow.setScale(1.f, 1.f);
        } else {
            spriteSheet.setScale(-1.f, 1.f);
            shadow.setScale(-1.f, 1.f);
        }
    }

    else {
        if (fabsf(player->getXpos() - xPos) < 300 &&
            fabsf(player->getYpos() - yPos) < 300)
            awake = true;
    }

    shadow.setPosition(xPos + 12, yPos + 1);
    spriteSheet.setPosition(xPos + 12, yPos);
}

const framework::Sprite & Critter::getShadow() const { return shadow; }

const framework::Sprite & Critter::getSprite() const {
    return spriteSheet[frameIndex];
}

void Critter::activate() { active = true; }

void Critter::deActivate() { active = false; }

bool Critter::isActive() { return active; }

void Critter::onDeath(EffectGroup & effects) {
    // With some random chance, add a heart item to the map
    unsigned long int temp = rng::random<5>();
    if (temp == 0) {
        effects.add<4>(
            ::resHandlerPtr->getTexture(ResHandler::Texture::gameObjects),
            ::resHandlerPtr->getTexture(ResHandler::Texture::redglow),
            xInit + 10, yInit, Item::Type::Heart);
    } else {
        effects.add<5>(
            ::resHandlerPtr->getTexture(ResHandler::Texture::gameObjects),
            ::resHandlerPtr->getTexture(ResHandler::Texture::blueglow),
            xInit + 10, yInit, Item::Type::Coin);
    }
    effects.add<1>(
        ::resHandlerPtr->getTexture(ResHandler::Texture::gameObjects),
        ::resHandlerPtr->getTexture(ResHandler::Texture::fireExplosionGlow),
        xInit + 8, yInit);
    killFlag = true;
}
