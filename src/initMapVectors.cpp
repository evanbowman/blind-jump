//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#include "initMapVectors.hpp"
#include <cmath>
#include "tileController.hpp"
#include "framework/framework.hpp"

void initMapVectors(tileController * pTiles) {
    int playerX, playerY, transporterX, transporterY;
    wall w;
    do {
        transporterX = rng::random<55>();
        transporterY = rng::random<55>();
    } while ((pTiles->mapArray[transporterX][transporterY] != 4));
    pTiles->teleporterLocation.x = transporterX;
    pTiles->teleporterLocation.y = transporterY;
    static const int mapSideLen = 61;
    for (int i = 0; i < mapSideLen; i++) {
        for (int j = 0; j < mapSideLen; j++) {
            int tileId = pTiles->mapArray[i][j];
            if (tileId == 3 || tileId == 4 || tileId == 11) {                
                Coordinate c1;
                c1.x = i;
                c1.y = j;
                // Assign coordinate priority based on distance from the transporter (and possibly items, tbd)
                c1.priority = sqrtf((i - transporterX) * (i - transporterX) + (j - transporterY) * (j - transporterY));
                pTiles->emptyMapLocations.push_back(c1);
            } else if (tileId == 2 || tileId == 9 || tileId == 6 || tileId == 10 || tileId == 1) {
                    //Set the wall's x position
                    w.setXinit((i * 32));
                    w.setYinit((j * 26));
                    w.setPosition(w.getXinit(), w.getYinit());
                    //Push it back
                    pTiles->walls.push_back(w);
            }
        }
    }
    // Sort the empty location vector based on coordinate priorities
    std::sort(pTiles->emptyMapLocations.begin(), pTiles->emptyMapLocations.end(), [](const Coordinate c1, const Coordinate c2) {
            return c1.priority < c2.priority;
        });
    playerX = pTiles->emptyMapLocations.back().x;
    playerY = pTiles->emptyMapLocations.back().y;
    static const uint8_t tileWidth = 32;
    static const uint8_t tileHeight = 26;
    pTiles->posX = -(tileWidth * playerX);
    pTiles->posY = -(tileHeight * playerY) - 4;
    pTiles->emptyMapLocations.pop_back();
}
