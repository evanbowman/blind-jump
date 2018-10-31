#include "aStar.hpp"
#include "mappingFunctions.hpp"
#include <algorithm>
#include <cmath>
#include <queue>
#include <unordered_map>
#include <unordered_set>

// Calculates a heuristic based on the distance between two nodes
inline float heuristic(int x1, int x2, int y1, int y2) {
    return (sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
}

namespace std {
template <> struct hash<aStrCoordinate> {
    inline size_t operator()(const aStrCoordinate & n) const {
        return n.x * 1812433253 + n.y;
    }
};
} // namespace std

// Overloaded operator for comparing two nodes
bool operator!=(const aStrCoordinate & a, const aStrCoordinate & b) {
    return (a.x != b.x) || (a.y != b.y);
}

// Overloaded operator for comparing two nodes
bool operator==(const aStrCoordinate & a, const aStrCoordinate & b) {
    return (a.x == b.x) && (a.y == b.y);
}

struct compare {
    bool operator()(const aStrCoordinate & a, const aStrCoordinate & b) const {
        return a.f < b.f;
    }
};

// A function to return a list of adjacent empty squares
std::vector<aStrCoordinate> getAdjacent(aStrCoordinate & coord,
                                        aStrCoordinate & target,
                                        Tile map[MAP_WIDTH][MAP_HEIGHT]) {
    // Declare a vector of adjacent coordinates to return
    std::vector<aStrCoordinate> adjacentTiles;
    bool diagonalMove = true;
    if (isTileWalkable(map[coord.x - 1][coord.y])) {
        aStrCoordinate newCoord;
        newCoord.g = coord.g + 1;
        newCoord.x = coord.x - 1;
        newCoord.y = coord.y;
        newCoord.f =
            newCoord.g + heuristic(newCoord.x, target.x, newCoord.y, target.y);
        adjacentTiles.push_back(newCoord);
    } else {
        diagonalMove = false;
    }
    if (isTileWalkable(map[coord.x + 1][coord.y])) {
        aStrCoordinate newCoord;
        newCoord.g = coord.g + 1;
        newCoord.x = coord.x + 1;
        newCoord.y = coord.y;
        newCoord.f =
            newCoord.g + heuristic(newCoord.x, target.x, newCoord.y, target.y);
        adjacentTiles.push_back(newCoord);
    } else {
        diagonalMove = false;
    }
    if (isTileWalkable(map[coord.x][coord.y - 1])) {
        aStrCoordinate newCoord;
        newCoord.g = coord.g + 1;
        newCoord.x = coord.x;
        newCoord.y = coord.y - 1;
        newCoord.f =
            newCoord.g + heuristic(newCoord.x, target.x, newCoord.y, target.y);
        adjacentTiles.push_back(newCoord);
    } else {
        diagonalMove = false;
    }
    if (isTileWalkable(map[coord.x][coord.y + 1])) {
        aStrCoordinate newCoord;
        newCoord.g = coord.g + 1;
        newCoord.x = coord.x;
        newCoord.y = coord.y + 1;
        newCoord.f =
            newCoord.g + heuristic(newCoord.x, target.x, newCoord.y, target.y);
        adjacentTiles.push_back(newCoord);
    } else {
        diagonalMove = false;
    }
    if (diagonalMove) {
        if (isTileWalkable(map[coord.x + 1][coord.y + 1])) {
            aStrCoordinate newCoord;
            newCoord.g = coord.g + 0.75;
            newCoord.x = coord.x + 1;
            newCoord.y = coord.y + 1;
            newCoord.f = newCoord.g +
                         heuristic(newCoord.x, target.x, newCoord.y, target.y);
            adjacentTiles.push_back(newCoord);
        }
        if (isTileWalkable(map[coord.x - 1][coord.y + 1])) {
            aStrCoordinate newCoord;
            newCoord.g = coord.g + 0.75;
            newCoord.x = coord.x - 1;
            newCoord.y = coord.y + 1;
            newCoord.f = newCoord.g +
                         heuristic(newCoord.x, target.x, newCoord.y, target.y);
            adjacentTiles.push_back(newCoord);
        }
        if (isTileWalkable(map[coord.x - 1][coord.y - 1])) {
            aStrCoordinate newCoord;
            newCoord.g = coord.g + 0.75;
            newCoord.x = coord.x - 1;
            newCoord.y = coord.y - 1;
            newCoord.f = newCoord.g +
                         heuristic(newCoord.x, target.x, newCoord.y, target.y);
            adjacentTiles.push_back(newCoord);
        }
        if (isTileWalkable(map[coord.x + 1][coord.y + 1])) {
            aStrCoordinate newCoord;
            newCoord.g = coord.g + 0.75;
            newCoord.x = coord.x + 1;
            newCoord.y = coord.y + 1;
            newCoord.f = newCoord.g +
                         heuristic(newCoord.x, target.x, newCoord.y, target.y);
        }
    }
    return adjacentTiles;
}

bool contains(std::vector<aStrCoordinate> & closed, aStrCoordinate & node) {
    for (auto element : closed) {
        if (element.x == node.x && element.y == node.y) {
            return true;
        }
    }

    return false;
}

std::vector<aStrCoordinate> reconstruct_path(
    aStrCoordinate start, aStrCoordinate goal,
    std::unordered_map<aStrCoordinate, aStrCoordinate> & came_from) {
    std::vector<aStrCoordinate> path;
    aStrCoordinate current = goal;
    path.push_back(current);
    while (current != start) {
        current = came_from[current];
        path.push_back(current);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<aStrCoordinate> astar_path(aStrCoordinate & origin,
                                       aStrCoordinate & target,
                                       Tile map[MAP_WIDTH][MAP_HEIGHT]) {
    std::vector<aStrCoordinate> closed;
    std::vector<aStrCoordinate> open = {origin};
    origin.g = 0;
    origin.f = heuristic(origin.x, target.x, origin.y, target.y);
    std::make_heap(open.begin(), open.end(), compare());
    std::unordered_map<aStrCoordinate, aStrCoordinate> cameFrom;
    cameFrom[origin] = origin;
    do {
        aStrCoordinate currentNode = open.back();
        closed.push_back(currentNode);
        open.pop_back();
        for (auto element : closed) {
            if (element.x == target.x && element.y == target.y) {
                return reconstruct_path(origin, target, cameFrom);
            }
        }
        std::vector<aStrCoordinate> adjacentTiles =
            getAdjacent(currentNode, target, map);
        for (auto & element : adjacentTiles) {
            if (contains(closed, element)) {
                continue;
            }
            if (!contains(open, element)) {
                open.push_back(element);
                cameFrom[element] = closed.back();
                std::push_heap(open.begin(), open.end(), compare());
            }
        }

    } while (!open.empty());
    return closed;
}
