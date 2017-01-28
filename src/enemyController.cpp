#include "enemyController.hpp"
#include "DetailGroup.hpp"
#include "Game.hpp"
#include "ResourcePath.hpp"
#include "camera.hpp"
#include "tileController.hpp"
#include "wall.hpp"
#include <cmath>

enemyController::enemyController() {}

void enemyController::draw(drawableVec & gameObjects, drawableVec & gameShadows,
                           Camera & camera) {
    const sf::View & cameraView = camera.getOverworldView();
    sf::Vector2f viewCenter = cameraView.getCenter();
    sf::Vector2f viewSize = cameraView.getSize();
    for (auto & element : turrets) {
        if (element->getPosition().x > viewCenter.x - viewSize.x / 2 - 32 &&
            element->getPosition().x < viewCenter.x + viewSize.x / 2 + 32 &&
            element->getPosition().y > viewCenter.y - viewSize.y / 2 - 32 &&
            element->getPosition().y < viewCenter.y + viewSize.y / 2 + 32) {
            std::tuple<sf::Sprite, float, Rendertype, float> shadow;
            std::get<0>(shadow) = element->getShadow();
            gameShadows.push_back(shadow);
            std::tuple<sf::Sprite, float, Rendertype, float> tSpr;
            std::get<0>(tSpr) = element->getSprite();
            std::get<1>(tSpr) = element->getPosition().y;
            if (element->colored()) {
                std::get<2>(tSpr) = Rendertype::shadeWhite;
            } else {
                std::get<2>(tSpr) = Rendertype::shadeDefault;
            }
            gameObjects.push_back(tSpr);
        }
    }
    for (auto & element : critters) {
        gameShadows.emplace_back(element->getShadow(), 0.f,
                                 Rendertype::shadeDefault, 0.f);
        std::tuple<sf::Sprite, float, Rendertype, float> tSpr;
        std::get<0>(tSpr) = element->getSprite();
        std::get<1>(tSpr) = element->getPosition().y - 16;
        // If the enemy should be colored, let the rendering code know to pass
        // it through a fragment shader
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
	    gameShadows.emplace_back(element->getShadow(), 0.f,
				     Rendertype::shadeDefault, 0.f);
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
    if (!turrets.empty()) {
        for (auto it = turrets.begin(); it != turrets.end();) {
            if ((*it)->getKillFlag() == 1) {
                util::sleep(milliseconds(60));
                camera.shake(0.17f);
                it = turrets.erase(it);
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
                        (*it)->update(elapsedTime, pGame);
                    }
                    cameraTargets.emplace_back((*it)->getPosition().x,
                                               (*it)->getPosition().y);
                }
                ++it;
            }
        }
    }
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
    if (!critters.empty()) {
        // Need to check if each enemy overlaps with any other enemies so that
        // they don't bunch up
        for (size_t i = 0; i < critters.size(); i++) {
            for (size_t j = 0; j < critters.size(); j++) {
                // Obviously it would be bad to compare an object to itself.
                if (i != j) {
                    // If the enemy at index i is active and overlaps with
                    // another enemy that is also active...
                    if (fabs(critters[i]->getPosition().x -
                             critters[j]->getPosition().x) < 12 &&
                        fabs(critters[i]->getPosition().y -
                             critters[j]->getPosition().y) < 12 &&
                        critters[i]->isActive() && critters[j]->isActive()) {
                        critters[i]->deActivate();
                    }
                }
            }
        }
        for (auto it = critters.begin(); it != critters.end();) {
            if ((*it)->getKillFlag()) {
                util::sleep(milliseconds(60));
                camera.shake(0.17f);
                it = critters.erase(it);
            } else {
                if ((*it)->getPosition().x >
                        viewCenter.x - viewSize.x / 2 - 32 &&
                    (*it)->getPosition().x <
                        viewCenter.x + viewSize.x / 2 + 32 &&
                    (*it)->getPosition().y >
                        viewCenter.y - viewSize.y / 2 - 32 &&
                    (*it)->getPosition().y <
                        viewCenter.y + viewSize.y / 2 + 32) {
                    cameraTargets.emplace_back((*it)->getPosition().x,
                                               (*it)->getPosition().y);
                }
                if (enabled) {
                    (*it)->update(pGame, elapsedTime, tileController);
                }
                ++it;
            }
        }

        // Now we have to reactivate all of the objects. Perhaps there is a
        // smarter way than this brute force approach...
        for (auto & element : critters) {
            element->activate();
        }
    }
    if (!dashers.empty()) {
	for (auto it = dashers.begin(); it != dashers.end();) {
	    if ((*it)->getKillFlag()) {
		util::sleep(milliseconds(60));
		camera.shake(0.17f);
		it = dashers.erase(it);
	    } else {
		if ((*it)->getPosition().x > viewCenter.x - viewSize.x / 2 - 32 &&
		    (*it)->getPosition().x < viewCenter.x + viewSize.x / 2 + 32 &&
		    (*it)->getPosition().y > viewCenter.y - viewSize.y / 2 - 32 &&
		    (*it)->getPosition().y < viewCenter.y + viewSize.y / 2 + 32) {
		    if (enabled) {
			(*it)->update(pGame, tileController.walls, elapsedTime);
			cameraTargets.emplace_back((*it)->getPosition().x,
						   (*it)->getPosition().y);
		    }
		}
		++it;
	    }
	}
    }
}

void enemyController::clear() {
    turrets.clear();
    scoots.clear();
    dashers.clear();
    critters.clear();
}

void enemyController::addTurret(tileController * pTiles) {
    auto pCoordVec = pTiles->getEmptyLocations();
    int locationSelect = rng::random<2>() ? rng::random(pCoordVec->size() / 2)
                                          : rng::random(pCoordVec->size());
    float xInit = (*pCoordVec)[locationSelect].x * 32 + pTiles->getPosX();
    float yInit = (*pCoordVec)[locationSelect].y * 26 + pTiles->getPosY();
    turrets.push_back(std::make_shared<Turret>(
        getgResHandlerPtr()->getTexture(ResHandler::Texture::gameObjects),
        xInit, yInit));
    (*pCoordVec)[locationSelect] = pCoordVec->back();
    pCoordVec->pop_back();
}

void enemyController::addScoot(tileController * pTiles) {
    auto pCoordVec = pTiles->getEmptyLocations();
    int locationSelect = rng::random<2>() ? rng::random(pCoordVec->size() / 2)
                                          : rng::random(pCoordVec->size());
    float xInit = (*pCoordVec)[locationSelect].x * 32 + pTiles->getPosX();
    float yInit = (*pCoordVec)[locationSelect].y * 26 + pTiles->getPosY();
    scoots.push_back(std::make_shared<Scoot>(
        getgResHandlerPtr()->getTexture(ResHandler::Texture::gameObjects),
        getgResHandlerPtr()->getTexture(ResHandler::Texture::scootShadow),
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
        getgResHandlerPtr()->getTexture(ResHandler::Texture::gameObjects),
        xInit, yInit));
    (*pCoordVec)[locationSelect] = pCoordVec->back();
    pCoordVec->pop_back();
}

void enemyController::addCritter(tileController * pTiles) {
    auto pCoordVec = pTiles->getEmptyLocations();
    int locationSelect = rng::random(pCoordVec->size());
    float xInit = (*pCoordVec)[locationSelect].x * 32 + pTiles->getPosX();
    float yInit = (*pCoordVec)[locationSelect].y * 26 + pTiles->getPosY();
    critters.push_back(std::make_shared<Critter>(
        getgResHandlerPtr()->getTexture(ResHandler::Texture::gameObjects),
        pTiles->mapArray, xInit, yInit));
    (*pCoordVec)[locationSelect] = pCoordVec->back();
    pCoordVec->pop_back();
}

void enemyController::setWindowSize(float windowW, float windowH) {
    this->windowW = windowW;
    this->windowH = windowH;
}

std::vector<std::shared_ptr<Critter>> & enemyController::getCritters() {
    return critters;
}

std::vector<std::shared_ptr<Dasher>> & enemyController::getDashers() {
    return dashers;
}

std::vector<std::shared_ptr<Scoot>> & enemyController::getScoots() {
    return scoots;
}

std::vector<std::shared_ptr<Turret>> & enemyController::getTurrets() {
    return turrets;
}
