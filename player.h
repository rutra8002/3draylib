#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "Map.h"

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
    bool CheckCollisionWithMap(const Map& map);

    Vector3 position;
    float rotation;
    float verticalRotation;
    float vx;
    float vy;
    float gravity;
    bool isGrounded;
};

#endif