#ifndef ENEMY_H
#define ENEMY_H

#include "constants.h"
#include "entity.h"

class Enemy:public Entity
{
public:
    Enemy(std::string l_name,std::string state,std::string naem,AnimationManager &l_anim,Level &level,float X,float Y,bool Dir,std::list<b2Body*>::iterator it);
    void Update(float &time); // Update enemies
    void SetEnemyBody(b2Body  *l_body); // Set enemy body for world
    void SeePlayer(float X,float Y,float W,float H); // Checks the location of player
private:
    b2Body *enemyBody;
    bool isShoot;
};

#endif // ENEMY_H
