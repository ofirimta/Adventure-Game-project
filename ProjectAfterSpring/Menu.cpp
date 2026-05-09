#include "Menu.h"
void Menu::draw(int room)
const {
	cls();
	gotoxy(0, 0);

	for (size_t i = 0; i < MAX_Y - 1; ++i)
	{
		cout << menu_screens[room][i] << endl;
	}
	cout << menu_screens[room][MAX_Y - 1];
	cout.flush();
}

int Menu::user_choice() const
{
	while (true)
	{
		char key = (char)_getch(); 
		if (key == special_nums_for_menu::EIGHT)
		{
			draw(1);
			key = (char)_getch();  
			draw(0);
		}
		else if (key == special_nums_for_menu::ONE)
		{
			return 1;
		}
		else if (key == special_nums_for_menu::NINE)

		{
			return 9;  
		}

	}
}