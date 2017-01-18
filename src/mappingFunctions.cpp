#include "mappingFunctions.hpp"
#include "tileController.hpp"
#include <cstring>

static void floodFill(Tile map[MAP_WIDTH][MAP_HEIGHT], size_t x, size_t y, Tile sub) {
    using Coord = std::pair<size_t, size_t>;
    std::stack<Coord> stack;
    stack.push({x, y});
    Tile target = map[x][y];
    const auto action = [map, target, sub, &stack](Coord & c, int xOff,
                                                   int yOff) {
        const int i = c.first + xOff;
        const int j = c.second + yOff;
        if (i > 0 && i < MAP_WIDTH - 1 && j > 0 && j < MAP_HEIGHT - 1) {
            if (map[i][j] == target) {
                map[i][j] = sub;
                stack.push({i, j});
            }
        }
    };
    while (!stack.empty()) {
        Coord coord = stack.top();
        stack.pop();
        action(coord, -1, 0);
        action(coord, 0, 1);
        action(coord, 0, -1);
        action(coord, 1, 0);
    }
}

inline void renumber(Tile map[MAP_WIDTH][MAP_HEIGHT]) {
    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            if (map[i][j] == Tile::Wall) {
                map[i][j] = Tile::_UNUSED1_;
            } else if (map[i][j] == Tile::Empty) {
                map[i][j] = Tile::Wall;
            }
        }
    }
}

inline void addEdges(Tile map[MAP_WIDTH][MAP_HEIGHT]) {
    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            if (map[i][j] == Tile::Wall) {
                if (map[i][j - 1] == Tile::Plate) {
                    if (map[i][j + 1] != Tile::Plate) {
                        map[i][j] = Tile::PlateLowerEdge;
                    } else {
                        map[i][j] = Tile::Plate;
                    }
                } else if (map[i][j + 1] == Tile::Plate) {
                    map[i][j] = Tile::PlateUpperEdge;
                }
            }
        }
    }
}

inline void addCenterTiles(Tile map[MAP_WIDTH][MAP_HEIGHT]) {
    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            if ((map[i - 1][j] == Tile::Plate || map[i - 1][j] == Tile::Sand ||
                 map[i - 1][j] == Tile::SandAndGrass) &&
                (map[i + 1][j] == Tile::Plate || map[i + 1][j] == Tile::Sand ||
                 map[i + 1][j] == Tile::SandAndGrass) &&
                (map[i][j - 1] == Tile::Plate || map[i][j - 1] == Tile::Sand ||
                 map[i][j - 1] == Tile::SandAndGrass) &&
                (map[i][j + 1] == Tile::Plate || map[i][j + 1] == Tile::Sand ||
                 map[i][j + 1] == Tile::SandAndGrass)) {
                if (rng::random<12>() > 2) {
                    map[i][j] = Tile::Sand;
                } else {
                    map[i][j] = Tile::SandAndGrass;
                }
            }
        }
    }
}

void condense(Tile map[MAP_WIDTH][MAP_HEIGHT], Tile maptemp[MAP_WIDTH][MAP_HEIGHT], int rep) {
    for (int i = 2; i < MAP_WIDTH - 2; i++) {
        for (int j = 2; j < MAP_HEIGHT - 2; j++) {
            uint8_t count = 0;
            if (map[i - 1][j - 1] == Tile::Wall) {
                count += 1;
            }
            if (map[i + 1][j - 1] == Tile::Wall) {
                count += 1;
            }
            if (map[i - 1][j + 1] == Tile::Wall) {
                count += 1;
            }
            if (map[i + 1][j + 1] == Tile::Wall) {
                count += 1;
            }
            if (map[i - 1][j] == Tile::Wall) {
                count += 1;
            }
            if (map[i + 1][j] == Tile::Wall) {
                count += 1;
            }
            if (map[i][j - 1] == Tile::Wall) {
                count += 1;
            }
            if (map[i][j + 1] == Tile::Wall) {
                count += 1;
            }
            if (map[i][j] == Tile::Wall) {
                if (count < 2) {
                    maptemp[i][j] = Tile::Empty;
                } else {
                    maptemp[i][j] = Tile::Wall;
                }
            } else {
                if (count > 5) {
                    maptemp[i][j] = Tile::Wall;
                } else {
                    maptemp[i][j] = Tile::Empty;
                }
            }
        }
    }
    for (int i = 2; i < MAP_WIDTH - 2; i++) {
        for (int j = 2; j < MAP_HEIGHT - 2; j++) {
            map[i][j] = maptemp[i][j];
        }
    }
    if (rep > 0) {
        condense(map, maptemp, rep - 1);
    }
}

int initMapOverlay(Tile map[MAP_WIDTH][MAP_HEIGHT]) {
    Tile maptemp[61][61];
    std::memset(map, 0, sizeof(map[0][0]) * std::pow(61, 2));
    std::memset(maptemp, 0, sizeof(map[0][0]) * std::pow(61, 2));
    for (int i = MAP_MARGIN; i < MAP_WIDTH - MAP_MARGIN; i++) {
        for (int j = MAP_MARGIN; j < MAP_WIDTH - MAP_MARGIN; j++) {
            map[i][j] = static_cast<Tile>(rng::random<2>());
        }
    }
    condense(map, maptemp, 3);
    uint8_t xindex;
    uint8_t yindex;
    do {
        xindex = rng::random<MAP_WIDTH>();
        yindex = rng::random<MAP_HEIGHT>();
    } while (map[xindex][yindex] != Tile::Wall);
    floodFill(map, xindex, yindex, Tile::Plate);
    int count = 0;
    for (int i = 0; i < MAP_WIDTH - 2; i++) {
        for (int j = 0; j < MAP_HEIGHT - 2; j++) {
            if (map[i][j] == Tile::Plate) {
                count += 1;
            }
        }
    }
    return count;
}

void combine(Tile map[MAP_WIDTH][MAP_HEIGHT], Tile overlay[MAP_WIDTH][MAP_HEIGHT]) {
    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            if ((overlay[i][j] == Tile::Plate && map[i][j] != Tile::Empty) &&
                (overlay[i][j] == Tile::Plate && map[i][j] != Tile::Wall)) {
                if (map[i][j] == Tile::PlateLowerEdge) {
                    map[i][j] = Tile::GrassLowerEdge;
                } else if (map[i][j] == Tile::PlateUpperEdge) {
                    map[i][j] = Tile::GrassUpperEdge;
                } else if (map[i][j] == Tile::Plate) {
                    map[i][j] = Tile::Grass;
                } else {
                    map[i][j] = Tile::GrassFlowers;
                }
            }
        }
    }
}

void cleanEdgesPostCombine(Tile map[61][61]) {
    for (int i = 1; i < MAP_WIDTH - 1; i++) {
        for (int j = 1; j < MAP_HEIGHT - 1; j++) {
            if (map[i][j] == Tile::GrassLowerEdge && map[i][j - 1] != Tile::Grass) {
                map[i][j] = Tile::PlateLowerEdge;
            } else if (map[i][j] == Tile::GrassUpperEdge && map[i][j + 1] != Tile::Grass) {
                map[i][j] = Tile::PlateUpperEdge;
            }
        }
    }
}

int generateMap(Tile map[MAP_WIDTH][MAP_HEIGHT]) {
    Tile maptemp[MAP_WIDTH][MAP_HEIGHT];
    std::memset(map, 0, sizeof(map[0][0]) * std::pow(61, 2));
    std::memset(maptemp, 0, sizeof(maptemp[0][0]) * std::pow(61, 2));
    for (int i = MAP_MARGIN; i < MAP_WIDTH - MAP_MARGIN; i++) {
        for (int j = MAP_MARGIN; j < MAP_HEIGHT - MAP_MARGIN; j++) {
            map[i][j] = static_cast<Tile>(rng::random<2>());
        }
    }
    condense(map, maptemp, 1);
    renumber(map);
    uint8_t xindex;
    uint8_t yindex;
    do {
        xindex = rng::random<MAP_WIDTH>();
        yindex = rng::random<MAP_HEIGHT>();
    } while (map[xindex][yindex] != Tile::_UNUSED1_);
    floodFill(map, xindex, yindex, Tile::Plate);
    for (int i = 2; i < MAP_WIDTH - 2; i++) {
        for (int j = 2; j < MAP_HEIGHT - 2; j++) {
            if (map[i][j] == Tile::_UNUSED1_) {
                map[i][j] = Tile::Wall;
            }
        }
    }
    addEdges(map); // Adds the top and bottom edges for the platforms
    addCenterTiles(map);
    int count = 0;
    for (int i = 0; i < MAP_WIDTH - 2; i++) {
        for (int j = 0; j < MAP_HEIGHT - 2; j++) {
            if (map[i][j] == Tile::Sand || map[i][j] == Tile::SandAndGrass) {
                count += 1;
            }
            if (map[i + 1][j] == Tile::Plate && map[i - 1][j] == Tile::Plate &&
                map[i][j + 1] == Tile::Plate && map[i][j - 1] == Tile::Plate) {
                map[i][j] = Tile::Plate;
            }
        }
    }
    Tile mapOverlay[MAP_WIDTH][MAP_HEIGHT];
    int count2;
    do {
        count2 = initMapOverlay(mapOverlay);
    } while (count2 < 300);
    combine(map, mapOverlay);
    cleanEdgesPostCombine(map);
    return count;
}
