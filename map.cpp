#include "map.h"
#include "raylib.h"
#include "raymath.h"
#include <cstdio>

Map::Map() {}

void Map::Initialize() {
    cubes.push_back({{0.0f, -2.0f, 0.0f}, {200.0f, 2.0f, 200.0f}});
    cubes.push_back({{-5.0f, 0.0f, -5.0f}, {2.0f, 3.0f, 2.0f}});
    cubes.push_back({{5.0f, 0.0f, -5.0f}, {2.0f, 2.0f, 4.0f}});
    cubes.push_back({{-5.0f, 0.0f, 5.0f}, {30.0f, 2.0f, 2.0f}});
    cubes.push_back({{5.0f, 0.0f, 5.0f}, {2.0f, 2.0f, 20.0f}});
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

    InitializeLights();

    lightingShader = LoadShader("shaders/lighting.vs", "shaders/lighting.fs");
    // Get shader locations
    viewPosLoc = GetShaderLocation(lightingShader, "viewPos");
    lightCountLoc = GetShaderLocation(lightingShader, "lightCount");

    // Get light uniform locations
    for (int i = 0; i < MAX_LIGHTS; i++) {
        char posName[32], colorName[32], intensityName[32];
        sprintf(posName, "lights[%i].position", i);
        sprintf(colorName, "lights[%i].color", i);
        sprintf(intensityName, "lights[%i].intensity", i);

        lightPositionLoc[i] = GetShaderLocation(lightingShader, posName);
        lightColorLoc[i] = GetShaderLocation(lightingShader, colorName);
        lightIntensityLoc[i] = GetShaderLocation(lightingShader, intensityName);
    }
}

void Map::AddLight(const Vector3& position, const Color& color, float intensity) {
    lights.push_back({position, color, intensity});
}

void Map::InitializeLights() {
    AddLight({0.0f, 10.0f, 0.0f}, WHITE, 1.0f);
    AddLight({5.0f, 5.0f, 5.0f}, RED, 0.8f);
}

void Map::Draw(const Vector3& cameraPos) {
    BeginShaderMode(lightingShader);

    // Update shader uniforms
    Vector3 camPos = cameraPos; // Use a temporary variable
    SetShaderValue(lightingShader, viewPosLoc, &camPos, SHADER_UNIFORM_VEC3);
    int lightCount = lights.size(); // Use a temporary variable
    SetShaderValue(lightingShader, lightCountLoc, &lightCount, SHADER_UNIFORM_INT);

    // Update light uniforms
    for (size_t i = 0; i < lights.size() && i < MAX_LIGHTS; i++) {
        SetShaderValue(lightingShader, lightPositionLoc[i], &lights[i].position, SHADER_UNIFORM_VEC3);
        Vector3 lightColor = {
            (float)lights[i].color.r / 255.0f,
            (float)lights[i].color.g / 255.0f,
            (float)lights[i].color.b / 255.0f
        };
        SetShaderValue(lightingShader, lightColorLoc[i], &lightColor, SHADER_UNIFORM_VEC3);
        SetShaderValue(lightingShader, lightIntensityLoc[i], &lights[i].intensity, SHADER_UNIFORM_FLOAT);
    }

    // Draw cubes
    for (const auto& cube : cubes) {
        DrawCube(cube.position, cube.dimensions.x, cube.dimensions.y, cube.dimensions.z, BLUE);
        DrawCubeWires(cube.position, cube.dimensions.x, cube.dimensions.y, cube.dimensions.z, DARKBLUE);
    }

    EndShaderMode();
}

void Map::DrawHitboxes() const {
#ifdef DEBUG_MODE
    for (const auto& cube : cubes) {
        BoundingBox cubeBox = {
            {cube.position.x - cube.dimensions.x / 2, cube.position.y - cube.dimensions.y / 2, cube.position.z - cube.dimensions.z / 2},
            {cube.position.x + cube.dimensions.x / 2, cube.position.y + cube.dimensions.y / 2, cube.position.z + cube.dimensions.z / 2}
        };
        DrawBoundingBox(cubeBox, GREEN);
    }
#endif
}

const std::vector<Map::Cube>& Map::GetCubes() const {
    return cubes;
}