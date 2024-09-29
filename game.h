#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "Camera3D.h"
#include "Map.h"

class Game {
public:
    Game();
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
};

#endif