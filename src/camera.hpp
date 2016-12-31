#pragma once
#include "Entity.hpp"
#include "calc.hpp"
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <array>
#include <utility>
#include <vector>
#include <unordered_map>

class Camera {
    std::weak_ptr<Entity> targetRef;
    sf::View overworldView, windowView;
    sf::Vector2f startPosition, midpoint, buffer, currentPosition;
    sf::Vector2u windowSize;
    bool isShaking;
    uint8_t shakeIndex;
    int64_t shakeTimer, trackingTimer;
    float shakeIntensity;
    enum class State { trackMidpoint, followPlayer, foundEnemy };
    State state;
    void upscaleWindowView();
    float rateFactor;
    std::unordered_map<std::string, int> watchList;

public:
    Camera(const sf::Vector2f & viewPort, const sf::Vector2u &);
    void update(const sf::Time &, const std::vector<sf::Vector2f> &);
    void setTarget(std::shared_ptr<Entity>);
    void snapToTarget();
    void setOffset(const sf::Vector2f &);
    const sf::View & getOverworldView() const;
    const sf::View & getWindowView() const;
    void shake(float);
    void setOverworldView(const sf::View &);
    void setWindowView(const sf::View &);
    bool moving() const;
    void setRateFactor(const float);
    sf::Vector2f getOffsetFromStart() const;
    sf::Vector2f getOffsetFromTarget() const;
    std::unordered_map<std::string, int> & getWatchList();
};
