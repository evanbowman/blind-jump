//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
//                                                                        //
// This program is free software: you can redistribute it and/or modify   //
// it under the terms of the GNU General Public License as published by   //
// the Free Software Foundation, either version 3 of the License, or      //
// (at your option) any later version.                                    //
//                                                                        //
// This program is distributed in the hope that it will be useful,        //
// but WITHOUT ANY WARRANTY; without even the implied warranty of         //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
// GNU General Public License for more details.                           //
//                                                                        //
// You should have received a copy of the GNU General Public License      //
// along with this program.  If not, see <http://www.gnu.org/licenses/>.  //
//========================================================================//

#pragma once

#include "SFML/Graphics.hpp"

template <uint16_t x, uint16_t y, uint16_t w, uint16_t h>
class SpriteSheet {
private:
	sf::Sprite sprite;
	
public:
	SpriteSheet() {}

	SpriteSheet(const sf::Texture & txtr) {
		setTexture(txtr);
	}
	
	const sf::Sprite & operator[](const std::size_t idx) {
		sprite.setTextureRect(sf::IntRect(x + idx * w, y, w, h));
		return sprite;
	}
	
	const sf::Vector2f & getScale() const {
		return sprite.getScale();
	}
	
	sf::Sprite * getSpritePtr() {
		return &sprite;
	}
	
	const sf::Sprite & getSprite() {
		return sprite;
	}
	
	void setRotation(float degrees) {
		sprite.setRotation(degrees);
	}
	
	void setScale(float xScale, float yScale) {
		sprite.setScale(xScale, yScale);
	}
	
	void setPosition(float xPos, float yPos) {
		sprite.setPosition(xPos, yPos);
	}
	
	float getYpos() const {
		return sprite.getPosition().y;
	}
	
	void setTexture(const sf::Texture & texture) {
		sprite.setTexture(texture);
	}
	
	void setOrigin(const int16_t xCenter, const int16_t yCenter) {
		sprite.setOrigin(xCenter, yCenter);
	}
};
