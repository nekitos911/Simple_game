#include "menu.h"

Menu::Menu(){}
Menu::Menu(std::string name,int l_stringsNum)
{
    originIsSet = false;
    m_texture.loadFromFile("Media/Images/menu.png");
    m_sprite.setTexture(m_texture);
    m_sprite.setTextureRect(IntRect(0,0,250,470));
    m_sprite.setPosition(0,0);
    m_name = name;
   // gamewindow = new GameWindow(m_window,m_view);
    currentString = 0;
    isExit = isNewGame = isMainMenu = isGameOver = false;
    stringsNum = l_stringsNum;
    m_content.resize(stringsNum);
    m_font.loadFromFile("Media/arial.ttf");
    for(int i = 0;i < stringsNum;i ++) {
        m_content[i].setFont(m_font);
        m_content[i].setCharacterSize(LOADING_CONTENT_SIZE);
        m_content[i].setFillColor(Color::White);
        m_content[i].setPosition(VIEW_WIDTH / 2,VIEW_HEIGHT / 2 + i * 40);
    }

}

void Menu::Update(RenderWindow &l_window) {
    if(!originIsSet)
        for(int i = 0;i < m_content.size();i ++)
            m_content[i].setOrigin(m_content[i].getLocalBounds().width / 2,m_content[i].getCharacterSize() / 2);
    Event event;
    while(l_window.pollEvent(event)) {
        if(event.type == Event::Closed) {
            isExit = true;
            isGameOver = false;
        }
        if(event.type == Event::KeyPressed)
            if(event.key.code == Keyboard::Down) {
                if(currentString != stringsNum - 1)
                    currentString++;
                else currentString = stringsNum - 1;
            }
        else if(event.key.code == Keyboard::Up) {
                if(currentString != 0)
                    currentString--;
                else currentString = 0;
            }
            else if(event.key.code == Keyboard::Return) {
                 if(m_name == "gameOver") {
                    if(currentString == 0)  { isNewGame = true; isMainMenu = false;}
                    else if(currentString == 1) isMainMenu = true;
                    else if(currentString == 2)
                    {isExit = true; isMainMenu = false; }
                    isGameOver = false;
                 }
                 else if (m_name == "mainMenu") {
                    if (currentString == 0) { isMainMenu = false; isNewGame = true;}
                    else if(currentString == 1)  {isControl = true; isMainMenu = false;}
                    else if(currentString == 2) { isExit = true; isMainMenu = false;}
                    isGameOver = false;
                 }
                }

            }

    for(int i = 0;i < stringsNum;i ++) {
        if(i != currentString) m_content[i].setFillColor(Color::White);
        else m_content[i].setFillColor(Color::Blue);
    }
}

void Menu::Draw(RenderWindow &l_window) {
    l_window.clear();
    l_window.draw(m_sprite);
    for(int i = 0;i < m_content.size();i ++)
        l_window.draw(m_content[i]);
    l_window.display();
}

bool Menu::GetExit() { return isExit;}
