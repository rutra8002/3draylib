#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "gameobject.h"
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

class Player : public GameObject {

public:
    Player();
    ~Player();
    void Init();
    void Update(float deltaTime) override;
    void UpdateWithMap(float deltaTime, const Map& map);
    void Draw() override;
    void DrawWithShader(Shader shader);
    [[nodiscard]] float GetSpeed() const;
    [[nodiscard]] float GetRotation() const;
    [[nodiscard]] float GetVerticalRotation() const;
    void SetRotation(float rotation);

private:
    void HandleMouseInput();
    std::vector<CollisionSide> CheckCollisionWithMap(const Map& map);
    void Jump();

    float rotation;
    float verticalRotation;
    float vx;
    float vy;
    float vz;
    float gravity;
    float mass;
    bool isGrounded;
    const float jumpSpeed = 15.0f;
    const float acceleration = 300.0f;
    const float friction = 20.0f;
    Model ironManModel{};
    float modelScale{0.1f};
};

#endif