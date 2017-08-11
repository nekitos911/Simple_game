#ifndef LOADING_H
#define LOADING_H

#include "constants.h"

using namespace sf;

class Loading
{
public:
    Loading();
    Loading(int x,int y,const wchar_t *loading_object1,const std::string loading_object2);

    void Draw(RenderWindow &window);
    void GetImage(Image &image,std::string string,bool drawSprite);

private:
    int mapW;
    RectangleShape m_backdrop;
    Font m_font;
    Text m_content[2];
    Text l_content;
    Sprite m_sprite;
    Texture m_texture;
    bool isDrawSprite;
    FloatRect rect;
    int x,y;
};

#endif // LOADING_H
