#ifndef MAP_H
#define MAP_H

#include "raylib.h"
#include <vector>

class Map {
public:
    struct Cube {
        Vector3 position;
        Vector3 dimensions;
    };

    Map();
    void Initialize();
    void Draw();
    void DrawHitboxes() const;
    [[nodiscard]] const std::vector<Map::Cube>& GetCubes() const;

private:
    std::vector<Cube> cubes;
};

#endif