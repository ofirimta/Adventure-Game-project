#pragma once

#include "Enums.h"
#include "Point.h"
#include "Screen.h"
#include "Player.h"



class Door  
{
	int num_of_door;   
	Screen& my_screen;
	int counter = 0;  
	bool need_key;
	int num_of_key = 0;
	int counter_of_keys = 0;
	bool collect_all_key = 0;
	bool need_switch;
	int num_of_switch;
	const char* solution;
    Point first_point_of_switches;
	bool itsAMatch = 0;
	bool door_is_open = 0;

public:

	Door(Screen& screen, int my_door_num, bool if_need_a_key, bool if_need_a_switch, int how_many_keys = -1, int how_many_switches = -1, const char* solu = "", Point p = Point(0, 0, 0, 0, 'w'));

	void AddThisKey()
	{
		counter_of_keys++;   
		setThisKey();
	}

	void DeleteThisKey()
	{
		counter_of_keys--; 
		setThisKey();
	}
	
	void setThisKey()
	{
		if (num_of_key <= counter_of_keys)
		{
			collect_all_key = 1;
		}
		else
		{
			collect_all_key = 0;
		}
	}
 
	void itsAMatchFunc()
	{
		if ((collect_all_key != 0) && (need_key != 0))
		{
			itsAMatch = 1;
		}
		else
		{
			itsAMatch = 0;
		}
	}

	void itsASwitchMatch(int my_room);
	void openDoor(Player my_player, int room);
	void openDoor(int room);
	void changeRoom(Player& my_character, int& room);  
	void ResetDoor();

	int getNumDoor() const
	{
		return (num_of_door);
	}

	bool getifSwitch() const
	{
		return (need_switch);
	}
	void addOneToCounter()
	{
		counter++;
	}
	int showCounter() const
	{
		return counter;
	}
	bool isDoorOpen() const
	{
		return door_is_open;
	}
	bool getItsAMatch()
	{
		if (need_key == 1)
		{
			itsAMatchFunc();
		}
		return itsAMatch;
	}
	void configure(int keys_needed, int switches_needed, const string& code, int x_switch, int y_switch, int id);
};