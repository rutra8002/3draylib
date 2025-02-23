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

    struct Light {
        Vector3 position;
        Color color;
        float intensity;
    };

    Map();
    void AddLight(const Vector3& position, const Color& color, float intensity);
    void InitializeLights();
    void Initialize();
    void Draw(const Vector3& cameraPos);
    void DrawLightRadius() const;
    void DrawHitboxes() const;
    [[nodiscard]] const std::vector<Map::Cube>& GetCubes() const;
    [[nodiscard]] Shader GetLightingShader() const;

private:
    std::vector<Cube> cubes;
    std::vector<Light> lights;
    static const int MAX_LIGHTS = 4;
    Shader lightingShader{};
    int viewPosLoc{};
    int lightCountLoc{};
    int lightPositionLoc[MAX_LIGHTS]{};
    int lightColorLoc[MAX_LIGHTS]{};
    int lightIntensityLoc[MAX_LIGHTS]{};
};

#endif