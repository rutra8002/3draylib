#include "mainmenu.h"
#include "raylib.h"

MainMenu::MainMenu(int width, int height)
    : screenWidth(width), screenHeight(height), startGameSelected(false),
      startButton(width / 2 - 100, height / 2, 200, 50, "Start Game", 20, DARKGRAY, LIGHTGRAY, GRAY, DARKGRAY) {}

void MainMenu::Update() {
    startButton.Update();
    if (startButton.IsClicked()) {
        startGameSelected = true;
    }
}

void MainMenu::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("MAIN MENU", screenWidth / 2 - MeasureText("MAIN MENU", 40) / 2, screenHeight / 2 - 100, 40, DARKGRAY);
    startButton.Draw();
    EndDrawing();
}

bool MainMenu::IsStartGameSelected() const {
    return startGameSelected;
}

void MainMenu::CenterCursor() const {
    SetMousePosition(screenWidth / 2, screenHeight / 2);
    HideCursor();
    DisableCursor();
}