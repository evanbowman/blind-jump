#include "background.hpp"

std::map<int, Layer> & BackgroundController::getBkgLayers() {
    return m_bkgLayers;
}

void BackgroundController::addBkgLayer(const int layerno, Layer && layer) {
    m_bkgLayers[layerno] = std::move(layer);
}

std::map<int, Layer> & BackgroundController::getFgLayers() {
    return m_fgLayers;
}

void BackgroundController::addFgLayer(const int layerno, Layer && layer) {
    m_fgLayers[layerno] = std::move(layer);
}
