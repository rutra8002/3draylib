#include "game.h"
#include "raylib.h"

Game::Game(int width, int height)
    : screenWidth(width), screenHeight(height),
      mainMenu(width, height), settingsMenu(width, height),
      inGame(false), inSettings(false), inMainMenu(true),
      bloomEnabled(true), skyEnabled(true), isFirstPerson(false) {
    InitWindow(screenWidth, screenHeight, "hello world");
    InitAudioDevice();
    camera.SetPosition({0.0f, 10.0f, 10.0f});
    camera.SetTarget({0.0f, 0.0f, 0.0f});
    map.Initialize();

    target = LoadRenderTexture(screenWidth, screenHeight);
    bloomShader = LoadShader(0, "shaders/bloom.fs");
    skyShader = LoadShader(0, "shaders/sky.fs");
}

Game::~Game() {
    UnloadShader(bloomShader);
    UnloadShader(skyShader);
    UnloadRenderTexture(target);
    CloseWindow();
    CloseAudioDevice();
}

void Game::Run() {
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        if (inMainMenu) {
            mainMenu.Update();
            if (mainMenu.IsStartGameSelected()) {
                mainMenu.CenterCursor();
                inGame = true;
                inMainMenu = false;
            }
            if (mainMenu.IsSettingsSelected()) {
                inSettings = true;
                inMainMenu = false;
            }
        } else if (inSettings) {
            settingsMenu.Update();
            if (settingsMenu.IsBackSelected()) {
                inSettings = false;
                inMainMenu = true;
                settingsMenu.ResetBackSelected();
                mainMenu.ResetSettingsSelected();
                bloomEnabled = settingsMenu.IsBloomEnabled();
                skyEnabled = settingsMenu.IsSkyEnabled();
                isFirstPerson = settingsMenu.IsFirstPerson();
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
    player.Update(deltaTime, map);

    if (isFirstPerson) {
        camera.SetFirstPersonView(player.GetPosition(), player.GetRotation(), player.GetVerticalRotation());
    } else {
        camera.SetPositionBehindPlayer(player.GetPosition(), player.GetRotation(), player.GetVerticalRotation());
        camera.SetTargetToPlayer(player.GetPosition());
    }
}

void Game::Draw() {
    if (inMainMenu) {
        mainMenu.Draw();
    } else if (inSettings) {
        settingsMenu.Draw();
    } else {
        BeginTextureMode(target);
        ClearBackground(RAYWHITE);

        if (skyEnabled) {
            BeginShaderMode(skyShader);
            DrawTextureRec(target.texture, {0, 0, (float)screenWidth, (float)-screenHeight}, {0, 0}, WHITE);
            EndShaderMode();
        }

        camera.BeginMode3D();

        player.Draw();
        map.Draw();


        camera.EndMode3D();

        EndTextureMode();


        BeginDrawing();

        if (bloomEnabled) {
            BeginShaderMode(bloomShader);
        }
        DrawTextureRec(
            target.texture,
            {0, 0, (float)screenWidth, (float)-screenHeight},
            {0, 0},
            WHITE
        );
        if (bloomEnabled) {
            EndShaderMode();
        }

#ifdef DEBUG_MODE
        map.DrawHitboxes();
#endif

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

    Vector3 playerPos = player.GetPosition();
    DrawText(TextFormat("Player Position: [X: %.2f, Y: %.2f, Z: %.2f]", playerPos.x, playerPos.y, playerPos.z), 10, 80, 20, DARKGRAY);

    float playerRot = player.GetRotation();
    DrawText(TextFormat("Player Rotation: %.2f", playerRot), 10, 110, 20, DARKGRAY);

    Vector3 cameraPos = camera.GetPosition();
    DrawText(TextFormat("Camera Position: [X: %.2f, Y: %.2f, Z: %.2f]", cameraPos.x, cameraPos.y, cameraPos.z), 10, 140, 20, DARKGRAY);

    Vector3 cameraTarget = camera.GetTarget();
    DrawText(TextFormat("Camera Target: [X: %.2f, Y: %.2f, Z: %.2f]", cameraTarget.x, cameraTarget.y, cameraTarget.z), 10, 170, 20, DARKGRAY);

    Vector2 playerRotation = {player.GetRotation(), player.GetVerticalRotation()};
    DrawText(TextFormat("Player Rotation: [X: %.2f, Y: %.2f]", playerRotation.x, playerRotation.y), 10, 200, 20, DARKGRAY);
}
#endif