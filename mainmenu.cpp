#include "MainMenu.h"
#include "raylib.h"

MainMenu::MainMenu(int width, int height) : screenWidth(width), screenHeight(height), startGameSelected(false) {}

void MainMenu::Update() {
    if (IsKeyPressed(KEY_ENTER)) {
        startGameSelected = true;
    }
}

void MainMenu::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("MAIN MENU", screenWidth / 2 - MeasureText("MAIN MENU", 40) / 2, screenHeight / 2 - 50, 40, DARKGRAY);
    DrawText("Press ENTER to Start", screenWidth / 2 - MeasureText("Press ENTER to Start", 20) / 2, screenHeight / 2, 20, DARKGRAY);
    EndDrawing();
}

bool MainMenu::IsStartGameSelected() const {
    return startGameSelected;
}

void MainMenu::CenterCursor() const {
    SetMousePosition(screenWidth / 2, screenHeight / 2);
}