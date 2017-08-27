#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include "constants.h"

class GameWindow
{
public:
    GameWindow();
    GameWindow(RenderWindow &l_window,View &view,std::string action = "NONE");
private:
    Image icon;
};

#endif // GAMEWINDOW_H
