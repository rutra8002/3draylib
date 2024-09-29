#include "Map.h"

Map::Map() {}

void Map::Initialize() {
    // Add some cubes to the map for reference
    cubePositions.push_back({-5.0f, 0.0f, -5.0f});
    cubePositions.push_back({5.0f, 0.0f, -5.0f});
    cubePositions.push_back({-5.0f, 0.0f, 5.0f});
    cubePositions.push_back({5.0f, 0.0f, 5.0f});
}

void Map::Draw() {
    for (const auto& position : cubePositions) {
        DrawCube(position, 2.0f, 2.0f, 2.0f, BLUE);
        DrawCubeWires(position, 2.0f, 2.0f, 2.0f, DARKBLUE);
    }
}