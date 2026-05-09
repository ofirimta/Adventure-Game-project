#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;

enum class Direction {
	UP,
	RIGHT,
	DOWN,
	LEFT,
	STAY

}; 

enum { MAX_X = 80, MAX_Y = 25 };
enum special_nums_for_menu { NINE = 57, ONE = 49, EIGHT = 56 };   
enum special_nums_for_riddle { Three = 51, FOUR = 52 }; 
enum special_nums_for_game { ESC = 27, H = 72, h = 104 };  

enum class ItemType
{
	NONE,
	KEY,
	BOMB,
	RIDDLE,
	SWITCH_ON,
	SWITCH_OFF,
	TORCH,
	SPRING
};

const char RIDDLE_CHAR = '?';
const char BOMB_CHAR = '@';
const char KEY_CHAR = 'K';
const char SWITCH_ON_CHAR = '/';
const char SWITCH_OFF_CHAR = '\\';
const char IMMUTABLE_WALL_CHAR = 'i';
const char WALL_CHAR = 'w';
const char OBSTACLE_CHAR = '*';
const char TORCH_CHAR = '!';
const char SPRING_CHAR = '#';
const char PLAYER1_CHAR = '$';
const char PLAYER2_CHAR = '&';
const char LIFE_GIFT_CHAR = '+';

const int NUM_KEYS = 6;  
const int MOVE_KEYS_COUNT = 5; 

constexpr int DOORS = 3;

enum BombSettings
{
	EXPLOSION_RADIUS = 3,
	EXPLODE_TIMER = 5
};