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

#include "detailParent.hpp"
#include "effectsController.hpp"

class Teleporter : public Detail {
public:
	Teleporter(float, float, const sf::Texture &, const sf::Texture &);
	const sf::Sprite & getShadow() const;
	const sf::Sprite & getSprite() const;
	bool smokeReady();
	void update(float, float, const sf::Time &);
	sf::Sprite * getGlow();
	
private:
	mutable sf::Sprite glowSprite;
	mutable sf::Sprite TeleporterSprites[2];
	int32_t smokeTimer;
};
