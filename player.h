#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"

class Player {

public:
    Player();
    void Update(float deltaTime);
    void Draw();
    Vector3 GetPosition() const;

private:
    Vector3 position;
};

#endif