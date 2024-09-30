#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "camera3D.h"
#include "map.h"
#include "mainmenu.h"

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

    Player player;
    Camera3DWrapper camera;
    Map map;
    MainMenu mainMenu;
    int screenWidth;
    int screenHeight;
    bool inGame;
};

#endif