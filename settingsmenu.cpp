#include "settingsmenu.h"
#include "raylib.h"

SettingsMenu::SettingsMenu(int width, int height)
    : screenWidth(width), screenHeight(height), backSelected(false), shaderEnabled(true),
      backButton(width / 2 - 100, height / 2 + 60, 200, 50, "Back", 20, DARKGRAY, LIGHTGRAY, GRAY, DARKGRAY),
      shaderToggleButton(width / 2 - 100, height / 2, 200, 50, "Shader: ON", 20, DARKGRAY, LIGHTGRAY, GRAY, DARKGRAY) {}

void SettingsMenu::Update() {
    backButton.Update();
    shaderToggleButton.Update();
    if (backButton.IsClicked()) {
        backSelected = true;
    }
    if (shaderToggleButton.IsClicked()) {
        shaderEnabled = !shaderEnabled;
        shaderToggleButton.SetText(shaderEnabled ? "Shader: ON" : "Shader: OFF");
    }
}

void SettingsMenu::Draw() {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("SETTINGS MENU", screenWidth / 2 - MeasureText("SETTINGS MENU", 40) / 2, screenHeight / 2 - 100, 40, DARKGRAY);
    shaderToggleButton.Draw();
    backButton.Draw();
    EndDrawing();
}

bool SettingsMenu::IsBackSelected() const {
    return backSelected;
}

void SettingsMenu::ResetBackSelected() {
    backSelected = false;
}

bool SettingsMenu::IsShaderEnabled() const {
    return shaderEnabled;
}