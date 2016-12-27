#include "camera.hpp"

#include "easingTemplates.hpp"

Camera::Camera(const sf::Vector2f & viewPort, const sf::Vector2u & _windowSize)
    : overworldView(sf::Vector2f(viewPort.x / 2, viewPort.y / 2), viewPort),
      startPosition(overworldView.getCenter()), currentPosition(startPosition),
      windowSize(_windowSize), isShaking(false), shakeIndex(0), shakeTimer(0),
      trackingTimer(0), shakeIntensity(0.f), state(State::followPlayer) {}

void Camera::update(const sf::Time & elapsedTime,
                    const std::vector<sf::Vector2f> & targets) {
    if (auto sharedTarget = targetRef.lock()) {
        overworldView.setCenter(sharedTarget->getPosition());
        float lerpSpeed;
        if ((state == State::trackMidpoint || state == State::foundEnemy) &&
            targets.empty()) {
            state = State::followPlayer;
            trackingTimer = 0;
        }
        switch (state) {
        case State::followPlayer:
            lerpSpeed = math::clamp(elapsedTime.asMicroseconds() * 0.0000025f,
                                    0.f, 1.f);
            currentPosition = math::lerp(sharedTarget->getPosition(),
                                         currentPosition, lerpSpeed);
            if (!targets.empty()) {
                state = State::foundEnemy;
                trackingTimer = 0;
            }
            break;

        case State::trackMidpoint: {
            lerpSpeed = math::clamp(elapsedTime.asMicroseconds() * 0.0000025f,
                                    0.f, 1.f);
            sf::Vector2f aggregate;
            float divisor = 0;
            for (const auto & vec : targets) {
                aggregate += vec;
                ++divisor;
            }
            aggregate /= divisor;
            // Enemies entering and leaving the camera view creates jarring
            // shifts
            // so I'm using a buffer of the average enemy positions
            buffer = math::lerp(buffer, aggregate, lerpSpeed * 0.1f);
            midpoint = math::lerp(sharedTarget->getPosition(), buffer, 0.78);
            currentPosition = math::lerp(midpoint, currentPosition, lerpSpeed);
        } break;

        case State::foundEnemy: {
            lerpSpeed = math::clamp(elapsedTime.asMicroseconds() * 0.0000025f,
                                    0.f, 1.f);
            sf::Vector2f aggregate;
            float divisor = 0;
            for (const auto & vec : targets) {
                aggregate += vec;
                ++divisor;
            }
            aggregate /= divisor;
            trackingTimer += elapsedTime.asMicroseconds();
            float targetWeight =
                1.f -
                0.22f * Easing::easeIn<1>(trackingTimer,
                                          static_cast<int64_t>(900000));
            midpoint = math::lerp(sharedTarget->getPosition(), aggregate,
                                  targetWeight);
            currentPosition = math::lerp(midpoint, currentPosition, lerpSpeed);
            if (trackingTimer > 900000) {
                state = State::trackMidpoint;
                buffer = aggregate;
            }
        } break;
        }
        // } else {
        //     state = State::followPlayer;
        //     lerpSpeed =
        // 	math::clamp(elapsedTime.asMicroseconds() * 0.0000055f, 0.f, 1.f);
        //     currentPosition =
        // 	math::lerp(sharedTarget->getPosition(), currentPosition, lerpSpeed);
        // }
        if (isShaking) {
            shakeTimer += elapsedTime.asMicroseconds();
            if (shakeTimer > 50000) {
                shakeTimer = 0;
                shakeIndex += 1;
                if (shakeIndex > 4) {
                    shakeIndex = 4;
                    isShaking = false;
                    shakeTimer = 0;
                }
            }
            static const std::array<int, 5> shakeConstants = {
                {3, -5, 3, -2, 1}};
            float shakeOffset = shakeConstants[shakeIndex];
            currentPosition.y += shakeOffset * shakeIntensity;
        }
        const sf::Vector2f cameraTargetOffset = getOffsetFromTarget();
        const sf::Vector2f windowViewSize = windowView.getSize();
        const sf::Vector2f overworldViewSize = overworldView.getSize();
        const sf::Vector2f scaleVec(windowViewSize.x / overworldViewSize.x,
                                    windowViewSize.y / overworldViewSize.y);
        const sf::Vector2f scaledCameraOffset(cameraTargetOffset.x * scaleVec.x,
                                              cameraTargetOffset.y *
                                                  scaleVec.y);
        windowView.setCenter(windowSize.x / 2.f + scaledCameraOffset.x,
                             windowSize.y / 2.f + scaledCameraOffset.y);
        const sf::Vector2f & targetPos = sharedTarget->getPosition();
        sf::Listener::setPosition(targetPos.x, targetPos.y, 35.f);
        static const float listenerDistFromScreen = 35.f;
    }
}

const sf::View & Camera::getOverworldView() const { return overworldView; }

const sf::View & Camera::getWindowView() const { return windowView; }

void Camera::setOffset(const sf::Vector2f & offset) {
    if (auto sharedTarget = targetRef.lock()) {
        const sf::Vector2f & targetPos = sharedTarget->getPosition();
        sf::Vector2f newPos;
        newPos.x = targetPos.x + offset.x;
        newPos.y = targetPos.y + offset.y;
        overworldView.setCenter(newPos);
        currentPosition = newPos;
    }
}

void Camera::setTarget(std::shared_ptr<Entity> target) {
    this->targetRef = target;
}

void Camera::snapToTarget() {
    if (auto sharedTarget = targetRef.lock()) {
        overworldView.setCenter(sharedTarget->getPosition());
        startPosition = overworldView.getCenter();
        currentPosition = startPosition;
    } else {
        throw std::runtime_error(
            "Error: cannot snapToTarget because camera target is not set \
or has been deallocated");
    }
}

void Camera::setOverworldView(const sf::View & _overworldView) {
    overworldView = _overworldView;
}

void Camera::setWindowView(const sf::View & _windowView) {
    windowView = _windowView;
}

bool Camera::moving() const {
    if (auto sharedTarget = targetRef.lock()) {
        const sf::Vector2f playerPos = sharedTarget->getPosition();
        if (std::abs(playerPos.x - currentPosition.x) < 0.5f &&
            std::abs(playerPos.y - currentPosition.y) < 0.5f) {
            return false;
        }
        return true;
    }
    return false;
}

void Camera::shake(float _shakeIntensity) {
    if (!isShaking) {
        shakeIntensity = _shakeIntensity;
        isShaking = true;
        shakeIndex = 0;
    }
}

sf::Vector2f Camera::getOffsetFromStart() const {
    return currentPosition - startPosition;
}

sf::Vector2f Camera::getOffsetFromTarget() const {
    if (auto sharedTarget = targetRef.lock()) {
        return currentPosition - sharedTarget->getPosition();
    }
    return {};
}
