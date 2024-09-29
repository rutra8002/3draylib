#include "Camera3D.h"

Camera3DWrapper::Camera3DWrapper() : camera{} {
    camera.position = {0.0f, 10.0f, 10.0f};
    camera.target = {0.0f, 0.0f, 0.0f};
    camera.up = {0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
}

void Camera3DWrapper::SetPosition(Vector3 position) {
    camera.position = position;
}

void Camera3DWrapper::SetTarget(Vector3 target) {
    camera.target = target;
}

void Camera3DWrapper::SetPositionBehindPlayer(Vector3 playerPosition) {
    Vector3 cameraPosition = playerPosition;
    cameraPosition.z += 20.0f;
    cameraPosition.y += 10.0f;
    SetPosition(cameraPosition);
}

void Camera3DWrapper::SetTargetToPlayer(Vector3 playerPosition) {
    SetTarget(playerPosition);
}

void Camera3DWrapper::BeginMode3D() {
    ::BeginMode3D(camera);
}

void Camera3DWrapper::EndMode3D() {
    ::EndMode3D();
}