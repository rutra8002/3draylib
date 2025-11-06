#include "camera3D.h"
#include "raymath.h"

Camera3DWrapper::Camera3DWrapper() : camera{}, currentMode(THIRD_PERSON_VIEW), currentCameraPosition{0.0f, 0.0f, 0.0f} {
    camera.target = {0.0f, 0.0f, 0.0f};
    camera.up = {0.0f, 1.0f, 0.0f};
    camera.fovy = 70.0f;
    camera.projection = CAMERA_PERSPECTIVE;
}

void Camera3DWrapper::SetPositionBehindPlayer(Vector3 playerPosition, float playerRotation, float playerVerticalRotation, float deltaTime) {
    Vector3 targetPosition = playerPosition;
    targetPosition.z += 20.0f * cosf(playerRotation * DEG2RAD);
    targetPosition.x += 20.0f * sinf(playerRotation * DEG2RAD);
    targetPosition.y += 10.0f * sinf(playerVerticalRotation * DEG2RAD);

    currentCameraPosition.x = Lerp(currentCameraPosition.x, targetPosition.x, 5.0f * deltaTime);
    currentCameraPosition.y = Lerp(currentCameraPosition.y, targetPosition.y, 5.0f * deltaTime);
    currentCameraPosition.z = Lerp(currentCameraPosition.z, targetPosition.z, 5.0f * deltaTime);

    SetPosition(currentCameraPosition);
}

void Camera3DWrapper::SetFirstPersonView(Vector3 playerPosition, float playerRotation, float playerVerticalRotation, float deltaTime) {
    Vector3 cameraPosition = playerPosition;
    cameraPosition.y += 1.0f;

    Vector3 target = cameraPosition;
    target.x -= sinf(playerRotation * DEG2RAD) * cosf(playerVerticalRotation * DEG2RAD);
    target.y -= sinf(playerVerticalRotation * DEG2RAD);
    target.z -= cosf(playerRotation * DEG2RAD) * cosf(playerVerticalRotation * DEG2RAD);

    SetPosition(cameraPosition);
    SetTarget(target);
}

void Camera3DWrapper::ToggleCameraMode() {
    currentMode = (currentMode == THIRD_PERSON_VIEW) ? FIRST_PERSON_VIEW : THIRD_PERSON_VIEW;
}

ViewMode Camera3DWrapper::GetCurrentMode() const {
    return currentMode;
}

void Camera3DWrapper::SetPosition(Vector3 position) {
    camera.position = position;
}

void Camera3DWrapper::SetTarget(Vector3 target) {
    camera.target = target;
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

Vector3 Camera3DWrapper::GetPosition() const {
    return camera.position;
}

Vector3 Camera3DWrapper::GetTarget() const {
    return camera.target;
}