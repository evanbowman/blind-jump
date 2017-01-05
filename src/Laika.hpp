#pragma once

#include "Drawable.hpp"
#include "framework/framework.hpp"
#include "spriteSheet.hpp"
#include "math.hpp"
#include "aStar.hpp"
#include "tileController.hpp"

template <typename DrawPolicy>
class _Laika : public Drawable<_Laika<DrawPolicy>, DrawPolicy>,
	       public framework::Object,
	       public std::enable_shared_from_this<_Laika<DrawPolicy>> {
public:
    enum class State {
	idle, approachPlayer
    };
    using HBox = framework::HitBox<32, 32, 0, 0>;
    _Laika(const float _xInit, const float _yInit, const sf::Texture & texture, uint8_t _map[61][61])
	: Object(_xInit, _yInit), state(State::idle), idleSheet(texture), runSheet(texture), shadow(texture), frameIndex(0), animationTimer(0), currentDir(0.f), recalc(0), map(_map) {
	idleSheet.setPosition(this->getPosition());
	idleSheet.setOrigin(16, 16);
	runSheet.setOrigin(18, 20);
	shadow.setPosition(this->getPosition());
	runSheet.setPosition(this->getPosition());
	shadow.setTextureRect(sf::IntRect(54, 57, 18, 18));
	shadow.setOrigin(9, 9);
    }
    static const int drawOffset = 6;
    const sf::Sprite & getSprite() const {
	switch (state) {
	case State::idle:
	    return idleSheet[frameIndex];

	case State::approachPlayer:
	    return runSheet[frameIndex];
	}
    }
    const sf::Sprite & getShadow() const { return shadow; }
    template <typename Game>
    void update(const sf::Time & elapsedTime, Game * pGame) {
	switch (state) {
	case State::idle: {
	    animationTimer += elapsedTime.asMicroseconds();
	    if (animationTimer > 50000) {
		animationTimer = 0;
		frameIndex += 1;
		if (frameIndex > 9) {
		    frameIndex = 0;
		}
	    }
	    idleSheet.setPosition(position);
	    if (pGame->getPlayer().getPosition().x > position.x) {
		shadow.setPosition(position.x + 2, position.y + 4);
		idleSheet.setScale(-1.f, 1.f);
	    } else {
		shadow.setPosition(position.x - 2, position.y + 4);
		idleSheet.setScale(1.f, 1.f);
	    }
	    const sf::Vector2f playerPos = pGame->getPlayer().getPosition();
	    if (math::distance(playerPos.x, playerPos.y, position.x, position.y) > 84) {
		state = State::approachPlayer;
		runSheet.setPosition(position);
	    }
	} break;

	case State::approachPlayer: {
	    animationTimer += elapsedTime.asMicroseconds();
	    if (animationTimer > 50000) {
		animationTimer = 0;
		frameIndex += 1;
		if (frameIndex > 4) {
		    frameIndex = 0;
		}
	    }
	    const sf::Vector2f playerPos = pGame->getPlayer().getPosition();
	    if (math::distance(playerPos.x, playerPos.y, position.x, position.y) < 68) {
		state = State::idle;
		path.clear();
	    }
	    tileController & tiles = pGame->getTileController();
	    if (path.empty() || recalc == 0) {
		recalc = 8;
		aStrCoordinate origin, target;
		origin.x = (position.x - tiles.posX) / 32;
		origin.y = (position.y - tiles.posY) / 26;
		target.x = (tiles.posX - playerPos.x - 12) / -32;
		target.y = (tiles.posY - playerPos.y - 32) / -26;
		if (map[target.x][target.y] == 3 || map[target.x][target.y] == 4 ||
		    map[target.x][target.y] == 5 || map[target.x][target.y] == 11 ||
		    map[target.x][target.y] == 8) {
		    path = astar_path(target, origin, map);
		    path.pop_back();
		    position.x = ((position.x - tiles.posX) / 32) * 32 + tiles.posX;
		    position.y = ((position.y - tiles.posY) / 26) * 26 + tiles.posY;
		    currentDir =
			atan2(position.y - (((path.back().y * 26) + 4 + tiles.posY)),
			      position.x - (((path.back().x * 32) + 4 + tiles.posX)));
		}
	    } else {
		static const float speed = 2.4f;
		position.x -= speed * cos(currentDir) *
		    (elapsedTime.asMicroseconds() * 0.00005f);
		position.y -= speed * sin(currentDir) *
		    (elapsedTime.asMicroseconds() * 0.00005f);
		if (fabs(position.x - (((path.back().x * 32) + 4 + tiles.posX))) < 8 &&
		    fabs(position.y - (((path.back().y * 26) + 4 + tiles.posY))) < 8) {
		    recalc--;
		    path.pop_back();
		    currentDir =
			atan2(position.y - (((path.back().y * 26) + 4 + tiles.posY)),
			      position.x - (((path.back().x * 32) + 4 + tiles.posX)));
		}
	    }
	    runSheet.setPosition(position);
	    const float xScale = cos(currentDir);
	    if (xScale > 0) {
		runSheet.setScale(1.f, 1.f);
		shadow.setPosition(position.x + 4, position.y + 4);
	    } else {
		runSheet.setScale(-1.f, 1.f);
		shadow.setPosition(position.x - 4, position.y + 4);
	    }
	} break;
	}
    }
    
private:
    State state;
    HBox hitBox;
    mutable SpriteSheet<423, 224, 32, 32> idleSheet;
    mutable SpriteSheet<391, 253, 36, 32> runSheet;
    sf::Sprite shadow;
    uint8_t frameIndex;
    int64_t animationTimer;
    uint8_t (*map)[61];
    std::vector<aStrCoordinate> path;
    float currentDir;
    int recalc;
};

