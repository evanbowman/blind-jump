//
//  gun.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/13/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#ifndef gun_hpp
#define gun_hpp

#include <stdio.h>
#include <SFML/Graphics.hpp>
#include "bulletType1.hpp"
#include <vector>
#include "shotPuff.hpp"
#include "effectsController.hpp"
#include "userInterface.hpp"
#include "inputController.hpp"
#include "soundController.hpp"

class gun {
private:
	//The gun object shouldn't display all the time
	int32_t timeout;
	sf::Texture gunTexture[6];
	sf::Sprite gunSprite[6];
   	int32_t bulletTimer;

	//Store the player sprite index after retrieving it
	char sprIndex;
	
	float xPos;
	float yPos;
	
public:
	//The gun object needs a default constructor
	gun();
	void setTimeout(int);
	void setPosition(float, float);
        int getTimeout(sf::Time &);
	//Define a function to return the gun sprite to the player object for drawing
	//The returned sprite depends on which way the player is facing
	sf::Sprite* getSprite(char);
	//Update the positions of all of the shot objects
        void updateShotVector(char, effectsController& ef, float, float, userInterface&, InputController*, SoundController&, int, sf::Time &);
	float getXpos();
	float getYpos();
};
#endif /* gun_hpp */
