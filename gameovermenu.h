#ifndef GAMEOVERMENU_H
#define GAMEOVERMENU_H

#include "menu.h"

class GameOverMenu:public Menu
{
public:
    GameOverMenu();
    GameOverMenu(std::string name,RenderWindow &l_window,int stringsNum);

    bool GetState();
    std::string GetString();

    //void Update();
};

#endif // GAMEOVERMENU_H
