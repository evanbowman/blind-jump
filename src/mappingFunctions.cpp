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

#include "tileController.hpp"
#include "mappingFunctions.hpp"

void floodFillspread(short screen[61][61], short x, short y, short prevC, short newC) {
	// Base cases
	if (x <= 2 || x >= 59 || y <= 2 || y >= 59)
		return;
	if (screen[x][y] != prevC)
		return;
	
	// Replace replace the old element with the desired new one
	screen[x][y] = newC;
	
	// Continue in four directions
	floodFillspread(screen, x+1, y, prevC, newC);
	floodFillspread(screen, x-1, y, prevC, newC);
	floodFillspread(screen, x, y+1, prevC, newC);
	floodFillspread(screen, x, y-1, prevC, newC);
}

// It mainly finds the previous color on (x, y) and
// calls floodFillUtil()
void floodFill(short screen[61][61], short x, short y, short newC) {
	int prevC = screen[x][y];
	floodFillspread(screen, x, y, prevC, newC);
}

inline void cleanUp(short map[61][61]) {
	//Don't draw any wall objects where you don't need to! If all adjacent tiles have walls or are empty, set to zero
	for (int i = 1; i < 60; i++) {
		for (int j = 1; j < 60; j++) {
			if (map[i][j] == 1 && map[i - 1][j] < 2 && map[i + 1][j] < 2 && map[i][j - 1] < 2 && map[i][j + 1] < 2) {
				map[i][j] = 0;
			}
		}
	}
}

inline void renumber(short map[61][61]) {
	for (int i = 0; i < 61; i++) {
		for (int j = 0; j < 61; j++) {
			if (map[i][j] == 1) {
				map[i][j] = 7;
			}
			else if (map[i][j] == 0) {
				map[i][j] = 1;
			}
		}
	}
}

inline void addEdges (short map[61][61]) {
	for (int i = 0; i < 61; i++) {
		for (int j = 0; j < 61; j++) {
			if (map[i][j] == 1) {
				if (map[i][j - 1] == 5) {
					if (map[i][j + 1] != 5) {
						map[i][j] = 2;
					}
					else {
						map[i][j] = 5;
					}
				}
				else if (map[i][j + 1] == 5) {
					map[i][j] = 6;
				}
			}
		}
	}
}

inline void addCenterTiles (short map[61][61]) {
	for (int i = 0; i < 61; i++) {
		for (int j = 0; j < 61; j++) {
			if ((map[i - 1][j] == 5 || map[i - 1][j] == 3 || map[i - 1][j] == 4) && (map[i + 1][j] == 5 || map[i + 1][j] == 3 || map[i + 1][j] == 4) && (map[i][j - 1] == 5 || map[i][j - 1] == 3 || map[i][j - 1] == 4) && (map[i][j + 1] == 5 || map[i][j + 1] == 3 || map[i][j + 1] == 4)) {
				if ((std::abs(static_cast<int>(globalRNG())) % 12) > 2) {
					map[i][j] = 3;
				}
				else {
					map[i][j] = 4;
				}
			}
		}
	}
}

void condense (short map[61][61], short maptemp[61][61], char rep) {
	int count = 0;
	
	for (int i = 2; i < 59; i++) {
		for (int j = 2; j < 59; j++) {
			count = 0;
			//This random map generation algorithm is based on the work of British mathematician John Conway,
			// where new elements arise from proximity to other elements.
			if (map[i - 1][j - 1] == 1) {
				count += 1;
			}
			if (map[i + 1][j - 1] == 1) {
				count += 1;
			}
			if (map[i - 1][j + 1] == 1) {
				count += 1;
			}
			if (map[i + 1][j + 1] == 1) {
				count += 1;
			}
			if (map[i - 1][j] == 1) {
				count += 1;
			}
			if (map[i + 1][j] == 1) {
				count += 1;
			}
			if (map[i][j - 1] == 1) {
				count += 1;
			}
			if (map[i][j + 1] == 1) {
				count += 1;
			}
			
			if (map[i][j]) {
				if (count < 2) {
					maptemp[i][j] = 0;
				}
				else {
					maptemp[i][j] = 1;
				}
			}
			else {
				if (count > 5) {
					maptemp[i][j] = 1;
				}
				else {
					maptemp[i][j] = 0;
				}
			}
		}
	}
	
	for (int i = 2; i < 59; i++) {
		for (int j = 2; j < 59; j++) {
			map[i][j] = maptemp[i][j];
		}
	}
	
	if (rep > 0) {
		condense(map, maptemp, rep - 1);
	}
}

int initMapOverlay(short map[61][61]) {
	short maptemp[61][61];
	//First initialize the whole map as walls (1)
	for (int i = 0; i < 61; i++) {
		for (int j = 0; j < 61; j++) {
			map[i][j] = 0;
			maptemp[i][j] = 0;
		}
	}
	//Loop through again, and create a series of other numbers greater than 2
	for (int i = 5; i < 54; i++) {
		for (int j = 5; j < 54; j++) {
			map[i][j] = (std::abs(static_cast<int>(globalRNG())) % 2);
		}
	}
	condense(map, maptemp, 3);
	short xindex;
	short yindex;
	do {
		xindex = std::abs(static_cast<int>(globalRNG())) % 61;
		yindex = std::abs(static_cast<int>(globalRNG())) % 61;
	}
	while (map[xindex][yindex] != 1);
	floodFill(map, xindex, yindex, 5);
	int count = 0;
	for (int i = 0; i < 59; i++) {
		for (int j = 0; j < 59; j++) {
			if (map[i][j] == 5) {
				count += 1;
			}
		}
	}
	return count;
}

void combine(short map[61][61], short overlay[61][61]) {
	for (int i = 0; i < 61; i++) {
		for (int j = 0; j < 61; j++) {
			if ((overlay[i][j] == 5 && map[i][j] != 0) && (overlay[i][j] == 5 && map[i][j] != 1)) {
				if (map[i][j] == 2) {
					map[i][j] = 9;
				}
				else if (map[i][j] == 6) {
					map[i][j] = 10;
				}
				else if (map[i][j] == 5) {
					map[i][j] = 8;
				}
				else {
					map[i][j] = 11;
				}
			}
		}
	}
}

void cleanEdgesPostCombine(short map[61][61]) {
	for (int i = 1; i < 60; i++) {
		for (int j = 1; j < 60; j++) {
			if (map[i][j] == 9 && map[i][j - 1] != 8) {
				map[i][j] = 2;
			}
			else if (map[i][j] == 10 && map[i][j + 1] != 8) {
				map[i][j] = 6;
			}
		}
	}
}

bool checkFootprint(short map[61][61], int x, int y, int w, int h) {
	for (int i = x; i < x + w; i++) {
		for (int j = y; j < y + h; j++) {
			if (map[i][j] != 3 && map[i][j] != 4 && map[i][j] != 11) {
				return false;
			}
		}
	}
	return true;
}

int mappingFunction(short map[61][61], int level, bool enableGrass) {
//// TODO: BOSS LEVELS
                short maptemp[61][61];
		//First initialize the whole map as walls (1)
		for (int i = 0; i < 61; i++) {
			for (int j = 0; j < 61; j++) {
				map[i][j] = 0;
				maptemp[i][j] = 0;
			}
		}
		//Loop through again, and create a series of other numbers greater than 2
		for (int i = 16; i < 44; i++) {
			for (int j = 16; j < 44; j++) {
				map[i][j] = (std::abs(static_cast<int>(globalRNG())) % 2);
			}
		}
		condense(map, maptemp, 1);
		renumber(map);
		short xindex;
		short yindex;
		do {
			xindex = std::abs(static_cast<int>(globalRNG())) % 61;
			yindex = std::abs(static_cast<int>(globalRNG())) % 61;
		}
		while (map[xindex][yindex] != 7);
		floodFill(map, xindex, yindex, 5);
		for (int i = 2; i < 59; i++) {
			for (int j = 2; j < 59; j++) {
				if (map[i][j] == 7) {
					map[i][j] = 1;
				}
			}
		}
		// If it's a boss level, add a platform to the center of the map
		
		addEdges(map);	//Adds the top and bottom edges for the platforms
		cleanUp(map); //Gets rid of extra walls so there's no need to construct objects for them
		addCenterTiles(map);
		int count = 0;
		for (int i = 0; i < 59; i++) {
			for (int j = 0; j < 59; j++) {
				if (map[i][j] == 3 || map[i][j] == 4) {
					count += 1;
				}
				if (map[i + 1][j] == 5 && map[i - 1][j] == 5 && map[i][j + 1] == 5 && map[i][j - 1] == 5) {
					map[i][j] = 5;
				}
			}
		}
		
		// If environments are enabled, draw in some grass...
		if (enableGrass) {
			short mapOverlay[61][61];
			int count2;
			do {
				count2 = initMapOverlay(mapOverlay);
			} while (count2 < 300);
			
			combine(map, mapOverlay);
			cleanEdgesPostCombine(map);
		}
		return count;
}
