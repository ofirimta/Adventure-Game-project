
#pragma once
#include "Point.h"
#include "Enums.h"
#include "Bomb.h"
#include "Screen.h"
#include "Obstacle.h"

class Screen;
class Door;
class riddle;
class Spring;


class Player {


    Point location;         
    char keys[NUM_KEYS];    
    Screen& screen;
    Bomb& active_bomb;
    Spring& my_spring;
    const char character;  
    ItemType held_item;     
    int& current_room_index; 
    bool is_finished_level = false; 
    int life_count = 3; 
    Door* pDoor;
    riddle& my_riddle_cla;
    int speed = 1;
    int Score = 0; 
    Player* partner = nullptr; 
    std::vector<Obstacle>* my_obstacles = nullptr; 

private:
    char char_under_player = ' ';

public:
    Player(const Point& point, const char(&the_keys)[NUM_KEYS + 1], Screen& theScreen, char character, Bomb& bomb_ref, Spring& spring, int& current_room, Door* current_room_door, riddle& riddle_cla);
    void draw();
    void move();
    void moveOneStep();
    void handleKeyPressed(char key);
    void handleDoor(char char_on_screen);
    void disposeItem();
    void setHeldItem(ItemType type);
    ItemType getHeldItem() const
    {
        return held_item;
    }
    void handleCollision(int component_char);
    bool isFinished() const { return is_finished_level; }
    void disappear();
    void appear();
    int getCurrentRoomIndex() const
    {
        return current_room_index;
    }
    char getCharacter() const
    {
        return character;
    }
    int getLifeCount() const
    {
        return life_count;
    }
    Point getLocation() const
    {
        return location;
    }
    void hitByBomb()
    {
        life_count--;
        if (life_count <= 0)
        {
            disappear();
        }
    }
    void ResetHealth()
    {
        life_count = 3;
        is_finished_level = false;
    }
    bool isAlive() const
    {
        return life_count > 0;
    }
    void resetLevelpos(int x, int y);
    void setDoor(Door* new_door)
    {
        pDoor = new_door;
    }
    void increaseScore()
    {
        Score = Score + 1;
    }
    void setPartner(Player* other_player)
    {
        partner = other_player;
    }
    void setObstacles(std::vector<Obstacle>* obstacles)
    {
        my_obstacles = obstacles;
    }
    void handleObstacle();
    int manageForce();
    int getSpeed() const
    {
        return speed;
    }
    void setSpeed(int s)
    {
        speed = s;
    }
    void setDirection(Direction dir)
    {
        location.setDirection(dir);
    }
    void resetSpring(Player& my_player, Point& my_location);
    Spring& getSpring() const
    {
        return my_spring;  
    }
    bool isOpposite(Direction dir1, Direction dir2) const;
    void setScore(int new_score)
    {
        Score = new_score;
    }
    int getScore() const
    {
        return Score;
    }
};