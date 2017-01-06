#pragma once

#include "Drawable.hpp"
#include <cmath>
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
	idle, returnToPlayer, approachEnemy
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
    static const int drawOffset = -20;
    
    const sf::Sprite & getSprite() const {
	switch (state) {
	case State::idle:
	    return idleSheet[frameIndex];

	case State::approachEnemy:
	case State::returnToPlayer:
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
		runSheet.setScale(-1.f, 1.f);
	    } else {
		shadow.setPosition(position.x - 2, position.y + 4);
		idleSheet.setScale(1.f, 1.f);
		runSheet.setScale(1.f, 1.f);
	    }
	    const sf::Vector2f playerPos = pGame->getPlayer().getPosition();
	    if (math::distance(playerPos.x, playerPos.y, position.x, position.y) > 64) {
		state = State::returnToPlayer;
		runSheet.setPosition(position);
	    } else {
		auto & enemies = pGame->getEnemyController();
		std::vector<std::shared_ptr<framework::Object>> enemyVec;
		const sf::View & cv = pGame->getCamera().getOverworldView();
		const auto collect = [&cv, &enemyVec](auto & vec) {
					 for (auto & element : vec) {
					     if (isWithinView(*element, cv)) {
						 enemyVec.push_back(element);
					     }
					 }
				     };
		collect(enemies.getCritters());
		collect(enemies.getScoots());
		collect(enemies.getDashers());
		collect(enemies.getTurrets());
		if (!enemyVec.empty()) {
		    std::sort(enemyVec.begin(), enemyVec.end(),
			      [this](const auto & lhs, const auto & rhs) {
				  const sf::Vector2f & posLhs = lhs->getPosition();
				  const sf::Vector2f & posRhs = rhs->getPosition();
				  const float distLhs = math::distance(this->position.x, this->position.y, posLhs.x, posLhs.y);
				  const float distRhs = math::distance(this->position.x, this->position.y, posRhs.x, posRhs.y);
				  return distLhs > distRhs;
			      });
		    this->targetEnemy = enemyVec.back();
		    state = State::approachEnemy;
		    runSheet.setPosition(position);
		}
	    }
	} break;

	case State::approachEnemy: {
	    animationTimer += elapsedTime.asMicroseconds();
	    if (animationTimer > 50000) {
		animationTimer = 0;
		frameIndex += 1;
		if (frameIndex > 4) {
		    frameIndex = 0;
		}
	    }
	    runSheet.setPosition(position);
	    const float xScale = cos(currentDir);
	    if (xScale > 0) {
		runSheet.setScale(1.f, 1.f);
		idleSheet.setScale(1.f, 1.f);
		shadow.setPosition(position.x, position.y + 4);
	    } else {
		runSheet.setScale(-1.f, 1.f);
		idleSheet.setScale(-1.f, 1.f);
		shadow.setPosition(position.x, position.y + 4);
	    }
	    if (auto sp = targetEnemy.lock()) {
		approachTarget(elapsedTime, pGame, sp->getPosition(), 2.3);
	    } else {
		idleSheet.setPosition(position);
		state = State::idle;
	    }
	} break;

	case State::returnToPlayer: {
	    animationTimer += elapsedTime.asMicroseconds();
	    if (animationTimer > 50000) {
		animationTimer = 0;
		frameIndex += 1;
		if (frameIndex > 4) {
		    frameIndex = 0;
		}
	    }
	    const sf::Vector2f playerPos = pGame->getPlayer().getPosition();
	    const float dist = math::distance(playerPos.x, playerPos.y, position.x, position.y);
	    if (dist < 48) {
		state = State::idle;
		idleSheet.setPosition(this->position);
		path.clear();
	    } else {
		float normal = fmax(180.f - (dist + 48.f), 0) / 180.f;
		approachTarget(elapsedTime, pGame, playerPos, (1.f - normal) * 2.8);
	    }
	    runSheet.setPosition(position);
	    const float xScale = cos(currentDir);
	    if (xScale > 0) {
		runSheet.setScale(1.f, 1.f);
		idleSheet.setScale(1.f, 1.f);
		shadow.setPosition(position.x, position.y + 4);
	    } else {
		runSheet.setScale(-1.f, 1.f);
		idleSheet.setScale(-1.f, 1.f);
		shadow.setPosition(position.x, position.y + 4);
	    }
	} break;
	}
    }

    template <typename Game>
    void approachTarget(const sf::Time & elapsedTime, Game * pGame,
			const sf::Vector2f & destination, const float speed) {
	tileController & tiles = pGame->getTileController();
	if (path.empty() || recalc == 0) {
	    recalc = 8;
	    aStrCoordinate origin, target;
	    origin.x = (position.x - tiles.posX) / 32;
	    origin.y = (position.y - tiles.posY) / 26;
	    target.x = (tiles.posX - destination.x - 12) / -32;
	    target.y = (tiles.posY - destination.y - 32) / -26;
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
    std::weak_ptr<framework::Object> targetEnemy;
};

