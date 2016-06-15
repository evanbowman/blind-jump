//
//  player.hpp
//  BlindJump
//
//  Created by Evan Bowman on 10/9/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef player_hpp
#define player_hpp

#include <SFML/Graphics.hpp>
#include "gun.hpp"
#include "tileController.hpp"
#include "detailController.hpp"
#include "soundController.hpp"
#include "inputController.hpp"
#include "RenderType.hpp"
#include "textureManager.hpp"
#include "spriteSheet.hpp"

class Player {
	
	enum class State {
		deactivated,
		nominal,
		dashing,
		cooldown,
		dying,
		dead,
		prepdash
	};
	
private:
	//Current number of lives for the player object
	char health;
	//Also store the current position of the player object. Don't need to store
	//the previous position because the object is fixed to the center of the screen.
	int posX;
	int posY;
	//Keep track of the current image index and sprite
	uint8_t imageIndex;
	char spriteIndex;
	//The player's movement speed
	float speed;
	//In some instances we might want to deactivate the player object
	bool active;
	//The game works by keeping the player object central and moving everything else
	float worldOffsetX;
	float worldOffsetY;

	sf::Sprite shadowSprite;
	SpriteSheet<32, 32> walkDown;
	SpriteSheet<32, 32> walkUp;
	SpriteSheet<32, 32> walkLeft;
	SpriteSheet<32, 32> walkRight;
	SpriteSheet<40, 38> deathSheet;
	SpriteSheet<32, 33> dashSheet;
	
	bool deathSeq;

	int32_t animationTimer;
  
	bool CollisionLeft;
	bool CollisionRight;
	bool CollisionUp;
	bool CollisionDown;
	
	//Keep track of the button state
	bool leftPrevious;
	bool rightPrevious;
	bool upPrevious;
	bool downPrevious;
	bool zprevious;
	
	float slowSpeed;
	
	// Variables to determine whether player can take damage
	bool canhurt;
	char hurtCounter;
	
	//Declare a gun object for the player
	gun weapon;
	
	// Dodge direction and mode variables
	bool dodging;
	State state;
	int dodgeTimer;
	char dodgeDir;
	
	float colorAmount;
	
	bool gotHeart, gotCoin;
	int32_t colorTimer;
	
	//Include a function for setting the animation frame index
	void setImageIndex(char);
	
	void checkCollision(tileController&, detailController&);
	
	//Now lets declare a few variables to keep track of the last position where we sorted wall objects
	// Note: wall objects sorted by distance, but performing a sort all the time eats up the cpu usage
	float previousCheckOffsetX;
	float previousCheckOffsetY;
	
public:
	float getWorldOffsetX() const;
	float getWorldOffsetY() const;
	void setWorldOffsetX(float);
	void setWorldOffsetY(float);
	//Functions for getting the current position of the player object
	float getPosX() const;
	float getPosY() const;
        void drawController(InputController*, effectsController& ef, sf::Time &);
	void draw(std::vector<std::tuple<sf::Sprite, float, Rendertype, float>>&, std::vector<std::tuple<sf::Sprite, float, Rendertype, float>>&, tileController&, effectsController&, detailController&, SoundController&, userInterface&, InputController*, sf::RenderTexture&, FontController&, sf::Time&);
	//Construct a default player object
	Player();
	//More functions for setting the current position
	void setPosition(float, float);
	bool isActive();
	void activate();
	void deActivate();
	void deActivateFaceUp();

	void setTextures(TextureManager *);
	
	// When the player is hit shake the screen. Would pass in reference to the screen shake controller but that would create a circular dependency
	bool scrShakeState;
	char getHealth() const;
	char getSprIndex() const;
	
	// Whether or not the player is teleporting
	bool visible = false;
	
	// Accessor function to check whether the player is dead
	bool isdead();
	
	// A function to reset the player
	void reset();
	
	// Accessor function to set the player's health to full
	void fillHealth(char);
};


#endif
