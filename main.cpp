#include "raylib.h"

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "hello world");
    InitAudioDevice();

    Camera camera = { 0 };
    camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };

    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        // Update
        if (IsKeyDown(KEY_RIGHT)) cubePosition.x += 10 * deltaTime;
        if (IsKeyDown(KEY_LEFT)) cubePosition.x -= 10 * deltaTime;
        if (IsKeyDown(KEY_UP)) cubePosition.z -= 10 * deltaTime;
        if (IsKeyDown(KEY_DOWN)) cubePosition.z += 10 * deltaTime;

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
        DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);

        DrawGrid(10, 1.0f);

        EndMode3D();

        DrawText("Move the cube with arrow keys", 10, 30, 20, DARKGRAY);

        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();
    CloseAudioDevice();

    return 0;
}