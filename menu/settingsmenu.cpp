#include "settingsmenu.h"
#include "raylib.h"

SettingsMenu::SettingsMenu(int width, int height)
    : screenWidth(width), screenHeight(height), backSelected(false), firstPerson(false),
      backButton(width / 2 - 100, height / 2 + 160, 200, 50, "Back", 20, DARKGRAY, LIGHTGRAY, GRAY, DARKGRAY),
      cameraToggleButton(width / 2 - 100, height / 2 + 40, 200, 50, "Camera: Third Person", 20, DARKGRAY, LIGHTGRAY, GRAY, DARKGRAY) {}

void SettingsMenu::Update() {
    backButton.Update();
    cameraToggleButton.Update();

    if (cameraToggleButton.IsClicked()) {
        firstPerson = !firstPerson;
        cameraToggleButton.SetText(firstPerson ? "Camera: First Person" : "Camera: Third Person");
    }

    if (backButton.IsClicked()) {
        backSelected = true;

    }
}


void SettingsMenu::Draw() {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("SETTINGS MENU", screenWidth / 2 - MeasureText("SETTINGS MENU", 40) / 2, screenHeight / 2 - 100, 40, DARKGRAY);
    cameraToggleButton.Draw();
    backButton.Draw();
    EndDrawing();
}


bool SettingsMenu::IsFirstPerson() const {
    return firstPerson;
}

bool SettingsMenu::IsBackSelected() const {
    return backSelected;
}

void SettingsMenu::ResetBackSelected() {
    backSelected = false;
}

