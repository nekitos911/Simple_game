#include "gameovermenu.h"

GameOverMenu::GameOverMenu(std::string name,RenderWindow &l_window,int l_stringsNum):Menu(name,l_stringsNum)
{
    originIsSet = true;
    isGameOver = true;
    isMainMenu = false;
    m_content[0].setString("New Game");
    m_content[1].setString("Main menu");
    m_content[2].setString("Exit");
}

GameOverMenu::GameOverMenu(){}

/*void GameOverMenu::Update() {


}*/

bool GameOverMenu::GetState() { return isGameOver;}
std::string GameOverMenu::GetString() {
    if(isNewGame) return "newGame";
    else if(isMainMenu) return "mainMenu";
    else if(isExit) return "exit";
}
