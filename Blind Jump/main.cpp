//
//  main.cpp
//  BlindJump
//
//  Created by Evan Bowman on 10/9/15.
//  Copyright © 2015 Evan Bowman. All rights reserved.
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "player.hpp"
#include "backgroundHandler.hpp"
#include <cmath>
#include <SFML/Window.hpp>
#include "gameMap.hpp"
#include "ResourcePath.hpp"
#include "inputController.hpp"

#define CREDITS_DISP_LENGTH 370
    
int main(int, char const**) {
    //Set the seed for random generation
    srand((unsigned int)time(0));   // Compiler warning for implicit conversion, so wrote it out explicitly (seeding with a time_t is probably fine though...)
    // An variable that can be decremented to make the 'Press Z' text flash
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    
    float aspectRatio = (float)desktop.width / (float)desktop.height;
    float windowWidth = 450;
    float windowHeight = 450;
    if (aspectRatio > 1) {
        float windowAspect;
        do {
            windowWidth += 0.025;
            windowHeight -= 0.025;
            windowAspect = windowWidth / windowHeight;
        }
        while (fabs(aspectRatio - windowAspect) > 0.005);
    }
    
    // Boolean that stores whether the game is on the title screen
    bool title = false;
    // Variable that enables drawing the cutscene
    // For transitions, simply use a rectangle primitive shape
    sf::RectangleShape overlayRect;
    sf::Vector2f v1(windowWidth, windowHeight);
    overlayRect.setSize(v1);
    overlayRect.setFillColor(sf::Color(5,5,25,255));
    
    sf::Texture vignetteTexture;
    vignetteTexture.loadFromFile(resourcePath() + "vignetteMask.png");
    vignetteTexture.setSmooth(true);
    sf::Sprite vignetteSpr;
    vignetteSpr.setTexture(vignetteTexture);
    vignetteSpr.setScale(windowWidth / 450, windowHeight / 450);
    
    // Wraps input from keyboard and gamepad
    InputController input;
    
    //Initialize the map
    GameMap Map(windowWidth, windowHeight, &vignetteTexture, &input);
    
    // Setup the window context settings
    sf::ContextSettings settings;
    settings.antialiasingLevel = 6;
    
    sf::RenderWindow window(sf::VideoMode(windowWidth * 2, windowHeight * 2), "Blind Jump", sf::Style::Fullscreen, settings);
    // Hide cursor inside the window
    window.setMouseCursorVisible(false);
    //Since the view is half the size of the window, the interface will have a sort of stylistic pixelated apperance
    sf::View view(sf::FloatRect(0, 0, windowWidth, windowHeight));
    //Apply the view to the window.
    window.setView(view);
    //Set the framerate to 60, so that the window doesn't update constantly
    window.setFramerateLimit(60);
    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    
    // Set the game icon
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    // Load start screen texture and apply it to a sprite object
    

    // For scene transitions:
    sf::RectangleShape transition;
    transition.setScale(windowWidth / 450, windowHeight / 450);
    transition.setFillColor(sf::Color(37, 36, 72, 255));
    
    // Load opening credits text and create a background
    sf::Texture creditsTextTxtr;
    sf::Sprite creditsTextSpr;
    sf::RectangleShape creditsBkg;
    creditsBkg.setSize(sf::Vector2f(windowWidth, windowHeight));
    creditsBkg.setFillColor(sf::Color(47, 51, 98, 255));
    
    // Start the game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
        }
        
        // Clear screen
        window.clear();
        
        input.update();
        
        //Update and draw all of the game objects by calling the update function within mapInit and passing in a reference to the window
        if (!title) {   // If not on the title screen
                Map.update(window);
            
            if (Map.getTeleporterCond()) {                     //Change the condition later to check for a value within Map
                Map.Reset();
            }
        }
        
        else {
            if (input.zPressed() && title) {
                title = false;
            }
            //window.draw(titlebkgSpr);
            //window.draw(titleSpr[3]);
            
            //window.draw(titleSpr[3]);
            //window.draw(titleSpr[3]);
            //window.draw(titleSpr[2]);
            //window.draw(titleSpr[0]);
            //window.draw(titleSpr[1]);
        }
        
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}

