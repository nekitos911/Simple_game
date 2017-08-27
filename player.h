#ifndef PLAYER_H
#define PLAYER_H

#include "animationmanager.h"
#include "level.h"
#include "gameovermenu.h"
#include "gamewindow.h"

enum class STATE {stay,walk,jump,duck,death,climb};


class Player
{
public:
    Player(AnimationManager &l_anim,Object &l_player,std::vector<Object> &l_ground,std::vector<Object> &l_ladder);
    Player();

    std::map<std::string,bool> key;

    void KeyCheck();
    void HandleInput();
    void Update(float &time);
    void SetView();
    void SetAnim();
    void Die(RenderWindow &window,View &view);
    void GameOver(RenderWindow &window,View &view);
    void Reset();
    void DrawPlayer(b2World &world,float x,float y,float w,float h);
    int Collision();
    int GetLife();
    int GetScore();
    AnimationManager &GetAnim();
    FloatRect GetRect();
    float GetH();
    float GetW();
    float GetCoordX();
    float GetCoordY();
    void IncreaseScore(int l_score);
    std::string GetLook();
    void SetPlayerBody(b2Body * l_body);
    void SetGroundBody(std::vector<b2Body*> l_body);
    void Draw(RenderWindow &window);
    bool IsShoot();
    bool IsLife();
    void IsLife(bool l_life);
    void SetIsShoot(bool l_isShoot);
    int GetGroundNum();
    bool GetIsShoot();
    void SetCoordY(float Y);
    std::string GetState();
    bool GetFlip();
    bool IsNewGame();
    bool IsPlaying();
    bool IsMainMenu();
    bool IsOnLadder();
    bool IsOnGround();
private:
    int m_life,m_score;
    bool onLadder,isShoot,hit,onGround,isLife,isLookDown,isLookUp;
    float x,y;
    float w,h;
    AnimationManager m_anim;
    Object player;
    std::vector<Object> ladder;
    std::vector<Object> ground;
    STATE m_state;
    b2Body *playerBody;
    std::vector<b2Body*> b_ground;
    Clock clock;
    bool isFlip;
    bool newGame,isPlaying,isMainMenu;
    int groundNum;
    GameOverMenu *gameOverMenu;
    GameWindow * gamewindow;
};

#endif // PLAYER_H
