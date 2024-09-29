#include "Camera3D.h"

Camera3DWrapper::Camera3DWrapper() {
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

void Camera3DWrapper::BeginMode3D() {
    ::BeginMode3D(camera);
}

void Camera3DWrapper::EndMode3D() {
    ::EndMode3D();
}