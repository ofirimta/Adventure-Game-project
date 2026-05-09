#include "Game.h"
#include <Windows.h> 
#include <cctype>   

const char player1_keys[NUM_KEYS + 1] = { 'w', 'd', 'x', 'a', 's', 'e' };
const char player2_keys[NUM_KEYS + 1] = { 'i', 'l', 'm', 'j', 'k', 'o' };


Game::Game() :
    game_bomb(Point(), game_screen),  spring1(game_screen), spring2(game_screen), game_riddle(game_screen),  pDoor(game_screen, 0, false, false),
    player1(Point(0, 0, 0, 0, '$'), player1_keys, game_screen, '$', game_bomb, spring1, current_room_index, &pDoor, game_riddle),
    player2(Point(0, 0, 0, 0, '&'), player2_keys, game_screen, '&', game_bomb, spring2, current_room_index, &pDoor, game_riddle)
{
    loadAllLevels(); 
    player1.setPartner(&player2);
    player2.setPartner(&player1);
}

void Game::setupLevel(int current_room_index)
{
    player1.setDoor(&pDoor);
    player2.setDoor(&pDoor);

    if (current_room_index >= all_levels_data.size()) 
        throw std::out_of_range("Game Logic Error: Attempted to setup invalid level index: " + std::to_string(current_room_index));

    const LevelData& currentLevel = all_levels_data[current_room_index];

    if (currentLevel.hasDoor) 
    {
        const auto& d = currentLevel.doorData;

        pDoor.configure(d.keysNumber, d.switchesNumber, d.switchCode, d.switch_x, d.switch_y, d.id);
    }

    player1.resetLevelpos(currentLevel.p1Start.getX(), currentLevel.p1Start.getY()); 
    player2.resetLevelpos(currentLevel.p2Start.getX(), currentLevel.p2Start.getY());

    player1.setHeldItem(ItemType::NONE); 
    player2.setHeldItem(ItemType::NONE);

    initObstacles(current_room_index); 

    if (currentLevel.isDark) 
    {
        game_screen.setDarkness(current_room_index, currentLevel.darkX1, currentLevel.darkY1, currentLevel.darkX2, currentLevel.darkY2);
    }
    else
    {
        game_screen.setDarkness(current_room_index, 0, 0, 0, 0);
    }
}
void Game::runGameLoop()
{
    setupLevel(current_room_index); 
    drawLevelState();

    bool wasLightOn = isAnyPlayerHoldingTorch();
    int last_room_index = current_room_index;

    while (state == GameState::RUNNING)
    {
        if (current_room_index != last_room_index) 
        { 
            last_room_index = current_room_index;  
            setupLevel(current_room_index);        
            drawLevelState();
            wasLightOn = isAnyPlayerHoldingTorch(); 
        }

        updateLighting(wasLightOn);  

        char key = 0;     
        if (_kbhit()) 
        {
            key = _getch();
            processGameInput(key, current_room_index);
        }

        if (state != GameState::RUNNING) 
        {
            break;
        }
     
        if (current_room_index < game_screen.getNumLevels()-1)
        {
            player1.move();
            if (player2.isAlive()) player2.draw();

            player2.move();
            if (player1.isAlive()) player1.draw();
        }

        game_bomb.update(player1, player2);  
        spring1.update(player1);
        spring2.update(player2);

        game_screen.setHealthAt(player1, current_room_index); 
        game_screen.setHealthAt(player2, current_room_index);

        game_screen.setScoreAt(player1,player2, current_room_index);
        Sleep(150);
    }
}

void Game::processGameInput(char key, int current_room_index)
{
    if (key == ESC)   
    {
        game_screen.delMessageAt(current_room_index);
        const char* new_message = "The_game_is_paused.";
        game_screen.setMessageAt(current_room_index, new_message);

        char ch = _getch();

        while ((ch != ESC))
        {
            if (ch == H || ch == h)
            {
                state = GameState::MENU;
                game_screen.delMessageAt(current_room_index);
                return;
            }
            ch = _getch();
        }
        game_screen.delMessageAt(current_room_index);
        return;
    }

    player1.handleKeyPressed(key);
    player2.handleKeyPressed(key);
}

void Game::run() {
    hideCursor();

    while (state != GameState::EXIT) {
        switch (state) {
        case GameState::MENU:
            game_menu.draw(0);
            handleMenuChoice((char)_getch());
            break;

        case GameState::RUNNING:
            runGameLoop();
            break;

        case GameState::EXIT:
            break;
        }
    }

    cls();
    std::cout << "Goodbye!" << std::endl;
}

void Game::handleMenuChoice(char choice) {
    switch (choice) {
    case ONE: 
        current_room_index = 0;
        game_screen.restart();

        player1.ResetHealth();
        player2.ResetHealth();

		player1.setScore(0);
        player2.setScore(0);

        player1.setHeldItem(ItemType::NONE);
        player2.setHeldItem(ItemType::NONE);

        spring1.resetPower(player1);
        spring2.resetPower(player2);

        pDoor.ResetDoor();  

        state = GameState::RUNNING;
        break;

    case NINE: 
        state = GameState::EXIT;
        break;

    case EIGHT: 
    { 
        game_menu.draw(1);
        [[maybe_unused]] char ignore = _getch();
        break;
    }

    default:
        break;
    }
}

void Game::initObstacles(int room_index)
{
    levels_obstacles.clear();
    bool visited[MAX_Y][MAX_X] = { false };

    for (int y = 0; y < MAX_Y; y++)
    {
        for (int x = 0; x < MAX_X; x++)
        {
            Point p(x, y, 0, 0, ' ');
            char ch = game_screen.getCharAt(p, room_index);

            if (ch == OBSTACLE_CHAR && !visited[y][x])
            {
                levels_obstacles.emplace_back(game_screen, p, room_index, visited);
            }
        }
    }

    player1.setObstacles(&levels_obstacles);
    player2.setObstacles(&levels_obstacles);
}

void Game::drawLevelState()
{
    bool isLightOn = isAnyPlayerHoldingTorch();
    game_screen.draw(current_room_index, isLightOn);

    game_screen.setHealthAt(player1, current_room_index);
    game_screen.setHealthAt(player2, current_room_index);

	game_screen.setScoreAt(player1, player2, current_room_index);

    if (player1.isAlive()) player1.draw();
    if (player2.isAlive()) player2.draw();
}

void Game::updateLighting(bool& wasLightOn)
{
    bool isLightOn = isAnyPlayerHoldingTorch();

    if (isLightOn != wasLightOn)
    {
        game_screen.updateLight(current_room_index, isLightOn);

        if (player1.isAlive()) player1.draw();
        if (player2.isAlive()) player2.draw();

        wasLightOn = isLightOn;
    }
}

void Game::loadAllLevels()  
{
    int room = 1; 
    bool keepLoading = true;

    while (keepLoading)
    {
        LevelData data = Files::loadLevel(room);
        if (data.isValid)
        {
            game_screen.addScreenFromFile(data.currentroom, data.legendLoc);

            all_levels_data.push_back(data);
            room++;
        }
        else
        {
			if (room == 1) 
            {
                throw std::runtime_error("CRITICAL ERROR: Could not load level 1. Check if 'adv-world_01.screen.txt' exists.");
            }

            keepLoading = false;
        }
    }
}

void Game::printErrorMessage(const std::string& msg)
{
    system("cls");
    std::cout << "\n============================================" << std::endl;
    std::cout << "               GAME CRASHED                 " << std::endl;
    std::cout << "============================================" << std::endl;
    std::cout << "Error: " << msg << std::endl;
    std::cout << "============================================" << std::endl;
    std::cout << "\nPress any key to exit..." << std::endl;
    _getch();
}