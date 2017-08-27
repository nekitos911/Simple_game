#ifndef GAME_H
#define GAME_H

#include "constants.h"
#include "level.h"
#include "animationmanager.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "statusbar.h"
#include "loading.h"
#include "gamewindow.h"
#include "mainmenu.h"

class Game
{
public:
    Game(bool l_isFirstPlay = true); //Initialize the game
    void SetWall(std::string name,float x,float y,float w,float h); // Set level static objects
    void SetPlayer(float x,float y,float w,float h); // Set Player
    void SetEnemy(float x,float y,float w,float h); // Set Enemies
    void SetCoins();

    void EnemyDie(); // Check for Enemies death
    void PlayerDie(); // Check for Player die
    void PlayerBulletRect();
    void EntitiesDie(); // Delete bullets and enemies
    void GameReset(); // Restart level,if player has died

    void SetView(float x,float y); // Set coordinates fo view
    void GameLoop(); // Main loop
    void Events(); // Events
    void HandleInput(); // Set keys for player
    void Update(); // Update the world
    void Draw(); // Draw the world
    bool IsNewGame();
    bool IsPlaying();
private:
    float timer,playerDeathAnimTimer;
    int loadingX,loadingY;
    float tempX,tempY;
    bool isNewGame,isPlaying;
    bool isFirstPlay;
    float PlayerX,PlayerY;
    std::string wallName;
    RenderWindow window;
    Clock clock;
    AnimationManager playerAnim;
    AnimationManager bulletAnim;
    AnimationManager enemyAnim;
    Player *player;
    Enemy *enemy;
    StatusBar *statusbar;
    Level level;
    View view;
    Image worldImage;
    Image playerImage;
    Image bulletImage;
    Image enemyImage;
    Image statusImage;
    Object playerObject;
    std::vector<Object> groundObjects;
    std::vector<Object> blockObjects;
    std::vector<Object> waterObjects;
    std::vector<Object> enemyObjects;
    std::vector<Object> ladderObjects;
    b2Vec2 gravity;
    b2Body *playerBody;
    std::vector<b2Body*> b_ground;
    std::list<b2Body*> enemybody;
    b2Body *bulletBody;
    b2World *world;
    std::list<Entity*> entities;
    Loading *loading;
    GameWindow *gamewindow;
    Music music;
    MainMenu *menu;
};

#endif // GAME_H
