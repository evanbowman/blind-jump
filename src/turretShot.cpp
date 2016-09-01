//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#include "turretShot.hpp"

TurretShot::TurretShot(const sf::Texture & mainTxtr, const sf::Texture & glowTxtr, float x, float y, float dir) :
	Effect{x, y}
{
	spriteSheet.setTexture(mainTxtr);
	glowSprite.setTexture(glowTxtr);
	spriteSheet.setRotation(dir + 270);
	spriteSheet.setOrigin(4, 6);
	glowSprite.setOrigin(22.5, 22.5);
	direction = dir * 3.14 / 180;
	scale = 2.8;
	animationTimer = 0;
}

void TurretShot::update(sf::Time & elapsedTime) {
	position.x += scale * 1.5 * (elapsedTime.asMicroseconds() * 0.00005f) * (cos(direction));
    position.y += scale * 1.5 * (elapsedTime.asMicroseconds() * 0.00005f) * (sin(direction));
	hitBox.setPosition(position);
	spriteSheet.setPosition(position.x, position.y);
	glowSprite.setPosition(position.x, position.y + 18);
	timer += elapsedTime.asMilliseconds();
	if (timer > 600) {
	    setKillFlag();
	}
	float offset = rng::random<20>();
	glowSprite.setColor(sf::Color(230 + offset, 230 + offset, 230 + offset, 255));
	animationTimer += elapsedTime.asMilliseconds();
	if (animationTimer > 50) {
		animationTimer -= 50;
		frameIndex ^= 0x01; // Toggle between the two frames
	}
}

const TurretShot::HBox & TurretShot::getHitBox() const {
	return hitBox;
}

const sf::Sprite & TurretShot::getSprite() {
	return spriteSheet[frameIndex];
}

const sf::Sprite & TurretShot::getGlow() {
	return glowSprite;
}

void TurretShot::speedFactor(float factor) {
	scale = factor;
}
