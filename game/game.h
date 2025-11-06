#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "player.h"
#include "camera3D.h"
#include "map.h"
#include "mainmenu.h"
#include "settingsmenu.h"

enum GameState {
    MAIN_MENU,
    SETTINGS_MENU,
    IN_GAME
};

class Game {
public:
    Game(int width, int height);
    ~Game();
    void Run();


private:
    void Update(float deltaTime);
    void Draw();

#ifdef DEBUG_MODE
    void DrawDebugMenu();
#endif

    Shader bloomShader{};
    Shader skyShader{};
    RenderTexture2D target{};
    Player player;
    Camera3DWrapper camera;
    Map map;
    MainMenu mainMenu;
    SettingsMenu settingsMenu;
    int screenWidth;
    int screenHeight;
    GameState currentState;
    bool bloomEnabled;
    bool skyEnabled;
};

#endif