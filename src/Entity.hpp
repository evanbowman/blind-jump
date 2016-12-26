#pragma once
#include "spriteSheet.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

class Entity;
using EntityRef = std::shared_ptr<Entity>;

class Entity {
    struct SpriteInfo {
	SpriteSheet * sheet;
	sf::Vector2f origin;
	sf::Vector2f scale;
    };
private:
    sf::Vector2f m_position;
    bool m_killFlag;
    uint16_t m_keyframe;
    float m_zOrder;
    SpriteInfo m_sprite;
    std::map<int, int> m_members;

public:
    Entity()
        : m_position(), m_killFlag(false), m_keyframe(0),
          m_zOrder(0.f), m_sprite{nullptr, {}, {1.f, 1.f}} {}
    inline void setPosition(const sf::Vector2f & position) {
        m_position = position;
    }
    inline std::map<int, int> & getMemberTable() { return m_members; }
    inline const sf::Vector2f & getPosition() const { return m_position; }
    inline bool getKillFlag() const { return m_killFlag; }
    inline void setKillFlag(const bool killFlag = true) {
        m_killFlag = killFlag;
    }
    inline void setKeyframe(const uint16_t keyframe) { m_keyframe = keyframe; }
    inline uint16_t getKeyframe() const { return m_keyframe; }
    inline void setSheet(SpriteSheet * sheet) { m_sprite.sheet = sheet; }
    inline SpriteSheet * getSheet() { return m_sprite.sheet; }
    inline float getZOrder() const { return m_zOrder; }
    inline void setZOrder(const float zOrder) { m_zOrder = zOrder; }
};
