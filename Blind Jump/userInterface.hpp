//
//  userInterface.hpp
//  Blind Jump
//
//  Created by Evan Bowman on 10/22/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#ifndef userInterface_hpp
#define userInterface_hpp

#include <stdio.h>
#include "SFML/Graphics.hpp"
#include "fontController.hpp"
#include "effectsController.hpp"
#include "ui_bubble.hpp"
#include "inputController.hpp"
#include <array>

// This part of the code is so tied to the aesthetic appearance of the game,
// making it difficult to describe. If there is a constant and you can't tell
// where it came from, it't purpose is that it makes an effect move across
// the screen or fade in at a rate that I think looks good
class Player;

class userInterface {
    
    enum class State { opening, open, closing, closed };
    
public:
    userInterface();
    void drawMenu(sf::RenderWindow&, Player*, FontController&, effectsController&, float, float, InputController*, sf::Time&);
    // Declare selection circles to go around the object
    sf::Texture txtShadowTexture;
    sf::Sprite txtShadowSprite;
    sf::Texture deathShadowTxt;
    sf::Sprite deathShadowSpr;
    void setPosition(float, float);
    sf::Texture itemTextures[3][3];
    void addItem(char, effectsController&, float, float, FontController&, Player&);
    
    char selectedColumn;
    std::array<unsigned char, 3> rowIndices;
    
    // Function to display the death sequence
    void dispDeathSeq();
    bool isComplete();
    bool canHeal;
    
    bool isVisible();
    
    // Function to reset the ui controller
    void reset();
    
    void setEnemyValueCount(int);
    
    bool isOpen();
    
    // Accessor for blur amount
    float getBlurAmount();
    
private:
    State state;
    
    float xPos, yPos;
    
    bool visible;
    
    std::array<sf::Sprite, 3> gunSprites;
    float weaponDispOffset;
    
    // Vector to hold UI bubbles for new items (although there should only be one at a time...
    std::vector<UIBubble> uiBubbles;
    
    int enemyValueCount;
    
    // The amount of blur to use when opening the items menu
    float blurAmount;
    
    bool keyPressed;
    
    bool deathSeq, deathSeqComplete;
        
    sf::Texture selectorShadowTexture;
    sf::Sprite selectorShadowSprite;
    
    std::vector<sf::Sprite> textToDisplay;
    // Store the amount the text moves during the entry animation to reset it to the original value
    float textDisplacement;
    sf::Texture letterTextures[29];
    sf::Texture inverseLetterTextures[29];
};
#endif /* userInterface_hpp */
