//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#include "backgroundHandler.hpp"
#include "ResourcePath.hpp"

//
// TODO: This is one of the oldest files in the project, and could be
// refactored...
//

backgroundHandler::backgroundHandler() {
    xOffset = 0;
    yOffset = 0;
    xOffPrev = 0;
    yOffPrev = 0;
    posY = 0;
    bkgSprite.setTexture(
        getgResHandlerPtr()->getTexture(ResHandler::Texture::bkgOrbit));
    for (int i = 0; i < STARMAP_SIZE; i++) {
        for (int j = 0; j < STARMAP_SIZE; j++) {
            starsFar[i][j].setTexture(getgResHandlerPtr()->getTexture(
                ResHandler::Texture::bkgStarsFar));
            starsFar[i][j].setPosition(i * 128, j * 128);
            stars[i][j].setTexture(getgResHandlerPtr()->getTexture(
                ResHandler::Texture::bkgStarsNear));
            stars[i][j].setPosition(i * 128, j * 128);
        }
    }
    foregroundTreesSpr.setTexture(
        getgResHandlerPtr()->getTexture(ResHandler::Texture::introLevelMask));
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

void backgroundHandler::drawBackground(sf::RenderTexture & target,
                                       const sf::View & worldView,
                                       const Camera & camera) {
    switch (workingSet) {
    case 0:
        foregroundTreesSpr.setPosition(windowW / 2 + xOffset - 108,
                                       windowH / 2 + yOffset - 494);
        target.draw(solidBkg);
        break;

    default: {
        const sf::Vector2f cameraOffset = camera.getOffsetFromTarget();
        static const float visibleArea = 0.75f;
        static const float borderAmt = 0.115f;
        bkgSprite.setPosition(
            windowW * borderAmt + cameraOffset.x * visibleArea,
            windowH * borderAmt + cameraOffset.y * visibleArea);
        target.draw(bkgSprite);
    } break;
    }
    target.setView(camera.getOverworldView());
    if (workingSet != 0) {
        for (int i = 0; i < STARMAP_SIZE; i++) {
            for (int j = 0; j < STARMAP_SIZE; j++) {
                if (stars[i][j].getPosition().x <
                    camera.getOverworldView().getCenter().x -
                        camera.getOverworldView().getSize().x / 2 - 128) {
                    stars[i][j].setPosition(stars[i][j].getPosition().x +
                                                128 * STARMAP_SIZE,
                                            stars[i][j].getPosition().y);
                }

                if (stars[i][j].getPosition().x >
                    camera.getOverworldView().getCenter().x +
                        camera.getOverworldView().getSize().x / 2 + 128) {
                    stars[i][j].setPosition(stars[i][j].getPosition().x -
                                                128 * STARMAP_SIZE,
                                            stars[i][j].getPosition().y);
                }

                if (stars[i][j].getPosition().y >
                    camera.getOverworldView().getCenter().y +
                        camera.getOverworldView().getSize().y / 2 + 128) {
                    stars[i][j].setPosition(stars[i][j].getPosition().x,
                                            stars[i][j].getPosition().y -
                                                128 * STARMAP_SIZE);
                }

                if (stars[i][j].getPosition().y <
                    camera.getOverworldView().getCenter().y -
                        camera.getOverworldView().getSize().y / 2 - 128) {
                    stars[i][j].setPosition(stars[i][j].getPosition().x,
                                            stars[i][j].getPosition().y +
                                                128 * STARMAP_SIZE);
                }

                if (starsFar[i][j].getPosition().x <
                    camera.getOverworldView().getCenter().x -
                        camera.getOverworldView().getSize().x / 2 - 128) {
                    starsFar[i][j].setPosition(starsFar[i][j].getPosition().x +
                                                   128 * STARMAP_SIZE,
                                               starsFar[i][j].getPosition().y);
                }

                if (starsFar[i][j].getPosition().x >
                    camera.getOverworldView().getCenter().x +
                        camera.getOverworldView().getSize().x / 2 + 128) {
                    starsFar[i][j].setPosition(starsFar[i][j].getPosition().x -
                                                   128 * STARMAP_SIZE,
                                               starsFar[i][j].getPosition().y);
                }

                if (starsFar[i][j].getPosition().y >
                    camera.getOverworldView().getCenter().y +
                        camera.getOverworldView().getSize().y / 2 + 128) {
                    starsFar[i][j].setPosition(starsFar[i][j].getPosition().x,
                                               starsFar[i][j].getPosition().y -
                                                   128 * STARMAP_SIZE);
                }

                if (starsFar[i][j].getPosition().y <
                    camera.getOverworldView().getCenter().y -
                        camera.getOverworldView().getSize().y / 2 - 128) {
                    starsFar[i][j].setPosition(starsFar[i][j].getPosition().x,
                                               starsFar[i][j].getPosition().y +
                                                   128 * STARMAP_SIZE);
                }

                starsFar[i][j].setPosition(starsFar[i][j].getPosition().x -
                                               (xOffPrev - xOffset) / 3.5,
                                           starsFar[i][j].getPosition().y -
                                               (yOffPrev - yOffset) / 3.5);
                stars[i][j].setPosition(
                    stars[i][j].getPosition().x - (xOffPrev - xOffset) / 3,
                    stars[i][j].getPosition().y - (yOffPrev - yOffset) / 3);
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
    bkgSprite.setScale((x * 0.77f) / 450, (y * 0.77f) / 450);
    solidBkg.setSize(sf::Vector2f(x, y));
    // Based on initial position for first room (the only place this sprite
    // shows up in the game
    foregroundTreesSpr.setPosition(x / 2 - x / 16 - 72, y / 2 - y / 18 - 476);
}

void backgroundHandler::setBkg(unsigned char workingSet) {
    this->workingSet = workingSet;
}
