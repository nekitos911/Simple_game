#ifndef STATUSBAR_H
#define STATUSBAR_H

#include "player.h"
#include "constants.h"

class StatusBar
{
public:
    StatusBar(Image &image,float l_mapW,float l_mapH);

    void Add(std::string life);
    void Draw(RenderWindow &window,float x,float y);
    void Update(std::string life,std::string score);
    void Clear();
private:
    std::string m_life;
    float mapW,mapH;
    std::string m_score;
    int m_numVisible;
    RectangleShape m_backdrop;
    Font m_font;
    Text m_content[2];
    Sprite m_sprite;
    Texture m_texture;
};

#endif // STATUSBAR_H
