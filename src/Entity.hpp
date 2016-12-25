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
    uint16_t m_keyframe;
    float m_zOrder;
    float m_shadowOffset;
    SpriteSheet * m_sheet;
    SpriteSheet * m_shadowSheet;
    sf::Sprite * m_glow;
    std::map<std::string, int> m_members;
    
public:
    Entity() : m_position(),
	       m_killFlag(false),
	       m_keyframe(0),
	       m_shadowOffset(0.f),
	       m_zOrder(0.f),
	       m_sheet(nullptr),
	       m_shadowSheet(nullptr),
	       m_glow(nullptr) {}

    inline float getShadowOffset() const {
	return m_shadowOffset;
    }
    inline void setShadowOffset(const float offset) {
	m_shadowOffset = offset;
    }
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
    inline void setKeyframe(const uint16_t keyframe) {
        m_keyframe = keyframe;
    }
    inline uint16_t getKeyframe() const {
	return m_keyframe;
    }
    inline void setSheet(SpriteSheet * sheet) {
	m_sheet = sheet;
    }
    inline void setShadowSheet(SpriteSheet * sheet) {
	m_shadowSheet = sheet;
    }
    inline SpriteSheet * getSheet() {
	return m_sheet;
    }
    inline SpriteSheet * getShadowSheet() {
	return m_shadowSheet;
    }
    inline sf::Sprite * getGlow() {
	return m_glow;
    }
    inline float getZOrder() const {
	return m_zOrder;
    }
    inline void setZOrder(const float zOrder) {
	m_zOrder = zOrder;
    }
};
