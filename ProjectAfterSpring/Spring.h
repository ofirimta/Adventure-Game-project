#pragma once
#include "Enums.h"
#include "Point.h"
#include "Screen.h"

class Player;  

class Spring
{
	Screen& my_screen;
	Point point_of_start;

	Direction my_oposite_direction;  
	Direction my_spring_direction;


	int my_power = 0;    
	int game_cycles = 0; 

	int counter_char_of_spring = 0;

	bool start_spring = 0;
	
public:

	Spring(Screen& screen);

	int getCounterChar() const
	{
		return counter_char_of_spring;
	}

	bool getIfStart() const
	{
		return start_spring;
	}

	Direction getOpositeDirection() const
	{
		return my_oposite_direction;
	}

	void ChangeCycles()  
	{
		game_cycles = my_power * my_power;
	}

	void resetPower(Player& my_player);
	void SetPower(Player& my_player);
	void SetPower(Player& my_player, int power);
	Direction updateSpringDirection() const;
	bool ifItsLegalAccess(Point& my_next_point, int current_room_index);


	bool collectChars(Player& my_player, Point& my_next_point, int current_room); 
	void update(Player& my_player);
	void drawChars(Player& my_player, int room_index);
	void startSpringFunc(Player& my_player, int current_room_index);         
	Direction getSpringDirection() const //Added By ofir
	{
		return my_spring_direction;
	}
	void triggerExternalForce(Player& my_player, int speed, Direction dir);
};