#ifndef ENTITY_H
#define ENTITY_H

#include "constants.h"
#include "animationmanager.h"
#include "level.h"

using namespace sf;

class Entity
{
public:
    Entity(std::string l_name,AnimationManager &l_anim,float X, float Y,bool Dir);

    bool IsLife(); // Check for life
    void Die(); // If died
    std::string GetName(); // Get entity name

    virtual void Update(float &time) = 0;

    void Draw(RenderWindow &window); // Draw entities

    void SetPlayerCoords(float l_playerX,float l_playerY,float l_playerW,float l_playerH); // Get player coords
    float GetTimer();

    bool IsShoot();
    std::string GetState();

    FloatRect GetRect();
    FloatRect GetBodyRect();
protected:
    Clock clock;
    float x,y,w,h;
    float playerX,playerY,playerW,playerH;
    AnimationManager m_anim;
    Texture texture;
    bool isLife,dir;
    float m_speed,timer;
    std::vector<Object> objects;
    std::string m_name;
    std::string m_state;
    std::string m_boss;
};


#endif // ENTITY_H
