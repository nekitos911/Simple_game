#include "bullet.h"

Bullet::Bullet (std::string l_name,AnimationManager &l_anim,Level &level,float X,float Y,bool Dir) : Entity(l_name,l_anim,X,Y,Dir)
{
    m_speed = 0.2;
    m_anim.Set("move");
    objects = level.GetAllObjects();
}

void Bullet::Update(float &time) {
    for (size_t i = 0;i < objects.size();i ++)
        if(objects[i].name == "block")
            if (GetRect().intersects(objects[i].rect))
                isLife = false;
    if(!dir) x += m_speed * time;
    else x -= m_speed * time;
    if(m_name == "bulletDown" || m_name == "enemyBulletDown" ) y += m_speed * time;
    else if(m_name == "bulletUp" || m_name == "enemyBulletUp") y -= m_speed * time;
    if (!isLife) m_anim.Set("explode");
    m_anim.Tick(time);
}

