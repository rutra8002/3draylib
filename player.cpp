#include "Player.h"

Player::Player() : position({0.0f, 0.0f, 0.0f}) {}

void Player::Update(float deltaTime) {
    if (IsKeyDown(KEY_D)) position.x += 10 * deltaTime;
    if (IsKeyDown(KEY_A)) position.x -= 10 * deltaTime;
    if (IsKeyDown(KEY_W)) position.z -= 10 * deltaTime;
    if (IsKeyDown(KEY_S)) position.z += 10 * deltaTime;
}

void Player::Draw() {
    DrawCube(position, 2.0f, 2.0f, 2.0f, RED);
    DrawCubeWires(position, 2.0f, 2.0f, 2.0f, MAROON);
}

Vector3 Player::GetPosition() const {
    return position;
}
