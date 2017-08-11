#include "enemy.h"

Enemy::Enemy(std::string l_name,AnimationManager &l_anim,Level &level,int X,int Y,bool Dir,std::list<b2Body*>::iterator it):Entity(l_name,l_anim,X,Y,Dir)
{
    m_speed = 2.0f;
    m_anim.Set("walk");
    m_anim.Flip(false);
    SetEnemyBody(*it);
    objects = level.GetObjects("wall");
}

void Enemy::Update(float &time) {
    SeePlayer(playerX,playerY);

    if (m_anim.GetName() == "walk") {
        for (size_t i = 0; i < objects.size();i ++) {
            if (objects[i].name == "wall") {
                if ((int)enemyBody->GetPosition().x == int(objects[i].rect.left  / SCALE)) {
                    if(m_speed > 0)
                    m_anim.Flip(true);
                    else m_anim.Flip(false);
                    m_speed *= -1;
                }
            }
        }
            enemyBody->SetLinearVelocity(b2Vec2(m_speed,0.0f));
    }
    b2Vec2 pos = enemyBody->GetPosition();
    x = (pos.x * SCALE);
    y = pos.y * SCALE;
    m_anim.Tick(time);
}

void Enemy::SetEnemyBody(b2Body *l_body) {
    enemyBody = l_body;
}

void Enemy::SeePlayer(int X,int Y) {
    if (enemyBody->GetPosition().x * SCALE < X + VIEW_WIDTH / 2) {
        m_anim.Flip(true);
        enemyBody->SetLinearVelocity(b2Vec2(0.0f,0.0f));
        m_anim.Set("shoot");
    }
    else m_anim.Set("walk");
}
