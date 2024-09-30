// player.h
#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "map.h"

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
    Vector3 GetPosition() const;
    float GetRotation() const;
    float GetVerticalRotation() const;
    void SetRotation(float rotation);

private:
    void HandleMouseInput();
    CollisionSide CheckCollisionWithMap(const Map& map);
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
};

#endif