#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "player.h"
#include "camera3D.h"
#include "map.h"
#include "mainmenu.h"
#include "settingsmenu.h"
#include <vector>
#include "GameObject.h"

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
    void DrawLightRadius() const;
#endif

    Shader bloomShader{};
    Shader skyShader{};
    RenderTexture2D target{};

    struct Light {
        Vector3 position;
        Color color;
        float intensity;
    };
    static const int MAX_LIGHTS = 4;
    Shader lightingShader{};
    int viewPosLoc{};
    int lightCountLoc{};
    int lightPositionLoc[MAX_LIGHTS]{};
    int lightColorLoc[MAX_LIGHTS]{};
    int lightIntensityLoc[MAX_LIGHTS]{};
    std::vector<Light> lights;
    void InitializeLights();
    void AddLight(const Vector3& position, const Color& color, float intensity);
    void ApplyLightingUniforms(const Vector3& cameraPos);

    Player player;
    Camera3DWrapper camera;
    Map map;
    std::vector<GameObject*> gameObjects;

    MainMenu mainMenu;
    SettingsMenu settingsMenu;

    int screenWidth;
    int screenHeight;
    GameState currentState;
    bool bloomEnabled;
    bool skyEnabled;
};

#endif