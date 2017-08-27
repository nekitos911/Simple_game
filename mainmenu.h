#ifndef MAINMENU_H
#define MAINMENU_H

#include "constants.h"
#include "menu.h"

class MainMenu:public Menu
{
public:
    MainMenu();
    MainMenu(std::string name,int stringsNum);

    //void Update();
    bool GetState();
    std::string GetString();
};

#endif // MAINMENU_H
