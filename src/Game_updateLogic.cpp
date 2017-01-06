#include "Game.hpp"

extern bool gameHasFocus;

void Game::updateLogic(const sf::Time & elapsedTime) {
    if (!::gameHasFocus) {
        util::sleep(milliseconds(200));
        return;
    }
    // Blurring is graphics intensive, the game caches frames in a RenderTexture
    // when possible
    if (stashed && UI.getState() != ui::Backend::State::statsScreen &&
        UI.getState() != ui::Backend::State::menuScreen) {
        stashed = false;
    }
    if (!stashed || preload) {
        std::lock_guard<std::mutex> overworldLock(overworldMutex);
        if (level != 0) {
            const sf::Vector2f & cameraOffset = camera.getOffsetFromStart();
            bkg.setOffset(cameraOffset.x, cameraOffset.y);
        } else { // TODO: why is this necessary...?
            bkg.setOffset(0, 0);
        }
        tiles.update();
        auto objUpdatePolicy = [&elapsedTime, this](auto & vec) {
            for (auto it = vec.begin(); it != vec.end();) {
                if ((*it)->getKillFlag()) {
                    it = vec.erase(it);
                } else {
                    (*it)->update(elapsedTime, this);
                    ++it;
                }
            }
        };
        detailGroup.apply(objUpdatePolicy);
        helperGroup.apply(objUpdatePolicy);
        std::vector<sf::Vector2f> cameraTargets;
        en.update(this, !UI.isOpen(), elapsedTime, cameraTargets);
        camera.update(elapsedTime, cameraTargets);
        if (player.visible) {
            player.update(this, elapsedTime, sounds);
            const sf::Vector2f playerPos = player.getPosition();
            sf::Listener::setPosition(playerPos.x, playerPos.y, 35.f);
        }
        if (!UI.isOpen()) {
            effectGroup.apply(objUpdatePolicy);
        }
    }
    {
        std::lock_guard<std::mutex> UILock(UIMutex);
        if (player.getState() == Player::State::dead) {
            UI.dispDeathSeq();
            if (UI.isComplete()) {
                UI.reset();
                player.reset();
                // Game::nextLevel() increments level, set to -1 so that it will
                // be zero
                level = -1;
                this->nextLevel();
                uiFrontend.reset();
                static const char playerStartingHealth = 4;
                uiFrontend.updateHealth(playerStartingHealth);
                uiFrontend.updateMaxHealth(playerStartingHealth);
                uiFrontend.setWaypointText(level);
            }
            UI.update(this, elapsedTime);
        } else {
            if (transitionState == TransitionState::None) {
                UI.update(this, elapsedTime);
            }
        }
    }
    updateTransitions(elapsedTime);
}
