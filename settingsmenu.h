#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include "button.h"

class SettingsMenu {
public:
    SettingsMenu(int width, int height);
    void Update();
    void Draw();
    bool IsBackSelected() const;
    void ResetBackSelected();

private:
    int screenWidth;
    int screenHeight;
    bool backSelected;
    Button backButton;
};

#endif