#include "map.h"

Map::Map() {}

void Map::Initialize() {
    cubes.push_back({{0.0f, -2.0f, 0.0f}, {20.0f, 2.0f, 20.0f}});
    cubes.push_back({{-5.0f, 0.0f, -5.0f}, {2.0f, 3.0f, 2.0f}});
    cubes.push_back({{5.0f, 0.0f, -5.0f}, {2.0f, 2.0f, 4.0f}});
    cubes.push_back({{-5.0f, 0.0f, 5.0f}, {3.0f, 2.0f, 2.0f}});
    cubes.push_back({{5.0f, 0.0f, 5.0f}, {2.0f, 2.0f, 2.0f}});
    //stairs
    cubes.push_back({{0.0f, 0.0f, 0.0f}, {2.0f, 1.0f, 1.0f}});
    cubes.push_back({{0.0f, 1.0f, 1.0f}, {2.0f, 1.0f, 1.0f}});
    cubes.push_back({{0.0f, 2.0f, 2.0f}, {2.0f, 1.0f, 1.0f}});
    cubes.push_back({{0.0f, 3.0f, 3.0f}, {2.0f, 1.0f, 1.0f}});
    cubes.push_back({{0.0f, 4.0f, 4.0f}, {2.0f, 1.0f, 1.0f}});
    cubes.push_back({{0.0f, 5.0f, 5.0f}, {2.0f, 1.0f, 1.0f}});
    cubes.push_back({{0.0f, 6.0f, 6.0f}, {2.0f, 1.0f, 1.0f}});
    cubes.push_back({{0.0f, 7.0f, 7.0f}, {2.0f, 1.0f, 1.0f}});
    cubes.push_back({{0.0f, 8.0f, 8.0f}, {2.0f, 1.0f, 1.0f}});
    cubes.push_back({{0.0f, 9.0f, 9.0f}, {2.0f, 1.0f, 1.0f}});
    cubes.push_back({{0.0f, 10.0f, 10.0f}, {2.0f, 1.0f, 1.0f}});

}

void Map::Draw() {
    for (const auto& cube : cubes) {
        DrawCube(cube.position, cube.dimensions.x, cube.dimensions.y, cube.dimensions.z, BLUE);
        DrawCubeWires(cube.position, cube.dimensions.x, cube.dimensions.y, cube.dimensions.z, DARKBLUE);
    }
}

const std::vector<Map::Cube>& Map::GetCubes() const {
    return cubes;
}