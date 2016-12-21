#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class Entity;

using EntityRef = std::shared_ptr<Entity>;

class Entity {
protected:
    sf::Vector2f m_position;
    bool m_killFlag;
    std::string m_state;
    std::map<uint8_t, uint64_t> m_counters;
    uint16_t m_frameIndex;
    sf::Sprite * m_sprite;
    
public:
    Entity() : m_position{}, m_killFlag(false), m_state(""), m_frameIndex(0), m_sprite(nullptr) {}
    inline void setPosition(const sf::Vector2f & position) {
	m_position = position;
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
    inline const std::string & getState() const {
	return m_state;
    }
    inline void setState(const std::string & state) {
	m_state = state;
    }
    inline uint64_t getCounter(const uint8_t which) {
	return m_counters[which];
    }
    inline void setCounter(const uint8_t which, const uint64_t value) {
	m_counters[which] = value;
    }
    inline void setFrameIndex(const uint16_t frameIndex) {
	m_frameIndex = frameIndex;
    }
    inline uint16_t getFrameIndex() const {
	return m_frameIndex;
    }
    inline sf::Sprite * getSprite() {
	return m_sprite;
    }
};
