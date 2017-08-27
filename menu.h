#ifndef MENU_H
#define MENU_H

#include "constants.h"
#include "gamewindow.h"

class Menu
{
public:
    Menu();
    Menu(std::string name,int l_stringsNum);
    void Draw(RenderWindow &l_window);
    void Update(RenderWindow &l_window);
    virtual bool GetState() = 0;
    bool GetExit();
protected:
    int currentString;
    bool isExit,isNewGame,isMainMenu,isGameOver,isControl;
    bool originIsSet;
    Sprite m_sprite;
    Texture m_texture;
    Font m_font;
    std::vector<Text> m_content;
    RenderWindow m_window;
    int stringsNum;
    GameWindow *gamewindow;
    View m_view;
    std::string m_name;

};

#endif // MENU_H
