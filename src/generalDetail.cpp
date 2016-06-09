//
//  generalDetail.cpp
//  Blind Jump
//
//  Created by Evan Bowman on 2/11/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#include "generalDetail.hpp"

GeneralDetail::GeneralDetail(float xStart, float yStart, sf::Sprite* spr, int len, float width, float height) : detailParent(xStart, yStart, len, width, height) {
  this->spr = *spr;
}

void GeneralDetail::update(float xOffset, float yOffset) {
  xPos = xOffset + xInit;
  yPos = yOffset + yInit;
  spr.setPosition(xPos - 3, yPos);
}

sf::Sprite* GeneralDetail::getSprite() {
  return &spr;
}

