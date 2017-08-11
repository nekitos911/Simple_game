#ifndef BULLET_H
#define BULLET_H

#include "animationmanager.h"
#include "constants.h"
#include "entity.h"

class Bullet : public Entity
{
public:
    Bullet(std::string l_name,AnimationManager &l_anim,Level &level,int X,int Y,bool Dir);

    void Update(float &time); // Update bullets
};

#endif // BULLET_H
