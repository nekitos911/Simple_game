#ifndef PLAYER_H
#define PLAYER_H

#include "animationmanager.h"
#include "level.h"

enum class STATE {stay,walk,jump,duck,death};


class Player
{
public:
    Player(AnimationManager &l_anim,Object &l_player,std::vector<Object> &l_ground);
    Player();

    std::map<std::string,bool> key;

    void KeyCheck();
    void HandleInput();
    void Update(float &time);
    void SetView();
    void SetAnim();
    void Die(RenderWindow &window);
    void GameOver(RenderWindow &window);
    void Reset();
    void DrawPlayer(b2World &world,int x,int y,int w,int h);
    void Collision();
    int GetLife();
    int GetScore();
    AnimationManager &GetAnim();
    IntRect GetRect();
    float GetH();
    float GetW();
    int GetCoordX();
    int GetCoordY();
    void IncreaseScore(int l_score);
    void SetPlayerBody(b2Body * l_body);
    void SetGroundBody(std::vector<b2Body*> l_body);
    void Draw(RenderWindow &window);
    bool IsShoot();
    bool IsLife();
    void IsLife(bool l_life);
    void SetIsShoot(bool l_isShoot);
    bool GetIsShoot();
    std::string GetState();
    bool GetFlip();
private:
    int m_life,m_score;
    bool onLadder,isShoot,hit,onGround,isLife;
    int x,y;
    float w,h;
    AnimationManager m_anim;
    Object player;
    std::vector<Object> ground;
    STATE m_state;
    b2Body *playerBody;
    std::vector<b2Body*> b_ground;
    Clock clock;
    bool isFlip;
};

#endif // PLAYER_H
