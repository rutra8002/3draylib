#include "settingsmenu.h"
#include "raylib.h"

SettingsMenu::SettingsMenu(int width, int height)
    : screenWidth(width), screenHeight(height), backSelected(false),
      bloomEnabled(true), skyEnabled(true), firstPerson(false),
      backButton(width / 2 - 100, height / 2 + 220, 200, 50, "Back", 20, DARKGRAY, LIGHTGRAY, GRAY, DARKGRAY),
      bloomToggleButton(width / 2 - 100, height / 2 - 20, 200, 50, "Bloom: ON", 20, DARKGRAY, LIGHTGRAY, GRAY, DARKGRAY),
      skyToggleButton(width / 2 - 100, height / 2 + 40, 200, 50, "Sky: ON", 20, DARKGRAY, LIGHTGRAY, GRAY, DARKGRAY),
      cameraToggleButton(width / 2 - 100, height / 2 + 100, 200, 50, "Camera: Third Person", 20, DARKGRAY, LIGHTGRAY, GRAY, DARKGRAY) {}

void SettingsMenu::Update() {
    backButton.Update();
    bloomToggleButton.Update();
    skyToggleButton.Update();
    cameraToggleButton.Update();

    if (cameraToggleButton.IsClicked()) {
        firstPerson = !firstPerson;
        cameraToggleButton.SetText(firstPerson ? "Camera: First Person" : "Camera: Third Person");
    }

    if (backButton.IsClicked()) {
        backSelected = true;

    }
    if (bloomToggleButton.IsClicked()) {
        bloomEnabled = !bloomEnabled;
        bloomToggleButton.SetText(bloomEnabled ? "Bloom: ON" : "Bloom: OFF");
    }
    if (skyToggleButton.IsClicked()) {
        skyEnabled = !skyEnabled;
        skyToggleButton.SetText(skyEnabled ? "Sky: ON" : "Sky: OFF");
    }
}


void SettingsMenu::Draw() {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("SETTINGS MENU", screenWidth / 2 - MeasureText("SETTINGS MENU", 40) / 2, screenHeight / 2 - 100, 40, DARKGRAY);
    bloomToggleButton.Draw();
    skyToggleButton.Draw();
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

bool SettingsMenu::IsBloomEnabled() const {
    return bloomEnabled;
}

bool SettingsMenu::IsSkyEnabled() const {
    return skyEnabled;
}