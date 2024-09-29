#include "raylib.h"

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Hello World");

    const char* text = "Hello World";
    int fontSize = 20;
    int textWidth = MeasureText(text, fontSize);
    int textHeight = fontSize;

    int posX = (screenWidth - textWidth) / 2;
    int posY = (screenHeight - textHeight) / 2;

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText(text, posX, posY, fontSize, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}