#ifndef MAINMENU_H
#define MAINMENU_H
#include "button.h"

class MainMenu {
public:
    MainMenu(int width, int height);
    void Update();
    void Draw();
    bool IsStartGameSelected() const;
    bool IsSettingsSelected() const;
    void CenterCursor() const;
    void ResetSettingsSelected();

private:
    int screenWidth;
    int screenHeight;
    bool startGameSelected;
    bool settingsSelected;
    Button startButton;
    Button settingsButton;
};

#endif