//
//  detailController.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/29/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#include "detailController.hpp"
#include "ResourcePath.hpp"
#include "player.hpp"
#include <iostream>
#include <cmath>

detailController::detailController() {
	pTM = nullptr;
}

Coordinate pickLocation(std::vector<Coordinate>& emptyLocations) {
	// Randomly pick an available empty location
	int locationSelect = rand() % emptyLocations.size();
	Coordinate c = emptyLocations[locationSelect];
	// Don't want to place two objects in the same position, so remove coordinate from the vector if used
	emptyLocations[locationSelect] = emptyLocations.back();
	emptyLocations.pop_back();
	return c;
}

void detailController::setTextureManager(TextureManager * pTM) {
	this->pTM = pTM;
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
	tempSprite.setTexture(*pTM->getTexture(TextureManager::Texture::warpImpact));
	misc32x26.emplace_back(posX, posY, &tempSprite, 1, 0, 0);
}

void detailController::addLamplight(float posX, float posY, int i, int j, float width, float height) {
	sf::Sprite tempSprites[2];
	tempSprites[0].setTexture(*pTM->getTexture(TextureManager::Texture::lamp));
	tempSprites[1].setTexture(*pTM->getTexture(TextureManager::Texture::lamplight));
	lamps.emplace_back((i * 32) + 16 + posX, (j * 26) + 18 + posY, tempSprites[0], tempSprites[1], 2, width, height);
}

void detailController::addRock(float posX, float posY, int i, int j) {
	rocks.emplace_back((i * 32) + posX, (j * 26) + posY, pTM->getTexture(TextureManager::Texture::rock), 2, 0, 0);
}

void detailController::addChest(tileController& t, float posX, float posY, float width, float height, char chestContents) {
	Coordinate c = pickLocation(t.emptyMapLocations);
    float placeOffsetX = (rand() % 6) - 3;
	chests.emplace_back((c.x * 32) + posX + 8 + placeOffsetX, (c.y * 26) + posY - 3, pTM->getTexture(TextureManager::Texture::treasureChest), pTM->getTexture(TextureManager::Texture::chestShadow), 7, width, height, chestContents);
}

void detailController::addEnemyScrap(float posX, float posY, float width, float height) {
	sf::Sprite tempSprite;
	tempSprite.setTexture(*pTM->getTexture(TextureManager::Texture::enemyScrap));
	misc32x26.emplace_back(posX - 6, posY - 2, &tempSprite, 0, width, height);
}

void detailController::addDamagedRobots(tileController& t, float posX, float posY) {
	if (rand() % 2) {
		Coordinate c;
		float placeOffsetX = 0;
		sf::Sprite tempSprite;
		try {
			c = pickLocationGrass(t.emptyMapLocations, t.mapArray);
			DamagedRobot dr((c.x * 32) + posX + placeOffsetX - 20, (c.y * 26) + posY - 20, pTM->getTexture(TextureManager::Texture::damagedRobot), 0, 0, 0);
			damagedRobots.push_back(dr);
		} catch(const char* e) {
			std::cout << e << std::endl;
		}

		if (rand() % 2) {
			try {
				c = pickLocationGrass(t.emptyMapLocations, t.mapArray);
	    		DamagedRobot dr((c.x * 32) + posX + placeOffsetX - 20, (c.y * 26) + posY - 20, pTM->getTexture(TextureManager::Texture::damagedRobot), 0, 0, 0);
				damagedRobots.push_back(dr);
			} catch(const char* e) {
				std::cout << e << std::endl;
			}
		}
		
		if (rand() % 2) {
			try {
				c = pickLocationGrass(t.emptyMapLocations, t.mapArray);
				DamagedRobot dr((c.x * 32) + posX + placeOffsetX - 20, (c.y * 26) + posY - 20, pTM->getTexture(TextureManager::Texture::damagedRobot), 0, 0, 0);
				damagedRobots.push_back(dr);
			} catch(const char* e) {
				std::cout << e << std::endl;
			}
		}
	}
}

void detailController::addDasherScrap(float posX, float posY, int scale) {
	if (scale == -1) {
		posX += -14;
	}
	sf::Sprite tempSprite;
	tempSprite.setScale((float) scale, 1);
	tempSprite.setTexture(*pTM->getTexture(TextureManager::Texture::dasherDead));
	tempSprite.setOrigin(14, 8);
	GeneralDetail dScrap(posX, posY, &tempSprite, 0, 0, 0);
	misc32x26.push_back(dScrap);
}

void detailController::addDoor(float xpos, float ypos, int x, int y, float w, float h) {
	doors.emplace_back(xpos + x * 32, ypos + y * 26, pTM->getTexture(TextureManager::Texture::introWall), 0, w, h);
}

void detailController::addPod(float xpos, float ypos, int x, int y) {
	sf::Sprite tempSprite;
	tempSprite.setOrigin(0, 30);
	tempSprite.setTexture(*pTM->getTexture(TextureManager::Texture::pod));
	misc32x26.emplace_back(xpos + x * 32, ypos + y * 26, &tempSprite, 0, 0, 0);
}

void detailController::addTeleporter(tileController& t, float posX, float posY, float width, float height) {
	Coordinate c = t.getTeleporterLoc();
	sf::Sprite tempSprites[2];
	tempSprites[0].setTexture(*pTM->getTexture(TextureManager::Texture::teleporter));
	tempSprites[1].setTexture(*pTM->getTexture(TextureManager::Texture::teleporterShadow));	
	sf::Sprite glow;
	glow.setTexture(*pTM->getTexture(TextureManager::Texture::teleporterGlow));
    teleporters.emplace_back((c.x * 32) + posX + 2, (c.y * 26) + posY - 4, tempSprites, glow, 2, width, height);
}

void detailController::update(effectsController & ef, userInterface & ui, FontController & fonts, Player & player, InputController * pInput, ScreenShakeController * pscr, sf::Time & elapsedTime) {
	float xOffset = player.getWorldOffsetX();
	float yOffset = player.getWorldOffsetY();
	std::vector<sf::Sprite *> * glow1 = ef.getGlowSprs();
	std::vector<sf::Sprite *> * glow2 = ef.getGlowSprs2();
	if (!teleporters.empty()) {
		for (auto & element : teleporters) {
			element.update(xOffset, yOffset, elapsedTime);
			if (element.smokeReady()) {
				ef.addWarpEffect(element.getxPos() - xOffset + 4 + (rand() % 6), element.getyPos() - yOffset + 2);
			}
			glow1->push_back(element.getGlow());
			glow2->push_back(element.getGlow());
		}
	}
	
	if (!lamps.empty()) {
		for (auto & element : lamps) {
			element.update(xOffset, yOffset);
			// Push the light effects back
			float xPos = element.getxPos();
			float yPos = element.getyPos();
			if (xPos < element.getWindowCenterX() + 150 && xPos > -150 && yPos < element.getWindowCenterY() + 150 && yPos > -150) {
				glow1->push_back(element.getGlow());
				glow2->push_back(element.getGlow());
			}
		}
	}
	
	if (!chests.empty()) {
		for (size_t i = 0; i < chests.size(); i++) {
			chests[i].update(xOffset, yOffset, player.getSprIndex(), pInput, elapsedTime);
			// If the user opened a chest, put it's item into the UI menu
			if (chests[i].getFrameIndex() == 3) {
				if (chests[i].isValid()) {
					ui.addItem(chests[i].getItem(), ef, chests[i].getxPos() - xOffset, chests[i].getyPos() - yOffset, fonts, player);
				}
			}
		}
	}
	
	if (!rocks.empty())
		for (auto & element : rocks)
			element.update(xOffset, yOffset);
	
	if (!doors.empty())
		for (auto & element : doors)
			element.update(xOffset, yOffset, pscr, ef, elapsedTime);
	
	if (!misc32x26.empty())
		for (auto & element : misc32x26)
			element.update(xOffset, yOffset);
	
	if (!damagedRobots.empty())
		for (auto & element : damagedRobots)
			element.update(xOffset, yOffset);
}

void detailController::killTeleporter() {
	teleporters.clear();
}

void detailController::draw(std::vector<std::tuple<sf::Sprite, float, Rendertype, float>> & gameObjects, std::vector<std::tuple<sf::Sprite, float, Rendertype, float>> & gameShadows, sf::RenderTexture& window) {
	if (!misc32x26.empty())
		for (auto & element : misc32x26)
			gameObjects.emplace_back(*element.getSprite(), element.getyPos() - 26, Rendertype::shadeDefault, 0.f);
    
	if (!teleporters.empty())
		for (auto & element : teleporters) {
			window.draw(*element.getShadow());
			window.draw(*element.getSprite());
		}
	
	if (!doors.empty())
		for (auto & element : doors)
			gameObjects.emplace_back(*element.getSprite(), element.getyPos() + 52, Rendertype::shadeDefault, 0.f);
	
	if (!rocks.empty())
		for (auto & element : rocks)
			gameObjects.emplace_back(*element.getSprite(), element.getyPos() + 22, Rendertype::shadeDefault, 0.f);
	
	if (!damagedRobots.empty())
		for (auto & element : damagedRobots)
			gameObjects.emplace_back(*element.getSprite(), element.getyPos(), Rendertype::shadeDefault, 0.f);
	
	if (!chests.empty())
		for (auto & element : chests) {
			gameObjects.emplace_back(*element.getSprite(), element.getZY(), Rendertype::shadeDefault, 0.f);
			gameShadows.emplace_back(*element.getShadow(), 0, Rendertype::shadeDefault, 0.f);
		}
	
	if (!lamps.empty()) {
		for (auto & element : lamps) {
			window.draw(*element.getSprite());
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

std::vector<TreasureChest> detailController::getChests() {
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
