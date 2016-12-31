#pragma once
#include "spriteSheet.hpp"
#include "utility.hpp"
#include <SFML/Graphics.hpp>
#include <list>
#include <memory>

class Entity;
using EntityRef = std::shared_ptr<Entity>;

// Entities are stored in iterator-stable containers with shared ownership
// scemantics,
// storing the iterators allows for faster removal
using ClassContainerIter =
    std::map<std::string, std::list<EntityRef>>::iterator;
using ListContainerIter = std::list<EntityRef>::iterator;

class Entity {
    struct SpriteInfo {
        SpriteSheet * sheet;
        sf::Vector2f origin;
        sf::Vector2f scale;
    };

private:
    size_t m_uid;
    ClassContainerIter m_classContainerIter;
    ListContainerIter m_listContainerIter;
    sf::Vector2f m_position;
    uint16_t m_keyframe;
    float m_zOrder;
    SpriteInfo m_sprite;
    sf::Shader * m_shader;
    std::vector<float> m_shaderData;
    std::map<int, int> m_members;

public:
    Entity()
        : m_uid(0), m_position(), m_keyframe(0), m_zOrder(0.f),
          m_sprite{nullptr, {}, {1.f, 1.f}}, m_shader(nullptr) {}
    inline void setPosition(const sf::Vector2f & position) {
        m_position = position;
    }
    inline void setClassContainerIter(ClassContainerIter it) {
        m_classContainerIter = it;
    }
    inline void setListContainerIter(ListContainerIter it) {
        m_listContainerIter = it;
    }
    inline void setScale(const sf::Vector2f & scale) { m_sprite.scale = scale; }
    inline const sf::Vector2f & getScale() { return m_sprite.scale; }
    inline void setShader(sf::Shader * shader) { m_shader = shader; }
    inline sf::Shader * getShader() { return m_shader; }
    inline std::vector<float> & getShaderData() { return m_shaderData; }
    inline ListContainerIter getListIterToSelf() { return m_listContainerIter; }
    inline const std::string & getClassName() const {
        return m_classContainerIter->first;
    }
    inline void setUid(const size_t uid) { m_uid = uid; }
    inline size_t getUid() { return m_uid; }
    inline std::map<int, int> & getMemberTable() { return m_members; }
    inline const sf::Vector2f & getPosition() const { return m_position; }
    inline void setKeyframe(const uint16_t keyframe) { m_keyframe = keyframe; }
    inline uint16_t getKeyframe() const { return m_keyframe; }
    inline void setSheet(SpriteSheet * sheet) { m_sprite.sheet = sheet; }
    inline SpriteSheet * getSheet() { return m_sprite.sheet; }
    inline float getZOrder() const { return m_zOrder; }
    inline void setZOrder(const float zOrder) { m_zOrder = zOrder; }
};
