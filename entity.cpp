#include "entity.h"

Entity::Entity(std::string l_name,AnimationManager &l_anim,int X,int Y,bool Dir)
{
    m_name = l_name;
    dir = Dir;
    m_anim = l_anim;
    m_anim.Flip(dir);
    x = X;
    y = Y;
    w = m_anim.getW();
    h = m_anim.getH();
    isLife = true;
    timer = 0;


}

void Entity::Draw(RenderWindow &window) {
    m_anim.Draw(window,x,y);
}

IntRect Entity::GetRect() { return IntRect(x,y,w,h); }
IntRect Entity::GetBodyRect() { return IntRect(x,y - h / 2,w,h); }

bool Entity::IsLife() {
    return isLife;
}
void Entity::Die() {
    isLife = false;
}

std::string Entity::GetName() { return m_name; }

void Entity::SetPlayerCoords(int l_playerX,int l_playerY) {
    playerX = l_playerX;
    playerY = l_playerY;
}

bool Entity::IsShoot() {
    if(m_anim.GetName() != "walk") return true;
    return false;
}
