#ifndef MAP_H
#define MAP_H

#include "raylib.h"
#include <vector>

class Map {
public:
    Map();
    void Initialize();
    void Draw();

private:
    std::vector<Vector3> cubePositions;
};

#endif