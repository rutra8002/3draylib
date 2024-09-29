#include "Map.h"

Map::Map() {}

void Map::Initialize() {
    cubes.push_back({{0.0f, -2.0f, 0.0f}, {20.0f, 2.0f, 20.0f}});
    cubes.push_back({{-5.0f, 0.0f, -5.0f}, {2.0f, 3.0f, 2.0f}});
    cubes.push_back({{5.0f, 0.0f, -5.0f}, {2.0f, 2.0f, 4.0f}});
    cubes.push_back({{-5.0f, 0.0f, 5.0f}, {3.0f, 2.0f, 2.0f}});
    cubes.push_back({{5.0f, 0.0f, 5.0f}, {2.0f, 2.0f, 2.0f}});
}

void Map::Draw() {
    for (const auto& cube : cubes) {
        DrawCube(cube.position, cube.dimensions.x, cube.dimensions.y, cube.dimensions.z, BLUE);
        DrawCubeWires(cube.position, cube.dimensions.x, cube.dimensions.y, cube.dimensions.z, DARKBLUE);
    }
}