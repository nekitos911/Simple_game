#include "entity.h"

Entity::Entity(std::string l_name,AnimationManager &l_anim,float X,float Y,bool Dir)
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

FloatRect Entity::GetRect() { return FloatRect(x,y,w,h); }
FloatRect Entity::GetBodyRect() { return FloatRect(x,y - h / 2,w,h); }

bool Entity::IsLife() {
    return isLife;
}
void Entity::Die() {
    isLife = false;
}

std::string Entity::GetName() { return m_name; }

void Entity::SetPlayerCoords(float l_playerX,float l_playerY,float l_playerW,float l_playerH) {
    playerX = l_playerX;
    playerY = l_playerY;
    playerW = l_playerW;
    playerH = l_playerH;
}

bool Entity::IsShoot() {
    if(m_anim.GetName() != "walk" && m_anim.GetName() != "stay" )  {
        if(timer > 800) {
            timer = 0;
            return true;
        }
        else return false;
    }
    return false;
}

float Entity::GetTimer() { return timer;}

std::string Entity::GetState() { return m_boss;}
