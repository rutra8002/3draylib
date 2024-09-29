#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

class Player {

public:
    Player();
    void Update(float deltaTime);
    void Draw();
    Vector3 GetPosition() const;
    float GetRotation() const;
    float GetVerticalRotation() const;
    void SetRotation(float rotation);

private:
    void HandleMouseInput();

    Vector3 position;
    float rotation;
    float verticalRotation;
};

#endif