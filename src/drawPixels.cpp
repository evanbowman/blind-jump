//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#include <SFML/Graphics.hpp>

void drawPixels(sf::Image & tileMap, const sf::Image & tileImage, int xIndex,
                int yIndex, int xoffset, int yoffset) {
    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < 26; j++) {
            // If the pixel color is not transparent
            sf::Color pixColor = tileImage.getPixel(i + xoffset, j + yoffset);
            if (pixColor.a != 0)
                tileMap.setPixel(xIndex * 32 + i, yIndex * 26 + j, pixColor);
        }
    }
}
