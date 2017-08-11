#include "statusbar.h"

StatusBar::StatusBar(Image &image,int l_mapW) {
    mapW = l_mapW;
    m_font.loadFromFile("Media/arial.ttf");
    for (int i = 0;i < 2;i++) {
        m_content[i].setFont(m_font);
        m_content[i].setCharacterSize(CONTENT_SIZE);
        m_content[i].setFillColor(Color::Black);
        m_content[i].setOrigin(0,0);
    }
    m_texture.loadFromImage(image);
    m_sprite.setTexture(m_texture);
}

void StatusBar::Draw(RenderWindow &window,int x) {
    if (x <= VIEW_WIDTH / 2 - OFFSET_X) {
        x = 0.5 * OFFSET_X;
    }
    else if (x > VIEW_WIDTH / 2 - OFFSET_X && x < mapW - VIEW_WIDTH / 2 - OFFSET_X ){
        x = x - VIEW_WIDTH / 2 + 1.5 * OFFSET_X;
    }
    else if (x >= mapW - VIEW_WIDTH / 2 - OFFSET_X ) {
        x = mapW - VIEW_WIDTH + 0.5 * OFFSET_X;
        m_sprite.setPosition(x,STATUSBAR_POSITION_Y);
        for(int i = 0; i < 2;i++)
        m_content[i].setPosition(x + CONTENT_OFFSET_X,STATUSBAR_POSITION_Y + CONTENT_OFFSET_Y);
    }
    m_sprite.setPosition(x,STATUSBAR_POSITION_Y);
    for(int i = 0; i < 2;i++) {
        m_content[i].setPosition(x + CONTENT_OFFSET_X + i * 100,STATUSBAR_POSITION_Y + CONTENT_OFFSET_Y);
        window.draw(m_content[i]);
    }
    window.draw(m_sprite);
}

void StatusBar::Update(std::string life, std::string score) {
    m_life = life;
    m_score = score;
    m_content[0].setString("x " + m_life);
    m_content[1].setString("Score: " + m_score);
}
