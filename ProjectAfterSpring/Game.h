#pragma once

#include "Enums.h"
#include "Screen.h"
#include "Player.h"
#include "Bomb.h"
#include "Door.h"
#include "Menu.h"
#include "riddle.h" 
#include "utils.h" 
#include "Obstacle.h"
#include "Spring.h"
#include "Files.h"

#include <conio.h> 

class Game {
public:
    enum class GameState {
        MENU,
        RUNNING,
        EXIT
    };

private:
    Screen game_screen;
    Menu game_menu;
    Bomb game_bomb;
    Spring spring1;
    Spring spring2;
    riddle game_riddle;
    Door pDoor;  
    int current_room_index = 0;
    Player player1;
    Player player2;
    GameState state = GameState::MENU;
    std::vector<Obstacle> levels_obstacles;
    void initObstacles(int room_index);
    std::vector<LevelData> all_levels_data;

    void setupLevel(int current_room_index);
    void runGameLoop();
    void processGameInput(char key, int current_room_index);
    void handleMenuChoice(char choice);
    bool isAnyPlayerHoldingTorch() const
    {
        return (player1.getHeldItem() == ItemType::TORCH) || (player2.getHeldItem() == ItemType::TORCH);
    }
    void drawLevelState();
    void updateLighting(bool& wasLightOn);
    void loadAllLevels();

public:
    Game();
    void run();
    static void printErrorMessage(const std::string& msg);
};