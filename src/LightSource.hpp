#pragma once
#include "spriteSheet.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class Light {
private:
    sf::Vector2f m_position;
    bool m_killFlag;
    SpriteSheet * m_sheet;
    sf::Vector2f m_origin;
public:
    Light() : m_position{}, m_killFlag(false), m_sheet(nullptr) {}
    inline void setPosition(const sf::Vector2f & position) {
	m_position = position;
    }
    inline const sf::Vector2f & getPosition() const { return m_position; }
    inline bool getKillFlag() const { return m_killFlag; }
    inline void setKillFlag(const bool killFlag = true) {
	m_killFlag = killFlag;
    }
    inline void setSheet(SpriteSheet * sheet) { m_sheet = sheet; }
    inline SpriteSheet * getSheet() { return m_sheet; }
    inline const sf::Vector2f & getOrigin() const { return m_origin; }
    inline void setOrigin(const sf::Vector2f & origin) { m_origin = origin; }
};
