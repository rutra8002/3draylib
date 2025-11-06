#ifndef MAP_H
#define MAP_H

#include "raylib.h"
#include <vector>
#include "GameObject.h"

class Map : public GameObject {
public:
    struct Cube {
        Vector3 position;
        Vector3 dimensions;
    };

    Map();
    void Initialize();
    void Draw() override;
    void DrawHitboxes() const;
    [[nodiscard]] const std::vector<Map::Cube>& GetCubes() const;

    std::string GetName() const override { return "Map"; }

private:
    std::vector<Cube> cubes;
};

#endif