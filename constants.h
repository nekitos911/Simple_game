#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Box2D/Box2D.h>
#include <Box2D/Common/b2Math.h>
#include <Box2D/Dynamics/b2Body.h>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "lib/tinyxml2.h"
#include <iostream>
#include <list>
#include <vector>
using namespace sf;

const float SCALE = 30.0f; // metres to coordinates
const short COLLISION_BREAK = -1; // Num for check player onGround
const short WINDOW_WIDTH = 1920;
const short WINDOW_HEIGHT = 1080;
const short VIEW_WIDTH = 640;
const short VIEW_HEIGHT = 480;
const short OFFSET_X = 36; // Offset for view
const short CONTENT_OFFSET_X = 40;
const short CONTENT_OFFSET_Y = 5;
const short STATUSBAR_POSITION_Y = 30;
const short BLOCKS_COUNT = 2; // Count of map walls(default 4)
const uint16 PLAYER_CATEGORY = 0x0002;
const uint16 PLAYER_MASK = 0x0001;
const uint16 WALL_CATEGORY = 0x0001;
const uint16 WALL_MASK = 0x0002;
const uint16 ENEMY_CATEGORY = 0x0001;
const uint16 ENEMY_MASK = 0x0002;
const short CONTENT_SIZE = 16;
const short LOADING_CONTENT_SIZE = 30;
const short PLAYER_LIFE = 3;
#endif // CONSTANTS_H
