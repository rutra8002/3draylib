#include "Player.h"
#include "raymath.h"

Player::Player() : position({0.0f, 0.0f, 0.0f}), rotation(0.0f), verticalRotation(0.0f), vx(0.0f), vy(0.0f), gravity(-9.8f), isGrounded(false) {}

void Player::Update(float deltaTime, const Map& map) {
    if (IsKeyDown(KEY_D)) {
        vx = 10 * cosf(-rotation * DEG2RAD);
        position.x += vx * deltaTime;
    }
    if (IsKeyDown(KEY_A)) {
        vx = -10 * cosf(-rotation * DEG2RAD);
        position.x += vx * deltaTime;
    }
    if (IsKeyDown(KEY_W)) {
        vx = 10 * sinf(-rotation * DEG2RAD);
        position.z += vx * deltaTime;
    }
    if (IsKeyDown(KEY_S)) {
        vx = -10 * sinf(-rotation * DEG2RAD);
        position.z += vx * deltaTime;
    }

    if (!isGrounded) {
        vy += gravity * deltaTime;
        position.y += vy * deltaTime;
    }

    if (CheckCollisionWithMap(map)) {
        vy = 0;
        isGrounded = true;
    } else {
        isGrounded = false;
    }

    HandleMouseInput();
}

bool Player::CheckCollisionWithMap(const Map& map) {
    for (const auto& cube : map.GetCubes()) {
        if (CheckCollisionBoxes(
            {position.x - 1.0f, position.y - 1.0f, position.z - 1.0f, position.x + 1.0f, position.y + 1.0f, position.z + 1.0f},
            {cube.position.x - cube.dimensions.x / 2, cube.position.y, cube.position.z - cube.dimensions.z / 2, cube.position.x + cube.dimensions.x / 2, cube.position.y + cube.dimensions.y, cube.position.z + cube.dimensions.z / 2}
        )) {
            position.y = cube.position.y + cube.dimensions.y;
            return true;
        }
    }
    return false;
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