#include "mainmenu.h"

MainMenu::MainMenu(){}
MainMenu::MainMenu(std::string name,int stringsNum):Menu(name,stringsNum)
{
    originIsSet = true;
    isMainMenu = true;
    m_content[0].setString("New Game");
    m_content[1].setString("Option");
    m_content[2].setString("Exit");
}

/*void MainMenu::Update() {
    Event event;
    while(m_window.pollEvent(event)) {
        if(event.type == Event::Closed) {
            isExit = true;
        }
}*/
bool MainMenu::GetState() { return isMainMenu; }
std::string MainMenu::GetString() {
    if(isNewGame) return "newGame";
    //else if(isMainMenu) return "mainMenu";
    else if(isExit) return "exit";
}
