//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#include "backgroundHandler.hpp"
#include "ResourcePath.hpp"

//
// TODO: This is one of the oldest files in the project, and could be refactored...
//

backgroundHandler::backgroundHandler() {
	xOffset = 0;
	yOffset = 0;
	xOffPrev = 0;
	yOffPrev = 0;
	posY = 0;
	bkgSprite.setTexture(global::resHandlerPtr->getTexture(ResHandler::Texture::bkgOrbit));
	for (int i = 0; i < STARMAP_SIZE; i++) {
		for (int j = 0; j < STARMAP_SIZE; j++) {
			starsFar[i][j].setTexture(global::resHandlerPtr->getTexture(ResHandler::Texture::bkgStarsFar));
			starsFar[i][j].setPosition(i * 128, j * 128);
			stars[i][j].setTexture(global::resHandlerPtr->getTexture(ResHandler::Texture::bkgStarsNear));
			stars[i][j].setPosition(i * 128, j * 128);
			
		}
	}
	foregroundTreesSpr.setTexture(global::resHandlerPtr->getTexture(ResHandler::Texture::introLevelMask));
	solidBkg.setFillColor(sf::Color(17, 45, 50));
	workingSet = 1;
}

void backgroundHandler::drawForeground(sf::RenderTexture & window) {
	switch (workingSet) {
		case 0:
			window.draw(foregroundTreesSpr);
			break;
			
		default:
			break;
	}
}

void backgroundHandler::drawBackground(sf::RenderTexture & target, const sf::View & worldView, const Camera & camera) {
	switch (workingSet) {
		case 0:
			foregroundTreesSpr.setPosition(windowW / 2 + xOffset - 108, windowH / 2 + yOffset - 494);
			target.draw(solidBkg);
			break;
			
		default:
		    target.draw(bkgSprite);
			break;
	}
	target.setView(camera.getView());
	if (workingSet != 0) {
		for (int i = 0; i < STARMAP_SIZE; i++) {
			for (int j = 0; j < STARMAP_SIZE; j++) {
				if (stars[i][j].getPosition().x < camera.getView().getCenter().x - camera.getView().getSize().x / 2 - 128) {
					stars[i][j].setPosition(stars[i][j].getPosition().x + 128 * STARMAP_SIZE, stars[i][j].getPosition().y);
				}
				
				if (stars[i][j].getPosition().x > camera.getView().getCenter().x + camera.getView().getSize().x / 2 + 128) {
					stars[i][j].setPosition(stars[i][j].getPosition().x - 128 * STARMAP_SIZE, stars[i][j].getPosition().y);
				}
				
				if (stars[i][j].getPosition().y > camera.getView().getCenter().y + camera.getView().getSize().y / 2 + 128) {
					stars[i][j].setPosition(stars[i][j].getPosition().x, stars[i][j].getPosition().y - 128 * STARMAP_SIZE);
				}
				
				if (stars[i][j].getPosition().y < camera.getView().getCenter().y - camera.getView().getSize().y / 2 - 128) {
					stars[i][j].setPosition(stars[i][j].getPosition().x, stars[i][j].getPosition().y + 128 * STARMAP_SIZE);
				}
				
				if (starsFar[i][j].getPosition().x < camera.getView().getCenter().x - camera.getView().getSize().x / 2 - 128) {
					starsFar[i][j].setPosition(starsFar[i][j].getPosition().x + 128 * STARMAP_SIZE, starsFar[i][j].getPosition().y);
				}
				
				if (starsFar[i][j].getPosition().x > camera.getView().getCenter().x + camera.getView().getSize().x / 2 + 128) {
					starsFar[i][j].setPosition(starsFar[i][j].getPosition().x - 128 * STARMAP_SIZE, starsFar[i][j].getPosition().y);
				}
				
				if (starsFar[i][j].getPosition().y > camera.getView().getCenter().y + camera.getView().getSize().y / 2 + 128) {
					starsFar[i][j].setPosition(starsFar[i][j].getPosition().x, starsFar[i][j].getPosition().y - 128 * STARMAP_SIZE);
				}
				
				if (starsFar[i][j].getPosition().y < camera.getView().getCenter().y - camera.getView().getSize().y / 2 - 128) {
					starsFar[i][j].setPosition(starsFar[i][j].getPosition().x, starsFar[i][j].getPosition().y + 128 * STARMAP_SIZE);
				}
				
				starsFar[i][j].setPosition(starsFar[i][j].getPosition().x - (xOffPrev - xOffset)/3.5, starsFar[i][j].getPosition().y - (yOffPrev - yOffset)/3.5);
				stars[i][j].setPosition(stars[i][j].getPosition().x - (xOffPrev - xOffset)/3, stars[i][j].getPosition().y - (yOffPrev - yOffset)/3);
				target.draw(starsFar[i][j]);
				target.draw(stars[i][j]);
			}
		}
	}
	target.setView(worldView);
	xOffPrev = xOffset;
	yOffPrev = yOffset;
}

void backgroundHandler::setOffset(float x, float y) {
	xOffset = x;
	yOffset = y;
}

void backgroundHandler::setPosition(float x, float y) {
	posX = x;
	posY = y;
}

void backgroundHandler::giveWindowSize(float x, float y) {
	windowW = x;
	windowH = y;
	for (auto i = 0; i < 3; i++) {
		// Scale the background sprites based on the window size, that way they always fill the game window
		bkgSprite.setScale(x / 450, y / 450);
	}
	
	solidBkg.setSize(sf::Vector2f(x, y));
	// Based on initial position for first room (the only place this sprite shows up in the game
	foregroundTreesSpr.setPosition(x / 2 - x / 16 - 72, y / 2 - y / 18 - 476);
}

void backgroundHandler::setBkg(unsigned char workingSet) {
	this->workingSet = workingSet;
}
