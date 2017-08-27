#include "enemy.h"

Enemy::Enemy(std::string l_name,std::string state,std::string name,AnimationManager &l_anim,Level &level,float X,float Y,bool Dir,std::list<b2Body*>::iterator it):Entity(l_name,l_anim,X,Y,Dir)
{
    m_boss = name;
    timer = 0;
    m_state = state;
    m_anim.Flip(true);
    m_speed = -2.0f;
    if(m_state != "stay") m_anim.Set("walk");
    else m_anim.Set("stay");
    SetEnemyBody(*it);
    objects = level.GetObjects("wall");
}

void Enemy::Update(float &time) {
    if (m_anim.GetName() != "stay" || m_anim.GetName() != "walk")
    timer += clock.getElapsedTime().asMilliseconds();
    clock.restart();

    b2Vec2 pos = enemyBody->GetPosition();
    x = (pos.x * SCALE);
    y = pos.y * SCALE;
    SeePlayer(playerX,playerY,playerW,playerH);

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
            if(m_state != "stay")
            enemyBody->SetLinearVelocity(b2Vec2(m_speed,0.0f));
    }
    m_anim.Tick(time);
}

void Enemy::SetEnemyBody(b2Body *l_body) {
    enemyBody = l_body;
}

void Enemy::SeePlayer(float X,float Y,float W,float H) {
    if(Y + VIEW_HEIGHT / 2 > enemyBody->GetPosition().y * SCALE && Y - VIEW_HEIGHT / 2 < enemyBody->GetPosition().y * SCALE) {
    if (X + VIEW_WIDTH / 2 > enemyBody->GetPosition().x * SCALE && X < enemyBody->GetPosition().x * SCALE ) {
        m_anim.Flip(true);
        enemyBody->SetLinearVelocity(b2Vec2(0.0f,0.0f));
        if(Y - H < GetRect().top  && Y + H > GetRect().top)
            m_anim.Set("shoot");
        else if (Y + H > GetRect().top)
            m_anim.Set("shootDown");
        else if (Y - H < GetRect().top) {
            y -= m_anim.getH() / 6;
            m_anim.Set("shootUp");
        }
    }
    else if(X > enemyBody->GetPosition().x * SCALE && X - VIEW_WIDTH / 2 <  enemyBody->GetPosition().x * SCALE  ) {
        m_anim.Flip(false);
        enemyBody->SetLinearVelocity(b2Vec2(0.0f,0.0f));
        if(Y - H <GetRect().top  && Y + H  > GetRect().top)
        m_anim.Set("shoot");
        else if (Y + H > GetRect().top)
            m_anim.Set("shootDown");
        else if (Y - H < GetRect().top) {
            y -= m_anim.getH() / 6;
            m_anim.Set("shootUp");
        }
    }
    else {
        if(m_state != "stay") m_anim.Set("walk");
        else m_anim.Set("stay");
    }
    } else {
        if(m_state != "stay") m_anim.Set("walk");
        else m_anim.Set("stay");
    }
}
