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
    struct Cube {
        Vector3 position;
        Vector3 dimensions;
    };
    std::vector<Cube> cubes;
};

#endif