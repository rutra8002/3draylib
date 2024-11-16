#ifndef MAINMENU_H
#define MAINMENU_H
#include "button.h"

class MainMenu {
public:
    MainMenu(int width, int height);
    void Update();
    void Draw();
    bool IsStartGameSelected() const;
    void CenterCursor() const;

private:
    int screenWidth;
    int screenHeight;
    bool startGameSelected;
    Button startButton;
};

#endif