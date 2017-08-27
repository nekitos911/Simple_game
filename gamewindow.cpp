#include "gamewindow.h"

GameWindow::GameWindow(RenderWindow &l_window,View &view,std::string action)
{
    if(action == "Create window") {
    l_window.create(VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT),"Fang",Style::Fullscreen);
    l_window.setFramerateLimit(60);
    icon.loadFromFile("Media/icon.png");
    l_window.setIcon(32, 32, icon.getPixelsPtr());
    l_window.setMouseCursorVisible(false);
    l_window.setVerticalSyncEnabled(true);
    }
    view.reset(FloatRect(0, 0, VIEW_WIDTH, VIEW_HEIGHT));
    view.setCenter(VIEW_WIDTH / 2 ,VIEW_HEIGHT / 2);
    l_window.setView(view);
}
GameWindow::GameWindow(){}
