//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#include "enemyController.hpp"
#include "DetailGroup.hpp"
#include "ResourcePath.hpp"
#include "camera.hpp"
#include "game.hpp"
#include "tileController.hpp"
#include "wall.hpp"
#include <cmath>

enemyController::enemyController() {}

void enemyController::draw(drawableVec & gameObjects, drawableVec & gameShadows,
                           Camera & camera) {
    const sf::View & cameraView = camera.getOverworldView();
    sf::Vector2f viewCenter = cameraView.getCenter();
    sf::Vector2f viewSize = cameraView.getSize();
    for (auto & element : scoots) {
        if (element->getPosition().x > viewCenter.x - viewSize.x / 2 - 32 &&
            element->getPosition().x < viewCenter.x + viewSize.x / 2 + 32 &&
            element->getPosition().y > viewCenter.y - viewSize.y / 2 - 32 &&
            element->getPosition().y < viewCenter.y + viewSize.y / 2 + 32) {
            gameShadows.emplace_back(element->getShadow(), 0.f,
                                     Rendertype::shadeDefault, 0.f);
            if (element->isColored()) {
                gameObjects.emplace_back(
                    element->getSprite(), element->getPosition().y - 16,
                    Rendertype::shadeWhite, element->getColorAmount());
            } else {
                gameObjects.emplace_back(element->getSprite(),
                                         element->getPosition().y - 16,
                                         Rendertype::shadeDefault, 0.f);
            }
        }
    }
    for (auto & element : dashers) {
        if (element->getPosition().x > viewCenter.x - viewSize.x / 2 - 32 &&
            element->getPosition().x < viewCenter.x + viewSize.x / 2 + 32 &&
            element->getPosition().y > viewCenter.y - viewSize.y / 2 - 32 &&
            element->getPosition().y < viewCenter.y + viewSize.y / 2 + 32) {
            auto state = element->getState();
            if (state != Dasher::State::dying && state != Dasher::State::dead) {
                gameShadows.emplace_back(element->getShadow(), 0.f,
                                         Rendertype::shadeDefault, 0.f);
            }
            for (auto & blur : *element->getBlurEffects()) {
                gameObjects.emplace_back(*blur.getSprite(), blur.yInit + 200,
                                         Rendertype::shadeDefault, 0.f);
            }
            if (element->isColored()) {
                gameObjects.emplace_back(
                    element->getSprite(), element->getPosition().y,
                    Rendertype::shadeWhite, element->getColorAmount());
            } else {
                gameObjects.emplace_back(element->getSprite(),
                                         element->getPosition().y,
                                         Rendertype::shadeDefault, 0.f);
            }
        }
    }
}

void enemyController::update(Game * pGame, bool enabled,
                             const sf::Time & elapsedTime,
                             std::vector<sf::Vector2f> & cameraTargets) {
    EffectGroup & effectGroup = pGame->getEffects();
    tileController & tileController = pGame->getTileController();
    Camera & camera = pGame->getCamera();
    Player * player = &pGame->getPlayer();
    const sf::View & cameraView = camera.getOverworldView();
    sf::Vector2f viewCenter = cameraView.getCenter();
    sf::Vector2f viewSize = cameraView.getSize();
    if (!scoots.empty()) {
        for (auto it = scoots.begin(); it != scoots.end();) {
            if ((*it)->getKillFlag()) {
                util::sleep(milliseconds(60));
                camera.shake(0.17f);
                it = scoots.erase(it);
            } else {
                if ((*it)->getPosition().x >
                        viewCenter.x - viewSize.x / 2 - 32 &&
                    (*it)->getPosition().x <
                        viewCenter.x + viewSize.x / 2 + 32 &&
                    (*it)->getPosition().y >
                        viewCenter.y - viewSize.y / 2 - 32 &&
                    (*it)->getPosition().y <
                        viewCenter.y + viewSize.y / 2 + 32) {
                    if (enabled) {
                        (*it)->update(pGame, tileController.walls, elapsedTime);
                    }
                    cameraTargets.emplace_back((*it)->getPosition().x,
                                               (*it)->getPosition().y);
                }
                ++it;
            }
        }
    }
    for (auto & element : dashers) {
        if (element->getPosition().x > viewCenter.x - viewSize.x / 2 - 32 &&
            element->getPosition().x < viewCenter.x + viewSize.x / 2 + 32 &&
            element->getPosition().y > viewCenter.y - viewSize.y / 2 - 32 &&
            element->getPosition().y < viewCenter.y + viewSize.y / 2 + 32) {
            if (enabled) {
                element->update(pGame, tileController.walls, elapsedTime);
                if (element->getState() != Dasher::State::dead) {
                    cameraTargets.emplace_back(element->getPosition().x,
                                               element->getPosition().y);
                }
            }
            if (element->getKillFlag()) {
                util::sleep(milliseconds(60));
                camera.shake(0.17f);
                element->setKillFlag(false);
            }
        }
    }
}

void enemyController::clear() {
    scoots.clear();
    dashers.clear();
}

void enemyController::addScoot(tileController * pTiles) {
    auto pCoordVec = pTiles->getEmptyLocations();
    int locationSelect = rng::random<2>() ? rng::random(pCoordVec->size() / 2)
                                          : rng::random(pCoordVec->size());
    float xInit = (*pCoordVec)[locationSelect].x * 32 + pTiles->getPosX();
    float yInit = (*pCoordVec)[locationSelect].y * 26 + pTiles->getPosY();
    scoots.push_back(std::make_shared<Scoot>(
        getgResHandlerPtr()->getTexture("textures/gameObjects.png"),
        getgResHandlerPtr()->getTexture("textures/charger_enemy_shadow.png"),
        xInit, yInit));
    (*pCoordVec)[locationSelect] = pCoordVec->back();
    pCoordVec->pop_back();
}

void enemyController::addDasher(tileController * pTiles) {
    auto pCoordVec = pTiles->getEmptyLocations();
    int locationSelect = rng::random<2>() ? rng::random(pCoordVec->size() / 2)
                                          : rng::random(pCoordVec->size() / 2);
    float xInit = (*pCoordVec)[locationSelect].x * 32 + pTiles->getPosX();
    float yInit = (*pCoordVec)[locationSelect].y * 26 + pTiles->getPosY();
    dashers.push_back(std::make_shared<Dasher>(
        getgResHandlerPtr()->getTexture("textures/gameObjects.png"),
        xInit, yInit));
    (*pCoordVec)[locationSelect] = pCoordVec->back();
    pCoordVec->pop_back();
}

void enemyController::setWindowSize(float windowW, float windowH) {
    this->windowW = windowW;
    this->windowH = windowH;
}

std::vector<std::shared_ptr<Dasher>> & enemyController::getDashers() {
    return dashers;
}

std::vector<std::shared_ptr<Scoot>> & enemyController::getScoots() {
    return scoots;
}
