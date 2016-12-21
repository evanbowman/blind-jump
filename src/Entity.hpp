#include <SFML/Graphics.hpp>
#include <memory>

class Entity {
protected:
    sf::Vector2f m_position;
    bool m_killFlag;
    std::string m_state;
    std::map<uint8_t, uint64_t> m_timers;
public:
    Entity() : m_position{}, m_killFlag(false), m_state("") {}
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
    inline uint64_t getTimer(const uint8_t which) {
	return m_timers[which];
    }
    inline void setTimer(const uint8_t which, const uint64_t value) {
	m_timers[which] = value;
    }
};
