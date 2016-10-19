//========================================================================//
// Copyright (C) 2016 Evan Bowman										  //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.			  //
//========================================================================//

#include <cmath>
#include "angleFunction.hpp"
#include "player.hpp"
#include "dasher.hpp"

Dasher::Blur::Blur(framework::Sprite * spr, float xInit, float yInit) {
	this->spr = *spr;
	this->xInit = xInit;
	this->yInit = yInit;
	killflag = false;
	timer = 0;
	sf::Color c = this->spr.getColor();
	c.a -= 120;
	c.r -= 30;
	c.g -= 30;
	c.b -= 10;
	this->spr.setColor(c);
	this->spr.setPosition(xInit, yInit);
}

framework::Sprite * Dasher::Blur::getSprite() {
	return &spr;
}

void Dasher::Blur::update(const sf::Time & elapsedTime) {
	timer += elapsedTime.asMilliseconds();
	if (timer > 18) {
		timer = 0;
		sf::Color c = spr.getColor();
		if (c.a > 30) {
			c.a -= 30;
			spr.setColor(c);
		} else {
			killflag = true;
		}
	}
}

bool Dasher::Blur::getKillFlag() {
	return killflag;
}

const Dasher::HBox & Dasher::getHitBox() const {
	return hitBox;
}

Dasher::Dasher(const sf::Texture & mainTxtr, float _xPos, float _yPos)
	: Enemy(_xPos, _yPos),
	  shotCount(0),
	  state(State::idle),
	  dasherSheet(mainTxtr),
	  deathSheet(mainTxtr),
	  hSpeed(0.f),
	  vSpeed(0.f),
	  timer(0)
{
	dasherSheet.setOrigin(14, 8);
	deathSheet.setOrigin(14, 8);
	shadow.setTexture(mainTxtr);
	shadow.setTextureRect(sf::IntRect(0, 100, 18, 16));
	health = 5;
	hitBox.setPosition(xPos, yPos);
}

const framework::Sprite & Dasher::getSprite() const {
	switch(state) {
	case State::dying:
		return deathSheet[frameIndex];
			
	case State::dead:
		return deathSheet[14];

	default:
		return dasherSheet[frameIndex];
	}
}

const framework::Sprite & Dasher::getShadow() const {
	return shadow;
}

void Dasher::update(const Player * player, const std::vector<wall> & walls, EffectGroup & effects, const sf::Time & elapsedTime) {
	if (health > 0) {
		for (auto & element : effects.get<9>()) {
			if (hitBox.overlapping(element.getHitBox()) && element.checkCanPoof()) {
				if (health == 1) {
					element.disablePuff();
					element.setKillFlag();
				}
				element.poof();
				health -= 1;
				colored = true;
				colorAmount = 1.f;
			}
		}
		if (health == 0) {
			if (xPos > player->getXpos()) {
				deathSheet.setScale(1, 1);
			} else {
			    deathSheet.setScale(-1, 1);
			}
			onDeath(effects);
		}
	}
	Enemy::updateColor(elapsedTime);

	dasherSheet.setPosition(xPos + 4, yPos);
	deathSheet.setPosition(xPos + 4, yPos);
	shadow.setPosition(xPos - 4, yPos + 22);
	hitBox.setPosition(xPos, yPos);

	timer += elapsedTime.asMilliseconds();

	auto facePlayer = [this, player]() {
		if (this->xPos > player->getXpos()) {
			this->dasherSheet.setScale(1, 1);
		} else {
			this->dasherSheet.setScale(-1, 1);
		}
	};
	switch(state) {
	case State::idle:
		if (timer >= 200) {
			timer -= 200;
			const int select = rng::random<2>();
			if (select) {
				state = State::dashBegin;
				frameIndex = 1;
			} else {
				state = State::shootBegin;
				frameIndex = 3;
			}
		}
		break;

	case State::pause:
		if (timer >= 200) {
			timer -= 200;
			state = State::dashBegin;
			frameIndex = 1;
		}
		break;

	case State::shooting:
		facePlayer();
		frameTimer += elapsedTime.asMilliseconds();
		if (frameTimer > 80 && shotCount < 3) {
			frameTimer -= 80;
			shotCount++;
			if (xPos > player->getXpos()) {
				effects.add<0>(::resHandlerPtr->getTexture(ResHandler::Texture::gameObjects), xPos - 14, yPos + 2);
				effects.add<7>(::resHandlerPtr->getTexture(ResHandler::Texture::gameObjects),
							   ::resHandlerPtr->getTexture(ResHandler::Texture::redglow),
							   xPos - 12, yPos, angleFunction(target.x + 8, target.y + 8, xPos, yPos));
			} else {
				effects.add<0>(::resHandlerPtr->getTexture(ResHandler::Texture::gameObjects), xPos + 6, yPos + 2);
				effects.add<7>(::resHandlerPtr->getTexture(ResHandler::Texture::gameObjects),
							   ::resHandlerPtr->getTexture(ResHandler::Texture::redglow),
							   xPos + 4, yPos, angleFunction(target.x, target.y + 8, xPos, yPos));
			}
		}

		if (timer > 300) {
			timer -= 300;
			shotCount = 0;
			state = State::pause;
		}
		break;

	case State::shootBegin:
		facePlayer();
		if (timer > 80) {
			timer -= 80;
			frameTimer = 0;
			target = player->requestFuturePos(EnemyShot::lifetime * 1000);
			state = State::shooting;
			frameIndex = 4;
		}
		break;

	case State::dashBegin:
	begin:
		facePlayer();
		if (timer > 352) {
			timer -= 352;
			state = State::dashing;
			frameIndex = 2;
			uint8_t tries{0};
			float dir{static_cast<float>(rng::random<359>())};
			do {
				tries++;
				if (tries > 254) {
					state = State::shootBegin;
					frameIndex = 3;
					goto begin;
				}
				dir += 12;
			} while (wallInPath(walls, dir, xPos, yPos));
			hSpeed = 5 * cos(dir);
			vSpeed = 5 * sin(dir);
			if (hSpeed > 0) {
				dasherSheet.setScale(-1, 1);
				deathSheet.setScale(-1, 1);
			} else {
				dasherSheet.setScale(1, 1);
				dasherSheet.setScale(1, 1);
			}
		}
		break;

	case State::dashing:
		frameTimer += elapsedTime.asMilliseconds();
		if (frameTimer > 40) {
			frameTimer = 0;
			blurEffects.emplace_back(dasherSheet.getSpritePtr(), xPos, yPos);
		}
		if (timer > 250) {
			timer -= 250;
			state = State::dashEnd;
			frameIndex = 1;
			hSpeed = 0.f;
			vSpeed = 0.f;
		}
		
		if (Enemy::checkWallCollision(walls, xPos, yPos)) {
			hSpeed *= -1.f;
			vSpeed *= -1.f;
		}
		break;

	case State::dashEnd:
		if (timer > 150) {
			blurEffects.clear();
			timer -= 150;
			state = State::idle;
			frameIndex = 0;
		}
		break;

	case State::dying:
		frameTimer += elapsedTime.asMilliseconds();
		if (frameTimer > 53) {
			frameTimer -= 53;
			frameIndex++;
			if (frameIndex > 14)
				state = State::dead;
		}
		break;

	case State::dead:
		break;
	}

	if (!blurEffects.empty()) {
		for (auto it = blurEffects.begin(); it != blurEffects.end();) {
			if (it->getKillFlag())
				it = blurEffects.erase(it);
			else {
				it->update(elapsedTime);
				++it;
			}
		}
	}
	
	xPos += hSpeed * (elapsedTime.asMicroseconds() * 0.00005f);
	yPos += vSpeed * (elapsedTime.asMicroseconds() * 0.00005f);
}

void Dasher::onDeath(EffectGroup & effects) {
	state = State::dying;
	hSpeed = 0;
	vSpeed = 0;
	frameIndex = 0;
	killFlag = true;
	unsigned long int temp = rng::random<4>();
	if (temp == 0) {
		effects.add<4>(::resHandlerPtr->getTexture(ResHandler::Texture::gameObjects),
					   ::resHandlerPtr->getTexture(ResHandler::Texture::redglow),
					   xPos, yPos + 4, Item::Type::Heart);
	} else {
		effects.add<5>(::resHandlerPtr->getTexture(ResHandler::Texture::gameObjects),
					   ::resHandlerPtr->getTexture(ResHandler::Texture::blueglow),
					   xPos, yPos + 4, Item::Type::Coin);
	}
	effects.add<1>(::resHandlerPtr->getTexture(ResHandler::Texture::gameObjects),
				   ::resHandlerPtr->getTexture(ResHandler::Texture::fireExplosionGlow),
				   xPos, yPos - 2);
	blurEffects.clear();
}

Dasher::State Dasher::getState() const {
	return state;
}

std::vector<Dasher::Blur> * Dasher::getBlurEffects() {
	return &blurEffects;
}

const sf::Vector2f & Dasher::getScale() const {
	return deathSheet.getScale();
}
