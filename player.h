#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "map.h"
#include <vector>

enum CollisionSide {
    NO_COLLISION,
    COLLISION_TOP,
    COLLISION_BOTTOM,
    COLLISION_LEFT,
    COLLISION_RIGHT,
    COLLISION_FRONT,
    COLLISION_BACK
};

class Player {

public:
    Player();
    void Update(float deltaTime, const Map& map);
    void Draw();
    [[nodiscard]] Vector3 GetPosition() const;
    [[nodiscard]] float GetRotation() const;
    [[nodiscard]] float GetVerticalRotation() const;
    void SetRotation(float rotation);
    void SetLightingShader(Shader shader);

private:
    void HandleMouseInput();
    std::vector<CollisionSide> CheckCollisionWithMap(const Map& map);
    void Jump();

    Vector3 position;
    float rotation;
    float verticalRotation;
    float vx;
    float vy;
    float vz;
    float gravity;
    float mass;
    bool isGrounded;
    const float jumpSpeed = 15.0f;
    Shader lightingShader{};
};

#endif