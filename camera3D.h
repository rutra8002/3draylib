#ifndef CAMERA3D_H
#define CAMERA3D_H

#include "raylib.h"

class Camera3DWrapper {
public:
    Camera3DWrapper();
    void SetPosition(Vector3 position);
    void SetTarget(Vector3 target);
    void BeginMode3D();
    void EndMode3D();

private:
    Camera camera;
};

#endif