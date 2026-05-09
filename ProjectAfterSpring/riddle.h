#pragma once

#include "Enums.h"
#include "Point.h"
#include "Screen.h"
#include "utils.h"
#include <cctype>  
#include <conio.h>  
#include <fstream>

using std::ifstream;
using std::stoi;
class Player;

class riddle
{
	Screen& my_screen;

	struct my_riddle    
	{
		int x_of_riddle;
		int y_of_riddle;
		int room_of_riddle;
		int correct_ansewr;
		int index_of_my_arr;
		bool if_sloved_riddle;

	};
	
	vector<my_riddle> my_arr;
	vector<vector<string>> riddles_screens;
	static const char* feedback_screens[3][MAX_Y];
	void loadRiddlesFromFile(const string& filename);
	bool last_answer_is_correct = false;

public:

	riddle(Screen& screen);
	my_riddle correctRiddle(Point& p, int my_room); 
	void run(Point& p, int my_room);
	void draw_riddle(int room) const;
	void draw_feedback(int room) const;
	bool getIfSolved() const
	{
		return last_answer_is_correct;
	}

};