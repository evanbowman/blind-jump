#pragma once

#include "Tile.hpp"

#define MAP_WIDTH 61
#define MAP_HEIGHT 61
#define MAP_MARGIN 16

int generateMap(Tile map[MAP_WIDTH][MAP_HEIGHT]);

inline bool isTileWalkable(Tile t) {
    return t == Tile::Sand ||
        t == Tile::SandAndGrass ||
        t == Tile::Plate ||
        t == Tile::Grass ||
        t == Tile::GrassFlowers;
}