#include "game.h"
#include "raylib.h"
#include "GameObject.h"

Game::Game(int width, int height)
    : screenWidth(width), screenHeight(height),
      mainMenu(width, height), settingsMenu(width, height),
      currentState(MAIN_MENU) {
    InitWindow(screenWidth, screenHeight, "hello world");
    InitAudioDevice();
    camera.SetPosition({0.0f, 10.0f, 10.0f});
    camera.SetTarget({0.0f, 0.0f, 0.0f});
    map.Initialize();

    target = LoadRenderTexture(screenWidth, screenHeight);

    lightingShader = LoadShader("shaders/lighting.vs", "shaders/lighting.fs");
    viewPosLoc = GetShaderLocation(lightingShader, "viewPos");
    lightCountLoc = GetShaderLocation(lightingShader, "lightCount");
    for (int i = 0; i < MAX_LIGHTS; i++) {
        char posName[32], colorName[32], intensityName[32];
        sprintf(posName, "lights[%i].position", i);
        sprintf(colorName, "lights[%i].color", i);
        sprintf(intensityName, "lights[%i].intensity", i);
        lightPositionLoc[i] = GetShaderLocation(lightingShader, posName);
        lightColorLoc[i] = GetShaderLocation(lightingShader, colorName);
        lightIntensityLoc[i] = GetShaderLocation(lightingShader, intensityName);
    }
    InitializeLights();

    player.Init();
    gameObjects.push_back(&map);
    gameObjects.push_back(&player);
}

Game::~Game() {
    UnloadShader(lightingShader);
    UnloadRenderTexture(target);
    CloseWindow();
    CloseAudioDevice();
}

void Game::Run() {
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        switch (currentState) {
            case MAIN_MENU:
                mainMenu.Update();
                if (mainMenu.IsStartGameSelected()) {
                    mainMenu.CenterCursor();
                    currentState = IN_GAME;
                }
                if (mainMenu.IsSettingsSelected()) {
                    currentState = SETTINGS_MENU;
                }
                break;
            case SETTINGS_MENU:
                settingsMenu.Update();
                if (settingsMenu.IsBackSelected()) {
                    currentState = MAIN_MENU;
                    settingsMenu.ResetBackSelected();
                    mainMenu.ResetSettingsSelected();
                }
                break;
            case IN_GAME:
                Update(deltaTime);
                break;
        }
        Draw();
    }
    EnableCursor();
    ShowCursor();
}

void Game::Update(float deltaTime) {
    player.Update(deltaTime, map);

    if (settingsMenu.IsFirstPerson()) {
        camera.SetFirstPersonView(player.GetPosition(), player.GetRotation(), player.GetVerticalRotation(), deltaTime);
    } else {
        camera.SetPositionBehindPlayer(player.GetPosition(), player.GetRotation(), player.GetVerticalRotation(), deltaTime);
        camera.SetTargetToPlayer(player.GetPosition());
    }
}

void Game::ApplyLightingUniforms(const Vector3& cameraPos) {
    Vector3 camPos = cameraPos;
    SetShaderValue(lightingShader, viewPosLoc, &camPos, SHADER_UNIFORM_VEC3);
    int lightCount = (int)lights.size();
    SetShaderValue(lightingShader, lightCountLoc, &lightCount, SHADER_UNIFORM_INT);

    for (size_t i = 0; i < lights.size() && i < MAX_LIGHTS; i++) {
        SetShaderValue(lightingShader, lightPositionLoc[i], &lights[i].position, SHADER_UNIFORM_VEC3);
        Vector3 lightColor = {
            (float)lights[i].color.r / 255.0f,
            (float)lights[i].color.g / 255.0f,
            (float)lights[i].color.b / 255.0f
        };
        SetShaderValue(lightingShader, lightColorLoc[i], &lightColor, SHADER_UNIFORM_VEC3);
        SetShaderValue(lightingShader, lightIntensityLoc[i], &lights[i].intensity, SHADER_UNIFORM_FLOAT);
    }
}

void Game::Draw() {
    switch (currentState) {
        case MAIN_MENU:
            mainMenu.Draw();
            break;
        case SETTINGS_MENU:
            settingsMenu.Draw();
            break;
        case IN_GAME:
            BeginTextureMode(target);
            ClearBackground(RAYWHITE);

            camera.BeginMode3D();

            // Lighting shader
            BeginShaderMode(lightingShader);
            ApplyLightingUniforms(camera.GetPosition());
            for (GameObject* obj : gameObjects) {
                obj->Draw();
            }
            EndShaderMode();

#ifdef DEBUG_MODE
            DrawLightRadius();
#endif

            Camera3DWrapper::EndMode3D();

            EndTextureMode();

            BeginDrawing();

            DrawTextureRec(
                target.texture,
                {0, 0, (float)screenWidth, (float)-screenHeight},
                {0, 0},
                WHITE
            );

#ifdef DEBUG_MODE
            map.DrawHitboxes();
#endif

            DrawText("Move the cube with WASD", 10, 30, 20, DARKGRAY);
            DrawFPS(10, 10);


#ifdef DEBUG_MODE
            DrawDebugMenu();
#endif

            EndDrawing();
            break;
    }
}

void Game::AddLight(const Vector3& position, const Color& color, float intensity) {
    lights.push_back({position, color, intensity});
}

void Game::InitializeLights() {
    AddLight({-5.0f, 5.0f, -5.0f}, RED, 4.8f);
    AddLight({5.0f, 5.0f, 5.0f}, GREEN, 4.8f);
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

    float playerspeed = player.GetSpeed();
    DrawText(TextFormat("Speed: %.2f", playerspeed), 10, 230, 20, DARKGRAY);

    DrawText("Game Objects:", 10, 260, 20, RED);

    int startY = 290;
    int lineHeight = 30;
    for (size_t i = 0; i < gameObjects.size(); ++i) {
        const GameObject* obj = gameObjects[i];
        int yPos = startY + static_cast<int>(i) * lineHeight;
        DrawText(TextFormat("%zu: %s", i, obj->GetName().c_str()), 10, yPos, 20, DARKGRAY);
    }
}

void Game::DrawLightRadius() const {
    for (const auto& light : lights) {
        DrawSphere(light.position, light.intensity/4, Fade(light.color, 0.7f));
    }
}
#endif