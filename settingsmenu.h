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
    bool IsBloomEnabled() const;
    bool IsSkyEnabled() const;
    bool IsFirstPerson() const;

private:
    int screenWidth;
    int screenHeight;
    bool backSelected;
    bool bloomEnabled;
    bool skyEnabled;
    bool firstPerson;
    Button cameraToggleButton;
    Button backButton;
    Button bloomToggleButton;
    Button skyToggleButton;
};

#endif
