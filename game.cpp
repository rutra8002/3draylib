#include "Game.h"
#include "raylib.h"

Game::Game() {
    InitWindow(800, 450, "hello world");
    InitAudioDevice();
    camera.SetPosition({0.0f, 10.0f, 10.0f});
    camera.SetTarget({0.0f, 0.0f, 0.0f});
}

Game::~Game() {
    CloseWindow();
    CloseAudioDevice();
}

void Game::Run() {
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        Update(deltaTime);
        Draw();
    }
}

void Game::Update(float deltaTime) {
    player.Update(deltaTime);
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    camera.BeginMode3D();

    player.Draw();

    DrawGrid(10, 1.0f);

    camera.EndMode3D();

    DrawText("Move the cube with arrow keys", 10, 30, 20, DARKGRAY);
    DrawFPS(10, 10);

    EndDrawing();
}