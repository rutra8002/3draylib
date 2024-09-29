#include "Player.h"

Player::Player() : position({0.0f, 0.0f, 0.0f}) {}

void Player::Update(float deltaTime) {
    if (IsKeyDown(KEY_RIGHT)) position.x += 10 * deltaTime;
    if (IsKeyDown(KEY_LEFT)) position.x -= 10 * deltaTime;
    if (IsKeyDown(KEY_UP)) position.z -= 10 * deltaTime;
    if (IsKeyDown(KEY_DOWN)) position.z += 10 * deltaTime;
}

void Player::Draw() {
    DrawCube(position, 2.0f, 2.0f, 2.0f, RED);
    DrawCubeWires(position, 2.0f, 2.0f, 2.0f, MAROON);
}