#ifndef ENTITY_H
#define ENTITY_H

#include "constants.h"
#include "animationmanager.h"
#include "level.h"

using namespace sf;

class Entity
{
public:
    Entity(std::string l_name,AnimationManager &l_anim,int X, int Y,bool Dir);

    bool IsLife(); // Check for life
    void Die(); // If died
    std::string GetName(); // Get entity name

    virtual void Update(float &time) = 0;

    void Draw(RenderWindow &window); // Draw entities

    void SetPlayerCoords(int l_playerX,int l_playerY); // Get player coords

    bool IsShoot();

    IntRect GetRect();
    IntRect GetBodyRect();
protected:
    int x,y,w,h;
    int playerX,playerY;
    AnimationManager m_anim;
    Texture texture;
    bool isLife,dir;
    float m_speed,timer;
    std::vector<Object> objects;
    std::string m_name;
};


#endif // ENTITY_H
