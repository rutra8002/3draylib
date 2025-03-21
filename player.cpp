#include "player.h"
#include "raymath.h"
#include "rlgl.h"

Player::Player() : position({0.0f, 0.0f, 0.0f}), rotation(0.0f), verticalRotation(0.0f),
                  vx(0.0f), vy(0.0f), vz(0.0f), gravity(-9.8f), mass(3), isGrounded(false) {
    modelScale = 0.03f;
}

void Player::Init() {
    // Load model here, after Raylib is initialized
    ironManModel = LoadModel("IronMan/IronMan.obj");
}
void Player::Update(float deltaTime, const Map& map) {
    std::vector<CollisionSide> collisionSides = CheckCollisionWithMap(map);
    isGrounded = false;

    for (CollisionSide collisionSide : collisionSides) {
        if (collisionSide == COLLISION_TOP) {
            vy = 0;
            isGrounded = true;
        } else if (collisionSide == COLLISION_BOTTOM) {
            vy = -vy;
        } else if (collisionSide == COLLISION_LEFT || collisionSide == COLLISION_RIGHT) {
            vx = 0;
        } else if (collisionSide == COLLISION_FRONT || collisionSide == COLLISION_BACK) {
            vz = 0;
        }
    }

    float currentAcceleration = isGrounded ? acceleration : acceleration * 0.05f;
    Vector3 movement = {0.0f, 0.0f, 0.0f};

    if (IsKeyDown(KEY_D)) {
        movement.x += cosf(-rotation * DEG2RAD);
        movement.z += sinf(-rotation * DEG2RAD);
    }
    if (IsKeyDown(KEY_A)) {
        movement.x -= cosf(-rotation * DEG2RAD);
        movement.z -= sinf(-rotation * DEG2RAD);
    }
    if (IsKeyDown(KEY_W)) {
        movement.x += sinf(-rotation * DEG2RAD);
        movement.z -= cosf(-rotation * DEG2RAD);
    }
    if (IsKeyDown(KEY_S)) {
        movement.x -= sinf(-rotation * DEG2RAD);
        movement.z += cosf(-rotation * DEG2RAD);
    }

    if (Vector3Length(movement) > 0) {
        movement = Vector3Normalize(movement);
    }

    vx += movement.x * currentAcceleration * deltaTime;
    vz += movement.z * currentAcceleration * deltaTime;

    if (isGrounded) {
        vx -= vx * friction * deltaTime;
        vz -= vz * friction * deltaTime;

        if (IsKeyDown(KEY_SPACE)) {
            Jump();
        }
    }

    position.x += vx * deltaTime;
    position.z += vz * deltaTime;
    position.y += vy * deltaTime;

    if (!isGrounded) {
        vy += gravity * mass * deltaTime;
    }

    HandleMouseInput();
}

Player::~Player() {
    UnloadModel(ironManModel);
}

void Player::Jump() {
    vy = jumpSpeed;
    isGrounded = false;
}

std::vector<CollisionSide> Player::CheckCollisionWithMap(const Map& map) {
    std::vector<CollisionSide> collisionSides;
    for (const auto& cube : map.GetCubes()) {
        BoundingBox playerBox = {
            {position.x - 1.0f, position.y - 1.0f, position.z - 1.0f},
            {position.x + 1.0f, position.y + 1.0f, position.z + 1.0f}
        };
        BoundingBox cubeBox = {
            {cube.position.x - cube.dimensions.x / 2, cube.position.y - cube.dimensions.y / 2, cube.position.z - cube.dimensions.z / 2},
            {cube.position.x + cube.dimensions.x / 2, cube.position.y + cube.dimensions.y / 2, cube.position.z + cube.dimensions.z / 2}
        };

        if (CheckCollisionBoxes(playerBox, cubeBox)) {
            float overlapX = std::min(playerBox.max.x - cubeBox.min.x, cubeBox.max.x - playerBox.min.x);
            float overlapY = std::min(playerBox.max.y - cubeBox.min.y, cubeBox.max.y - playerBox.min.y);
            float overlapZ = std::min(playerBox.max.z - cubeBox.min.z, cubeBox.max.z - playerBox.min.z);

            if (overlapX < overlapY && overlapX < overlapZ) {
                if (playerBox.min.x < cubeBox.max.x && playerBox.max.x > cubeBox.max.x) {
                    position.x = cubeBox.max.x + 1.0f;
                    collisionSides.push_back(COLLISION_LEFT);
                }
                if (playerBox.max.x > cubeBox.min.x && playerBox.min.x < cubeBox.min.x) {
                    position.x = cubeBox.min.x - 1.0f;
                    collisionSides.push_back(COLLISION_RIGHT);
                }
            } else if (overlapY < overlapX && overlapY < overlapZ) {
                if (playerBox.min.y < cubeBox.max.y && playerBox.max.y > cubeBox.max.y) {
                    position.y = cubeBox.max.y + 1.0f;
                    collisionSides.push_back(COLLISION_TOP);
                }
                if (playerBox.max.y > cubeBox.min.y && playerBox.min.y < cubeBox.min.y) {
                    position.y = cubeBox.min.y - 1.0f;
                    collisionSides.push_back(COLLISION_BOTTOM);
                }
            } else {
                if (playerBox.min.z < cubeBox.max.z && playerBox.max.z > cubeBox.max.z) {
                    position.z = cubeBox.max.z + 1.0f;
                    collisionSides.push_back(COLLISION_FRONT);
                }
                if (playerBox.max.z > cubeBox.min.z && playerBox.min.z < cubeBox.min.z) {
                    position.z = cubeBox.min.z - 1.0f;
                    collisionSides.push_back(COLLISION_BACK);
                }
            }
        }
    }
    return collisionSides;
}

void Player::HandleMouseInput() {
    rotation -= GetMouseDelta().x * 0.3f;
    verticalRotation += GetMouseDelta().y * 0.3f;
    verticalRotation = Clamp(verticalRotation, -89.0f, 89.0f); // Limit vertical rotation to avoid flipping
}

void Player::Draw() {
    // Add a safety check
    if (ironManModel.meshes == NULL) {
        // Fallback to a simple cube if model isn't loaded
        DrawCube(position, 2.0f, 2.0f, 2.0f, RED);
        return;
    }

    BeginShaderMode(lightingShader);
    rlPushMatrix();
    rlTranslatef(position.x, position.y, position.z);
    rlRotatef(rotation, 0.0f, 1.0f, 0.0f);

    // Draw Iron Man model instead of cube
    DrawModelEx(ironManModel,
                Vector3{0, -1.0f, 0},  // Adjust Y position to align with ground
                Vector3{0, 1, 0},      // Rotation axis
                180.0f,
                Vector3{modelScale, modelScale, modelScale},
                WHITE);

    rlPopMatrix();
    EndShaderMode();

    #ifdef DEBUG_MODE
        BoundingBox playerBox = {
            {position.x - 1.0f, position.y - 1.0f, position.z - 1.0f},
            {position.x + 1.0f, position.y + 1.0f, position.z + 1.0f}
        };
    DrawBoundingBox(playerBox, RED);
    #endif
}

//get speed function
float Player::GetSpeed() const {
    return sqrt(vx * vx + vz * vz);
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

void Player::SetLightingShader(Shader shader) {
    lightingShader = shader;
}