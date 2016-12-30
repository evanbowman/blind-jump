#pragma once
#include "spriteSheet.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <list>

class Entity;
using EntityRef = std::shared_ptr<Entity>;

// Entities are stored in iterator-stable containers with shared ownership scemantics,
// storing the iterators allows for faster removal
using ClassContainerIter = std::map<std::string, std::list<EntityRef>>::iterator;
using ListContainerIter = std::list<EntityRef>::iterator;

class Entity {
    struct SpriteInfo {
        SpriteSheet * sheet;
        sf::Vector2f origin;
        sf::Vector2f scale;
    };

private:
    size_t m_eid;
    ClassContainerIter m_classContainerIter;
    ListContainerIter m_listContainerIter;
    sf::Vector2f m_position;
    bool m_killFlag;
    uint16_t m_keyframe;
    float m_zOrder;
    SpriteInfo m_sprite;
    std::map<int, int> m_members;

public:
    Entity()
        : m_eid(0), m_position(), m_killFlag(false), m_keyframe(0), m_zOrder(0.f),
          m_sprite{nullptr, {}, {1.f, 1.f}} {}
    inline void setPosition(const sf::Vector2f & position) {
        m_position = position;
    }
    inline void setClassContainerIter(ClassContainerIter it) {
	m_classContainerIter = it;
    }
    inline void setListContainerIter(ListContainerIter it) {
	m_listContainerIter = it;
    }
    inline ListContainerIter getListIterToSelf() {
	return m_listContainerIter;
    }
    inline const std::string & getClassName() const {
	return m_classContainerIter->first;
    }
    inline void setEid(const size_t eid) { m_eid = eid; }
    inline size_t getEid() { return m_eid; }
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
