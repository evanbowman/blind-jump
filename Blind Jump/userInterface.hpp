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

// This part of the code is so tied to the aesthetic appearance of the game,
// making it difficult to describe. If there is a constant and you can't tell
// where it came from, it't purpose is that it makes an effect move across
// the screen or fade in at a rate that I think looks good
class Player;

class userInterface {
public:
    userInterface();
    void drawMenu(sf::RenderWindow&, Player*, unsigned char*, FontController&, effectsController&, float, float, InputController*);
    sf::CircleShape circle;
    // Declare selection circles to go around the object
    sf::CircleShape selCircle1;
    sf::CircleShape selCircle2;
    sf::CircleShape selCircle3;
    sf::CircleShape selCircle4;
    sf::CircleShape circle2;
    sf::CircleShape selectedCircle;
    sf::RectangleShape overlayRect;
    sf::Texture txtShadowTexture;
    sf::Sprite txtShadowSprite;
    sf::Texture deathTextTexture;
    sf::Sprite deathTextSprite;
    sf::Texture deathShadowTxt;
    sf::Sprite deathShadowSpr;
    sf::Texture weaponNames[6];
    sf::Sprite weaponName;
    sf::RectangleShape weaponNameUnderscore;
    bool visible;
    float r;
    float r2;
    void setPosition(float, float);
    float xPos;
    float yPos;
    float rectAlpha;
    float angle;
    sf::Texture itemTextures[6];
    sf::Sprite itemSprites[5];
    void addItem(char, effectsController&, float, float, FontController&, Player&);
    sf::CircleShape itemCircle[4];
    bool closing;
    // Keep track of whether the user has pressed key with state variable
    char selectDir = 'L';
    
    // Function to display the death sequence
    void dispDeathSeq();
    bool isComplete();
    bool canHeal;
    
    bool isVisible();
    
    // Function to reset the ui controller
    void reset();
    
    void setEnemyValueCount(int);
    char getCurrentItem();
    
private:
    char items[4];
    char selected;
    bool msgOpenSignal;
    bool msgOpened;
    bool msgVisible;
    
    // Vector to hold UI bubbles for new items (although there should only be one at a time...
    std::vector<UIBubble> uiBubbles;
    
    int enemyValueCount;
    
    bool deathSeq;
    bool deathSeqComplete;
    
    float msgBoxXorigin;
    float msgBoxYorigin;
    float msgBoxWidth;
    float msgBoxHeight;
    
    sf::Texture selectorShadowTexture;
    sf::Sprite selectorShadowSprite;
    
    std::vector<sf::Sprite> textToDisplay;
    // Store the amount the text moves during the entry animation to reset it to the original value
    float textDisplacement;
    sf::Texture letterTextures[29];
    sf::Texture inverseLetterTextures[29];
};
#endif /* userInterface_hpp */
