#ifndef CAMERA3D_H
#define CAMERA3D_H

#include "raylib.h"

enum ViewMode {
    THIRD_PERSON_VIEW,
    FIRST_PERSON_VIEW
};

class Camera3DWrapper {
public:
    Camera3DWrapper();
    void SetPosition(Vector3 position);
    void SetTarget(Vector3 target);
    void BeginMode3D();
    static void EndMode3D();
    void SetPositionBehindPlayer(Vector3 playerPosition, float playerRotation, float playerVerticalRotation, float deltaTime);
    void SetFirstPersonView(Vector3 playerPosition, float playerRotation, float playerVerticalRotation, float deltaTime);
    void SetTargetToPlayer(Vector3 playerPosition);
    void ToggleCameraMode();
    [[nodiscard]] Vector3 GetPosition() const;
    [[nodiscard]] Vector3 GetTarget() const;
    [[nodiscard]] ViewMode GetCurrentMode() const;

private:
    Camera camera;
    ViewMode currentMode;
    Vector3 currentCameraPosition;
};

#endif