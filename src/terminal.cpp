#include "terminal.hpp"

Terminal::Terminal(const float _xInit,
				   const float _yInit,
				   const sf::Texture & mainTxtr,
				   const sf::Texture & glowTxtr)
	: Detail(_xInit + rng::random<4, -2>(), _yInit),
	  animationTimer(0),
	  frameIndex(0),
	  screenSheet(mainTxtr),
	  mainSprite(mainTxtr),
	  shadow(mainTxtr),
	  glow(glowTxtr)
{
	shadow.setTextureRect(sf::IntRect(0, 159, 21, 12));
	mainSprite.setTextureRect(sf::IntRect(0, 132, 21, 27));
	mainSprite.setPosition(position);
	glow.setOrigin(200, 200);
	glow.setPosition(position.x + 16, position.y + 13);
	screenSheet.setPosition(position.x + 1, position.y + 2);
	shadow.setPosition(position.x, position.y + 20);
}

const sf::Sprite & Terminal::getSprite() const {
	return mainSprite;
}

const sf::Sprite & Terminal::getGlow() const {
	return glow;
}

const sf::Sprite & Terminal::getShadow() const {
	return shadow;
}

const sf::Sprite & Terminal::getScreen() const {
	return screenSheet[frameIndex];
}

void Terminal::update(const sf::Time & elapsedTime) {
	animationTimer += elapsedTime.asMicroseconds();
	static const int FLICKER_FREQUENCY = 30000;
	if (animationTimer > FLICKER_FREQUENCY) {
		animationTimer -= FLICKER_FREQUENCY;
		frameIndex ^= 1;
	}
}
