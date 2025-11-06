#ifndef MAP_H
#define MAP_H

#include "raylib.h"
#include "gameobject.h"
#include <vector>

class Map : public GameObject {
public:
    struct Cube {
        Vector3 position;
        Vector3 dimensions;
    };

    Map();
    void Initialize();
    void Update(float deltaTime) override;
    void Draw() override;
    void DrawWithShader(Shader shader, const Vector3& cameraPos);
    void DrawHitboxes() const;
    [[nodiscard]] const std::vector<Map::Cube>& GetCubes() const;

private:
    std::vector<Cube> cubes;
};

#endif