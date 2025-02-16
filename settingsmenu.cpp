#include "settingsmenu.h"
#include "raylib.h"

SettingsMenu::SettingsMenu(int width, int height)
    : screenWidth(width), screenHeight(height), backSelected(false),
      backButton(width / 2 - 800, height / 2, 200, 50, "Back", 20, DARKGRAY, LIGHTGRAY, GRAY, DARKGRAY) {}

void SettingsMenu::Update() {
    backButton.Update();
    if (backButton.IsClicked()) {
        backSelected = true;
    }
}

void SettingsMenu::Draw() {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("SETTINGS MENU", screenWidth / 2 - MeasureText("SETTINGS MENU", 40) / 2, screenHeight / 2 - 100, 40, DARKGRAY);
    backButton.Draw();
    EndDrawing();
}

bool SettingsMenu::IsBackSelected() const {
    return backSelected;
}

void SettingsMenu::ResetBackSelected() {
    backSelected = false;
}