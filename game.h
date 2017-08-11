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

class Game
{
public:
    Game(); //Initialize the game
    void SetWall(std::string name,int x,int y,int w,int h); // Set level static objects
    void SetPlayer(int x,int y,int w,int h); // Set Player
    void SetEnemy(int x,int y,int w,int h); // Set Enemies
    void SetCoins();

    void EnemyDie(); // Check for Enemies death
    void PlayerDie(); // Check for Player die
    void PlayerBulletRect();
    void EntitiesDie(); // Delete bullets and enemies
    void GameReset(); // Restart level,if player has died

    void SetView(int x,int y); // Set coordinates fo view
    void GameLoop(); // Main loop
    void Events(); // Events
    void HandleInput(); // Set keys for player
    void Update(); // Update the world
    void Draw(); // Draw the world
private:
    float timer,playerDeathAnimTimer;
    int loadingX,loadingY;
    float tempX,tempY;
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
    Image icon;
    Object playerObject;
    std::vector<Object> groundObjects;
    std::vector<Object> blockObjects;
    std::vector<Object> waterObjects;
    std::vector<Object> enemyObjects;
    b2Vec2 gravity;
    b2Body *playerBody;
    std::vector<b2Body*> b_ground;
    std::list<b2Body*> enemybody;
    b2Body *bulletBody;
    b2World *world;
    std::list<Entity*> entities;
    Loading *loading;
};

#endif // GAME_H
