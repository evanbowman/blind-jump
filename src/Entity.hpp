#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "spriteSheet.hpp"

class Entity;
using EntityRef = std::shared_ptr<Entity>;

class Entity {
private:
    sf::Vector2f m_position;
    bool m_killFlag;
    uint16_t m_frameIndex;
    SpriteSheet * m_sheet;
    SpriteSheet * m_shadow;
    sf::Sprite * m_glow;
    std::map<std::string, int> m_members;
    
public:
    Entity() : m_position{},
	       m_killFlag(false),
	       m_frameIndex(0),
	       m_sheet(nullptr),
	       m_shadow(nullptr),
	       m_glow(nullptr) {}
    inline void setPosition(const sf::Vector2f & position) {
	m_position = position;
    }
    inline std::map<std::string, int> & getMemberTable() {
	return m_members;
    }
    inline const sf::Vector2f & getPosition() const {
	return m_position;
    }
    inline bool getKillFlag() const {
	return m_killFlag;
    }
    inline void setKillFlag(const bool killFlag = true) {
	m_killFlag = killFlag;
    }
    inline void setFrameIndex(const uint16_t frameIndex) {
	m_frameIndex = frameIndex;
    }
    inline uint16_t getFrameIndex() const {
	return m_frameIndex;
    }
    inline void setSheet(SpriteSheet * sheet) {
	m_sheet = sheet;
    }
    inline SpriteSheet * getSheet() {
	return m_sheet;
    }
    inline SpriteSheet * getShadow() {
	return m_shadow;
    }
    inline sf::Sprite * getGlow() {
	return m_glow;
    }
};
