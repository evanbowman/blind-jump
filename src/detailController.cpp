//
//  detailController.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/29/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#include "detailController.hpp"
#include "player.hpp"
#include <cmath>
#include "gameMap.hpp"

detailController::detailController(float _windowW, float _windowH, ResourceHandler * _pRH)
	: pRH{_pRH},
	  windowW{_windowW},
	  windowH{_windowH}
{}

Coordinate pickLocation(std::vector<Coordinate>& emptyLocations) {
	// Randomly pick an available empty location
	int locationSelect = rand() % emptyLocations.size();
	Coordinate c = emptyLocations[locationSelect];
	// Don't want to place two objects in the same position, so remove coordinate from the vector if used
	emptyLocations[locationSelect] = emptyLocations.back();
	emptyLocations.pop_back();
	return c;
}

Coordinate pickLocationGrass(std::vector<Coordinate>& emptyLocations, short mapArray[61][61]) {
	// Randomly pick an available empty location
	Coordinate c;
	int locationSelect;
	// Keep track of loop iterations (in case there actually aren't any open grass tiles left)
	int count = 0;
	do {
		count++;
		locationSelect = rand() % emptyLocations.size();
		c = emptyLocations[locationSelect];
		if (count > 500/*On average there are 300 open spaces on a map*/) {
			throw "Maximum tries exceeded--grass tile.";
		}
	} while (mapArray[c.x][c.y] != 8  && mapArray[c.x][c.y] != 11);
	// Don't want to place two objects in the same position, so remove coordinate from the vector if used
	emptyLocations[locationSelect] = emptyLocations.back();
	emptyLocations.pop_back();
	return c;
}

Coordinate pickLocationSand(std::vector<Coordinate>& emptyLocations, short mapArray[61][61]) {
	// Randomly pick an available empty location
	Coordinate c;
	int locationSelect;
	// Keep track of loop iterations (in case there actually aren't any open grass tiles left)
	int count = 0;
	do {
		count++;
		locationSelect = rand() % emptyLocations.size();
		c = emptyLocations[locationSelect];
		if (count > 500/*On average there are 300 open spaces on a map*/) {
			throw "Maximum tries exceeded.";
		}
	} while (mapArray[c.x][c.y] != 3);
	// Don't want to place two objects in the same position, so remove coordinate from the vector if used
	emptyLocations[locationSelect] = emptyLocations.back();
	emptyLocations.pop_back();
	return c;
}

Coordinate pickLocation2(std::vector<Coordinate>& emptyLocations) {
	// Randomly pick an available empty location
	int locationSelect = rand() % emptyLocations.size();
	Coordinate c = emptyLocations[locationSelect];
	return c;
}

void detailController::addWarpImpact(float posX, float posY) {
	sf::Sprite tempSprite;
	tempSprite.setTexture(pRH->getTexture(ResourceHandler::Texture::gameObjects));
	tempSprite.setTextureRect(sf::IntRect(128, 161, 32, 26));
	misc32x26.emplace_back(posX, posY, tempSprite);
}

void detailController::addLamplight(float posX, float posY, int i, int j, float width, float height) {
	sf::Sprite glow;
	glow.setTexture(pRH->getTexture(ResourceHandler::Texture::lamplight));
	lamps.emplace_back((i * 32) + 16 + posX, (j * 26) + 18 + posY, pRH->getTexture(ResourceHandler::Texture::gameObjects), glow);
}

void detailController::addRock(float posX, float posY, int i, int j) {
	rocks.emplace_back((i * 32) + posX, (j * 26) + posY, pRH->getTexture(ResourceHandler::Texture::gameObjects));
}

void detailController::addChest(tileController& t, float posX, float posY, float width, float height, char chestContents) {
	Coordinate c = pickLocation(t.emptyMapLocations);
    float placeOffsetX = (rand() % 6) - 3;
	chests.emplace_back((c.x * 32) + posX + 8 + placeOffsetX, (c.y * 26) + posY - 3, pRH->getTexture(ResourceHandler::Texture::gameObjects), chestContents);
}

void detailController::addEnemyScrap(float posX, float posY, float width, float height) {
	sf::Sprite tempSprite;
	tempSprite.setTexture(pRH->getTexture(ResourceHandler::Texture::gameObjects));
	tempSprite.setTextureRect(sf::IntRect(112, 161, 16, 15));
	misc32x26.emplace_back(posX - 6, posY - 2, tempSprite);
}

void detailController::addDamagedRobots(tileController& t, float posX, float posY) {
	if (rand() % 2) {
		Coordinate c;
		float placeOffsetX = 0;
		sf::Sprite tempSprite;
		try {
			c = pickLocationGrass(t.emptyMapLocations, t.mapArray);
			DamagedRobot dr((c.x * 32) + posX + placeOffsetX - 20, (c.y * 26) + posY - 20, pRH->getTexture(ResourceHandler::Texture::gameObjects));
			damagedRobots.push_back(dr);
		} catch(const char* e) {
			//std::cout << e << std::endl;
		}

		if (rand() % 2) {
			try {
				c = pickLocationGrass(t.emptyMapLocations, t.mapArray);
	    		DamagedRobot dr((c.x * 32) + posX + placeOffsetX - 20, (c.y * 26) + posY - 20, pRH->getTexture(ResourceHandler::Texture::gameObjects));
				damagedRobots.push_back(dr);
			} catch(const char* e) {
				//std::cout << e << std::endl;
			}
		}
		
		if (rand() % 2) {
			try {
				c = pickLocationGrass(t.emptyMapLocations, t.mapArray);
				DamagedRobot dr((c.x * 32) + posX + placeOffsetX - 20, (c.y * 26) + posY - 20, pRH->getTexture(ResourceHandler::Texture::gameObjects));
				damagedRobots.push_back(dr);
			} catch(const char* e) {
				//std::cout << e << std::endl;
			}
		}
	}
}
 
void detailController::addDoor(float xpos, float ypos, int x, int y, float w, float h) {
	doors.emplace_back(xpos + x * 32, ypos + y * 26, pRH->getTexture(ResourceHandler::Texture::introWall));
}

void detailController::addPod(float xpos, float ypos, int x, int y) {
	sf::Sprite tempSprite;
	tempSprite.setOrigin(0, 30);
	tempSprite.setTexture(pRH->getTexture(ResourceHandler::Texture::gameObjects));
	tempSprite.setTextureRect(sf::IntRect(164, 145, 44, 50));
	misc32x26.emplace_back(xpos + x * 32, ypos + y * 26, tempSprite);
}

void detailController::addTeleporter(tileController& t, float posX, float posY, float width, float height) {
	Coordinate c = t.getTeleporterLoc();
   	sf::Sprite glow;
	glow.setTexture(pRH->getTexture(ResourceHandler::Texture::teleporterGlow));
    teleporters.emplace_back((c.x * 32) + posX + 2, (c.y * 26) + posY - 4, pRH->getTexture(ResourceHandler::Texture::gameObjects), &glow);
}

void detailController::update(GameMap * pGM, sf::Time & elapsedTime) {
	Player & player = pGM->getPlayer();
	FontController * pFonts = pGM->getPFonts();
	InputController * pInput = pGM->getPInput();
	effectsController & ef = pGM->getEffects();
	userInterface & ui = pGM->getUI();
	ScreenShakeController * pscr = pGM->getPSSC();

	float xOffset = player.getWorldOffsetX();
	float yOffset = player.getWorldOffsetY();

	std::vector<sf::Sprite *> * glow1 = ef.getGlowSprs();
	std::vector<sf::Sprite *> * glow2 = ef.getGlowSprs2();

	if (!teleporters.empty()) {
		for (auto & element : teleporters) {
			element.update(xOffset, yOffset, elapsedTime);
			if (element.smokeReady()) {
				ef.addWarpEffect(element.getXpos() - xOffset + 4 + (rand() % 6), element.getYpos() - yOffset + 2);
			}
			glow1->push_back(element.getGlow());
			glow2->push_back(element.getGlow());
		}
	}
	
	if (!lamps.empty()) {
		for (auto & element : lamps) {
			element.update(xOffset, yOffset, elapsedTime);
			// Push the light effects back
			float xPos = element.getXpos();
			float yPos = element.getYpos();
			if (xPos < windowW + 150 && xPos > -150 && yPos < windowH + 150 && yPos > -150) {
				glow1->push_back(element.getGlow());
				glow2->push_back(element.getGlow());
			}
		}
	}
	
	if (!chests.empty()) {
		for (auto & element : chests) {
			element.update(xOffset, yOffset, elapsedTime);
			if (pInput->zPressed() && element.getState() == TreasureChest::State::closed && std::abs(windowW / 2 - element.getXpos()) < 20 && std::abs(windowH / 2 - element.getYpos()) < 20) {
				element.setState(TreasureChest::State::opening);
			} else if (element.getState() == TreasureChest::State::ready) {
				element.setState(TreasureChest::State::complete);
				ui.addItem(element.getItem(), ef, element.getXpos() - xOffset, element.Detail::getYpos() - yOffset, *pFonts, player);
			}
		}
	}
	
	if (!rocks.empty())
		for (auto & element : rocks)
			element.update(xOffset, yOffset, elapsedTime);
	
	if (!doors.empty())
		for (auto & element : doors)
			element._update(xOffset, yOffset, pscr, ef, elapsedTime); // Workaround, fix needed
	
	if (!misc32x26.empty())
		for (auto & element : misc32x26)
			element.update(xOffset, yOffset, elapsedTime);
	
	if (!damagedRobots.empty())
		for (auto & element : damagedRobots)
			element.update(xOffset, yOffset, elapsedTime);
}

void detailController::killTeleporter() {
	teleporters.clear();
}

void detailController::draw(drawableVec & gameObjects, drawableVec & gameShadows, sf::RenderTexture & window) {
	if (!misc32x26.empty())
		for (auto & element : misc32x26)
			gameObjects.emplace_back(element.getSprite(), element.getYpos() - 26, Rendertype::shadeDefault, 0.f);
    
	if (!teleporters.empty())
		for (auto & element : teleporters) {
			window.draw(element.getShadow());
			window.draw(element.getSprite());
		}
	
	if (!doors.empty())
		for (auto & element : doors)
			gameObjects.emplace_back(element.getSprite(), element.getYpos() + 52, Rendertype::shadeDefault, 0.f);
	
	if (!rocks.empty())
		for (auto & element : rocks)
			gameObjects.emplace_back(element.getSprite(), element.getYpos() + 22, Rendertype::shadeDefault, 0.f);
	
	if (!damagedRobots.empty())
		for (auto & element : damagedRobots)
			gameObjects.emplace_back(element.getSprite(), element.getYpos(), Rendertype::shadeDefault, 0.f);
	
	if (!chests.empty())
		for (auto & element : chests) {
			gameObjects.emplace_back(element.getSprite(), element.getYpos() - 12, Rendertype::shadeDefault, 0.f);
			gameShadows.emplace_back(element.getShadow(), 0, Rendertype::shadeDefault, 0.f);
		}
	
	if (!lamps.empty()) {
		for (auto & element : lamps) {
			window.draw(element.getSprite());
		}
	}
}

void detailController::clear() {
	teleporters.clear();
	chests.clear();
	misc32x26.clear();
	lamps.clear();
	damagedRobots.clear();
	rocks.clear();
	doors.clear();
}

std::vector<TreasureChest> & detailController::getChests() {
	return chests;
}

Teleporter* detailController::getTeleporter() {
	return &teleporters[0];
}

std::vector<LampLight>* detailController::getLamps() {
	return &lamps;
}

std::vector<Rock>* detailController::getRocks() {
	return &rocks;
}
