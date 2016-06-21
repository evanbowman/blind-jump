//
//  inputController.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 3/10/16.
//  Copyright © 2016 Evan Bowman. All rights reserved.
//

#pragma once
#ifndef inputController_hpp
#define inputController_hpp

#include "SFML/Graphics.hpp"

class InputController {
private:
	bool left, right, up, down, x, z, c, focused;
	
public:
	InputController();
	bool isFocused() const;
	bool leftPressed() const;
	bool rightPressed() const;
	bool upPressed() const;
	bool downPressed() const;
	bool xPressed() const;
	bool zPressed() const;
	bool cPressed() const;
	void update(sf::RenderWindow &);
};

#endif /* inputController_hpp */
