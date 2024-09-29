#include "Player.h"
#include "raymath.h"

Player::Player() : position({0.0f, 0.0f, 0.0f}), rotation(0.0f), verticalRotation(0.0f) {}

void Player::Update(float deltaTime) {
    if (IsKeyDown(KEY_D)) {
        position.x += 10 * deltaTime * cosf(-rotation * DEG2RAD);
        position.z += 10 * deltaTime * sinf(-rotation * DEG2RAD);
    }
    if (IsKeyDown(KEY_A)) {
        position.x -= 10 * deltaTime * cosf(-rotation * DEG2RAD);
        position.z -= 10 * deltaTime * sinf(-rotation * DEG2RAD);
    }
    if (IsKeyDown(KEY_W)) {
        position.x += 10 * deltaTime * sinf(-rotation * DEG2RAD);
        position.z -= 10 * deltaTime * cosf(-rotation * DEG2RAD);
    }
    if (IsKeyDown(KEY_S)) {
        position.x -= 10 * deltaTime * sinf(-rotation * DEG2RAD);
        position.z += 10 * deltaTime * cosf(-rotation * DEG2RAD);
    }

    HandleMouseInput();
}

void Player::HandleMouseInput() {
    rotation -= GetMouseDelta().x * 0.3f;
    verticalRotation += GetMouseDelta().y * 0.3f;
    verticalRotation = Clamp(verticalRotation, -89.0f, 89.0f); // Limit vertical rotation to avoid flipping
}

void Player::Draw() {
    DrawCube(position, 2.0f, 2.0f, 2.0f, RED);
    DrawCubeWires(position, 2.0f, 2.0f, 2.0f, MAROON);
}

Vector3 Player::GetPosition() const {
    return position;
}

float Player::GetRotation() const {
    return rotation;
}

float Player::GetVerticalRotation() const {
    return verticalRotation;
}

void Player::SetRotation(float newRotation) {
    rotation = newRotation;
}