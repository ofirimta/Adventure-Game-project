#define _CRT_SECURE_NO_WARNINGS
#include "Screen.h"
#include "Player.h"

void Screen::draw(int room, bool hasTorch) const
{
	if (room < 0 || room >= current_screens.size()) return;

	cls();
	gotoxy(0, 0);

	bool is_room_dark = dark_rooms[room].isDark;
	bool shouldHideDetails = is_room_dark && !hasTorch; 

	if (!shouldHideDetails) 
	{
		for (size_t i = 0; i < current_screens[room].size() - 1; ++i)
		{
			cout << current_screens[room][i] << endl;
		}
		cout << current_screens[room].back();
	}

	else 
	{

		int x1 = dark_rooms[room].x1;
		int y1 = dark_rooms[room].y1;
		int x2 = dark_rooms[room].x2;
		int y2 = dark_rooms[room].y2;

		for (size_t y = 0; y < current_screens[room].size(); ++y)
		{
			for (size_t x = 0; x < current_screens[room][y].size(); ++x)
			{
				bool inside = (x >= x1 && x <= x2) && (y >= y1 && y <= y2);

				if (inside) {
					cout << ' ';
				}
				else
				{
					cout << current_screens[room][y][x];
				}
			}
			cout << endl;
		}
	}
	cout.flush();
}

void Screen::setInventoryAt(const Player& my_player, int room)
{
	if (notValidRoom(room))
		return;

	size_t baseX = legend_locations[room].getX();
	size_t baseY = legend_locations[room].getY();
	int y = baseY + 2;
	char player_sign = my_player.getCharacter();
	int i = 0;
	ItemType my_item_type = my_player.getHeldItem();  
	const char* new_inventory = "";

	switch (my_item_type)
	{
	case ItemType::NONE:
		new_inventory = "NONE";
		break;
	case ItemType::KEY:
		new_inventory = "Key";
		break;
	case ItemType::BOMB:
		new_inventory = "Bomb";
		break;
	case ItemType::SWITCH_ON:
		new_inventory = "On";
		break;
	case ItemType::SWITCH_OFF:
		new_inventory = "Off";
		break;
	case ItemType::TORCH:
		new_inventory = "Torch";
		break;
	}
	char ch = new_inventory[i];
	if (player_sign == '$')
	{
		while (ch != '\0')
		{
			if (baseX + 52 + i < MAX_X)
			{
				current_screens[room][y][baseX + 52 + i] = ch;
				gotoxy(baseX + 52 + i, y);
				cout << ch;
			}
			i++;
			ch = new_inventory[i];
		}
	}
	else
	{
		while (ch != '\0')
		{
			if (baseX + 65 + i < MAX_X)
			{
				current_screens[room][y][baseX + 65 + i] = ch;
				gotoxy(baseX + 65 + i, y);
				cout << ch;
			}
			i++;
			ch = new_inventory[i];
		}
	}
}

void Screen::delInventoryAt(const Player& my_player, int room)
{
	if (notValidRoom(room)) return;

	size_t baseX = legend_locations[room].getX();
	size_t baseY = legend_locations[room].getY();
	int y = baseY + 2;

	char player_sign = my_player.getCharacter();
	int i = 0;

	if (player_sign == '$')
	{
		if (baseX + 52 >= MAX_X) return;
		char ch = current_screens[room][y][baseX + 52 + i];

		while ((ch != ' ') && (ch != '&'))
		{
			if (baseX + 52 + i < MAX_X)
			{
				current_screens[room][y][baseX + 52 + i] = ' ';
				gotoxy(baseX + 52 + i, y);
				cout << ' ';

				i++;
				if (baseX + 52 + i < MAX_X)
					ch = current_screens[room][y][baseX + 52 + i];
				else
					break;
			}
		}
	}
	else
	{
		if (baseX + 65 >= MAX_X) return;

		char ch = current_screens[room][y][baseX + 65 + i];
		while ((ch != ' ') && (ch != '\0'))
		{
			if (baseX + 65 + i < MAX_X) {
				current_screens[room][y][baseX + 65 + i] = ' ';
				gotoxy(baseX + 65 + i, y);
				cout << ' ';

				i++;
				if (baseX + 65 + i < MAX_X)
					ch = current_screens[room][y][baseX + 65 + i];
				else
					break;
			}
		}
	}
}

void Screen::setHealthAt(const Player& my_player, int room)
{
	if (notValidRoom(room)) return;
	size_t baseX = legend_locations[room].getX();
	size_t baseY = legend_locations[room].getY();
	int y = baseY + 2;

	char player_sign = my_player.getCharacter();
	char new_life_val = (char)((my_player.getLifeCount()) + '0');

	if (player_sign == '$')
	{
		if (baseX + 11 < MAX_X)
		{
			current_screens[room][y][baseX + 11] = new_life_val;
			gotoxy(baseX + 11, y);
			cout << new_life_val;
		};
	}
	else
	{
		if (baseX + 17 < MAX_X)
		{
			current_screens[room][y][baseX + 17] = new_life_val;
			gotoxy(baseX + 17, y);
			cout << new_life_val;
		}
	}
	cout.flush();
}


void Screen::setScoreAt(const Player& my_player1, const Player& my_player2, int room)
{
	if (notValidRoom(room)) return;

	size_t baseX = legend_locations[room].getX();
	size_t baseY = legend_locations[room].getY();
	int y = baseY + 3;

	int scoreX = baseX + 68;

	int totalScore = my_player1.getScore() + my_player2.getScore();
	string s = std::to_string(totalScore);


	for (int i = 0; i < 5; i++)  
	{
		if (scoreX + i < MAX_X)
		{
			current_screens[room][y][scoreX + i] = ' ';
		}
	}

	gotoxy(scoreX, y);
	cout << "     ";

	gotoxy(scoreX, y);
	cout << s;

	for (size_t i = 0; i < s.length(); ++i)
	{
		if (scoreX + i < MAX_X)
		{
			current_screens[room][y][scoreX + i] = s[i];
		}
	}

	cout.flush();
}

void Screen::setMessageAt(int room, const char* new_str)
{
	if (notValidRoom(room)) return;

	size_t baseX = legend_locations[room].getX();
	size_t baseY = legend_locations[room].getY();
	int y = baseY + 1;

	int i = 0;

	char ch = new_str[i];
	while (ch != '\0')
	{
		if (baseX + 10 + i < MAX_X)
		{
			current_screens[room][y][baseX + 10 + i] = ch;
			gotoxy(baseX + 10 + i, y);
			cout << ch;
		}
		i++;
		ch = new_str[i];
	}
}

void Screen::setHintAt(int room, const char* new_str)
{
	if (notValidRoom(room)) return;
	size_t baseX = legend_locations[room].getX();
	size_t baseY = legend_locations[room].getY();
	int y = baseY + 3;

	int i = 0;
	char ch = new_str[i];
	while (ch != '\0')
	{
		if (baseX + 7 + i < MAX_X)
		{
			current_screens[room][y][baseX + 7 + i] = ch;
			gotoxy(baseX + 7 + i, y);
			cout << ch;
		}
		i++;
		ch = new_str[i];
	}
}

void Screen::delMessageAt(int room)
{
	if (notValidRoom(room)) return;

	size_t baseX = legend_locations[room].getX();
	size_t baseY = legend_locations[room].getY();
	int y = baseY + 1;

	int i = 0;
	if (baseX + 10 >= MAX_X) return;

	char ch = current_screens[room][y][baseX + 10 + i];

	while ((ch != ' ') && (ch != '\0'))
	{
		if (baseX + 10 + i < MAX_X) {
			current_screens[room][y][baseX + 10 + i] = ' ';
			gotoxy(baseX + 10 + i, y);
			cout << ' ';

			i++;
			if (baseX + 10 + i < MAX_X)
				ch = current_screens[room][y][baseX + 10 + i];
			else
				break;
		}
	}
}

void Screen::restart()
{
	current_screens = templates_screens;
}

void Screen::updateLight(int room, bool hasTorch) const
{
	if (notValidRoom(room)) return;
	if (!dark_rooms[room].isDark) return;

	int x1 = dark_rooms[room].x1;
	int y1 = dark_rooms[room].y1;
	int x2 = dark_rooms[room].x2;
	int y2 = dark_rooms[room].y2;

	for (int y = y1; y <= y2; ++y)  
	{
		for (int x = x1; x <= x2; ++x)
		{
			gotoxy(x, y);

			if (hasTorch)
			{
				cout << current_screens[room][y][x];
			}
			else
			{
				cout << ' ';
			}
		}
	}
	cout.flush();
}

void Screen::addScreenFromFile(const vector<string>& newLevel, const Point& legendLocation)
{
	vector<string> currentLevel = newLevel;
	Point finalLegendPos = legendLocation;

	if (legendLocation.getY() > 19)
	{
		finalLegendPos.setY(0);
		finalLegendPos.setX(0);
	}

	while (currentLevel.size() < MAX_Y)
	{
		currentLevel.push_back(string(MAX_X, ' '));
	}

	for (auto& row : currentLevel)
	{
		row.resize(MAX_X, ' ');


		if (row[0] != 'i' && (row[0] < '1' || row[0] > '9') && row[0] != 'H' && row[0] != 'M')
		{
			row[0] = 'i';
		}

		if (row[MAX_X - 1] != 'i' && (row[MAX_X - 1] < '1' || row[MAX_X - 1] > '9'))
		{
			row[MAX_X - 1] = 'i';
		}
	}

	for (int i = 0; i < MAX_X; i++)
	{
		currentLevel[MAX_Y - 1][i] = 'i';
	}

	if (finalLegendPos.getY() > 0)
	{
		for (int j = 0; j < MAX_X; j++)
		{
			currentLevel[0][j] = 'i';
		}
	}

	LoadLegend(currentLevel, finalLegendPos);

	current_screens.push_back(currentLevel);
	templates_screens.push_back(currentLevel);
	legend_locations.push_back(finalLegendPos);
	dark_rooms.push_back({ false, 0,0,0,0 });
}

void Screen::LoadLegend(vector<string>& currentLevel, const Point& legendLocation)
{
	size_t baseX = 0;
	size_t baseY = legendLocation.getY();

	string lines[] = {
		"iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii",
		"Messages:                                                                  i",
		"Health: $: 3  &: 3     Level: 1/4      Inventory: $:           &:          i",
		"Hints:                                                  Scores:            i",
		"iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii"
	};

	for (int i = 0; i < 5; ++i)
	{
		int currentY = baseY + i;

		if (currentY >= 0 && currentY < MAX_Y)
		{

			for (size_t j = 0; j < lines[i].size() && (baseX + (int)j) < MAX_X; ++j)
			{
				currentLevel[currentY][baseX + j] = lines[i][j];
			}
		}
	}
}