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

#include "enemyCreationFunctions.hpp"
#include "turret.hpp"
#include "scoot.hpp"
#include "dasher.hpp"

//A function to add a turret
void addTurret(short mapArray[61][61], short descriptionArray[61][61], enemyController& en, float posX, float posY, float windowW, float windowH, std::vector<Coordinate>& emptyLocations) {
	
	//Construct a turret with all its sprites
	Turret t(en.getTurretSprites());
	
	// Randomly pick an available empty location
	int locationSelect = (std::abs(static_cast<int>(globalRNG())) % 2) ? std::abs(static_cast<int>(globalRNG())) % (emptyLocations.size() / 2 ) : std::abs(static_cast<int>(globalRNG())) % (emptyLocations.size());
	Coordinate c = emptyLocations[locationSelect];
	// Don't want to place two objects in the same position, so remove coordinate from the vector if used
	emptyLocations[locationSelect] = std::move(emptyLocations.back());
	emptyLocations.pop_back();
	
	// Use the selected coordinate to initialize the position of the enemy object
	t.setInitPosition((c.x * 32) + posX + 8 + ((std::abs(static_cast<int>(globalRNG())) % 6) - 3), (c.y * 26) + posY - 12 + ((std::abs(static_cast<int>(globalRNG())) % 6) - 3));
	//Let the turret know where the player is (always at the center of the window!
	t.setPlayerPos(windowW, windowH);
	en.addTurret(t);
}

