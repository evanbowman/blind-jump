//========================================================================//
// Copyright (C) 2016 Evan Bowman                                         //
// Liscensed under GPL 3, see: <http://www.gnu.org/licenses/>.            //
//========================================================================//

#pragma once
#include "colors.hpp"
#include "easingTemplates.hpp"
#include "inputController.hpp"
#include "resourceHandler.hpp"
#include "shutdownSignal.hpp"
#include <SFML/Graphics.hpp>
#include <array>

class Player;
class Game;

//
// TODO: Combine ui frontend and ui backend into one class, neater that way?
//

namespace ui {
class PowerupBubble {
public:
    void init(float);
    void setRadius(float, float);
    void setPosition(float, float);
    sf::Vector2f getPosition();
    float getRadius();
    void setAlpha(uint8_t);
    const sf::CircleShape & getShape() const;
    const sf::Sprite & getSprite();
    void setFrame(size_t);

private:
    sf::CircleShape bubble;
    framework::SpriteSheet<0, 0, 46, 46> powerupSheet;
};

class Frontend {
public:
    enum class Text {
        resumeText,
        quitText,
        healthNumText,
        scoreText,
        waypointText,
        heart,
        coin,
        powerupText
    };
    Frontend(sf::View, float, float);
    void init();
    void setWaypointText(const int);
    void setZoneText(char);
    void draw(sf::RenderWindow &);
    void setTextAlpha(uint8_t, Text);
    void setBubbleAlpha(uint8_t);
    void setBubbleRadius(float);
    void setTextOffset(float, float, Text);
    void updateHealth(char);
    void updateMaxHealth(char);
    void drawTitle(unsigned char, sf::RenderWindow &);
    void drawDeathText(unsigned char, sf::RenderWindow &);
    char getMaxHealth() const;
    sf::Text * getTitle();
    sf::Text * getDeathText();
    void reset();
    void resetWPText();
    void resetHPText();
    void resetSCText();
    void updateScore(int);
    int getScore();
    void setBarWidth(float);

private:
    float scale;
    sf::Texture texture;
    sf::View fontView;
    sf::Text waypointText, titleText, deathText, scoreText, healthNumText;
    sf::Text resumeText, quitText, powerupText;
    char maxHealth, health;
    bool healthModified, scoreModified;
    int score;
    PowerupBubble powerupBubble;
    float windowCenterX, windowCenterY;
    sf::Clock wpTextDisplayTimer, healthDisplayTimer, scoreDisplayTimer;
    sf::ConvexShape heart;
    sf::CircleShape coin;
    float barWidth;
    sf::RectangleShape powerupBarFront, powerupBarBack;
};

class Backend {
public:
    enum class State {
        closed,
        deathScreenEntry,
        deathScreen,
        deathScreenExit,
        statsScreen,
        complete,
        menuScreenEntry,
        menuScreenExit,
        menuSelectionTransition,
        menuScreen
    };
    enum class PowerupBubbleState {
        triggered,
        opening,
        open,
        closing,
        closed,
        dormant
    };
    Backend();
    void update(Game * game, const sf::Time &);
    void draw(sf::RenderWindow &, ui::Frontend &);
    void dispDeathSeq();
    bool isComplete();
    bool canHeal;
    bool isOpen() const;
    float getDesaturateAmount();
    State getState() const;
    void reset();
    void setEnemyValueCount(int);
    bool blurEnabled();
    bool desaturateEnabled();
    float getBlurAmount();
    PowerupBubbleState getPowerupBubbleState() const;

private:
    State state;
    PowerupBubbleState powerupBubbleState;
    int menuItemSelected;
    int menuItemTarget;
    int32_t timer, timerAlt;
    int64_t powerupTimer, powerupBubbleTimer;
    bool dispPowerupBar;
    float blurAmount, desaturateAmount;
};
}
