#include "loading.h"

Loading::Loading() {}

Loading::Loading(float X,float Y,const wchar_t *loading_object1,const std::string loading_object2)
{
    x = X;
    y = Y;
    isDrawSprite = false;
    m_font.loadFromFile("Media/arial.ttf");
    for (int i = 0;i < 2; i ++) {
    m_content[i].setFont(m_font);
    m_content[i].setCharacterSize(LOADING_CONTENT_SIZE);
    m_content[i].setFillColor(Color::White);

    m_content[0].setOrigin(wcslen(loading_object1 - 1) / 2,m_content[0].getCharacterSize() / 2);
    m_content[1].setOrigin(loading_object2.size(),m_content[1].getCharacterSize() / 2);
    }
    m_content[0].setString(loading_object1);
    m_content[0].setPosition(x,y / 2) ;
    m_content[1].setString(loading_object2);
    m_content[1].setPosition(x,y / 2 + 50) ;
}

void Loading::GetImage(Image &image,std::string string,bool drawSprite) {
    l_content.setFont(m_font);
    l_content.setCharacterSize(LOADING_CONTENT_SIZE);
    l_content.setFillColor(Color::White);
    l_content.setOrigin(string.size() / 2,l_content.getCharacterSize() / 2);
    l_content.setString(string);

    m_texture.loadFromImage(image);
    m_sprite.setTexture(m_texture);
    m_sprite.setOrigin(image.getSize().x / 2,image.getSize().y / 2);
    m_sprite.setPosition(x + image.getSize().x / 2,y / 2 + LOADING_CONTENT_SIZE * 2 );
    l_content.setPosition(x + 3 * image.getSize().x / 2,
                         y / 2 + LOADING_CONTENT_SIZE * 2);
    isDrawSprite = drawSprite;
}

void Loading::Draw(RenderWindow &window) {
    window.clear();
    for (int i = 0;i < 2;i ++)
    window.draw(m_content[i]);
    if (isDrawSprite) {
        window.draw(m_sprite);
        window.draw(l_content);
    }
    window.display();
}
