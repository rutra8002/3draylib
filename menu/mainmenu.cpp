#include "mainmenu.h"
#include "raylib.h"

MainMenu::MainMenu(int width, int height)
    : screenWidth(width), screenHeight(height), startGameSelected(false), settingsSelected(false),
      startButton(width / 2 - 100, height / 2, 200, 50, "Start Game", 20, DARKGRAY, LIGHTGRAY, GRAY, DARKGRAY),
      settingsButton(width / 2 - 100, height / 2 + 60, 200, 50, "Settings", 20, DARKGRAY, LIGHTGRAY, GRAY, DARKGRAY) {}

void MainMenu::Update() {
    startButton.Update();
    settingsButton.Update();
    if (startButton.IsClicked()) {
        startGameSelected = true;
    }
    if (settingsButton.IsClicked()) {
        settingsSelected = true;
    }
}

void MainMenu::Draw() {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawText("MAIN MENU", screenWidth / 2 - MeasureText("MAIN MENU", 40) / 2, screenHeight / 2 - 100, 40, DARKGRAY);
    startButton.Draw();
    settingsButton.Draw();
    EndDrawing();
}

void MainMenu::ResetSettingsSelected() {
    settingsSelected = false;
}

bool MainMenu::IsStartGameSelected() const {
    return startGameSelected;
}

bool MainMenu::IsSettingsSelected() const {
    return settingsSelected;
}

void MainMenu::CenterCursor() const {
    SetMousePosition(screenWidth / 2, screenHeight / 2);
    HideCursor();
    DisableCursor();
}