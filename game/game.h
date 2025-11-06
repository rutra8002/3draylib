#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "player.h"
#include "camera3D.h"
#include "map.h"
#include "mainmenu.h"
#include "settingsmenu.h"
#include <vector>

enum GameState {
    MAIN_MENU,
    SETTINGS_MENU,
    IN_GAME
};

struct Light {
    Vector3 position;
    Color color;
    float intensity;
};

class Game {
public:
    Game(int width, int height);
    ~Game();
    void Run();


private:
    void Update(float deltaTime);
    void Draw();
    void InitializeLighting();
    void AddLight(const Vector3& position, const Color& color, float intensity);
    void UpdateLightingUniforms(const Vector3& cameraPos);

#ifdef DEBUG_MODE
    void DrawDebugMenu();
    void DrawLightRadius() const;
#endif

    Shader bloomShader{};
    Shader skyShader{};
    Shader lightingShader{};
    RenderTexture2D target{};
    Player player;
    Camera3DWrapper camera;
    Map map;
    MainMenu mainMenu;
    SettingsMenu settingsMenu;
    std::vector<Light> lights;
    static const int MAX_LIGHTS = 4;
    int viewPosLoc{};
    int lightCountLoc{};
    int lightPositionLoc[MAX_LIGHTS]{};
    int lightColorLoc[MAX_LIGHTS]{};
    int lightIntensityLoc[MAX_LIGHTS]{};
    int screenWidth;
    int screenHeight;
    GameState currentState;
    bool bloomEnabled;
    bool skyEnabled;
};

#endif