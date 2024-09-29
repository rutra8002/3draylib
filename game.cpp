#include "Game.h"
#include "raylib.h"

Game::Game(int width, int height) : screenWidth(width), screenHeight(height), mainMenu(width, height), inGame(false) {
    InitWindow(screenWidth, screenHeight, "hello world");
    InitAudioDevice();
    camera.SetPosition({0.0f, 10.0f, 10.0f});
    camera.SetTarget({0.0f, 0.0f, 0.0f});
    map.Initialize();
}

Game::~Game() {
    CloseWindow();
    CloseAudioDevice();
}

void Game::Run() {
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        if (!inGame) {
            mainMenu.Update();
            if (mainMenu.IsStartGameSelected()) {
                mainMenu.CenterCursor();
                inGame = true;
            }
        } else {
            Update(deltaTime);
        }
        Draw();
    }
    EnableCursor();
    ShowCursor();
}

void Game::Update(float deltaTime) {
    player.Update(deltaTime);
    camera.SetPositionBehindPlayer(player.GetPosition(), player.GetRotation());
    camera.SetTargetToPlayer(player.GetPosition());
    player.SetRotation(player.GetRotation());
}

void Game::Draw() {
    if (!inGame) {
        mainMenu.Draw();
    } else {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        camera.BeginMode3D();

        player.Draw();
        map.Draw();

        DrawGrid(10, 1.0f);

        camera.EndMode3D();

        DrawText("Move the cube with WASD", 10, 30, 20, DARKGRAY);
        DrawFPS(10, 10);

#ifdef DEBUG_MODE
        DrawDebugMenu();
#endif

        EndDrawing();
    }
}

#ifdef DEBUG_MODE
void Game::DrawDebugMenu() {
    DrawText("DEBUG MENU", 10, 50, 20, RED);
}
#endif