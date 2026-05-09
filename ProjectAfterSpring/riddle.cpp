#include "riddle.h"
#include "Player.h"
using std::getline;
using std::to_string;

const char* riddle::feedback_screens[3][MAX_Y] =
{
    //   01234567890123456789012345678901234567890123456789012345678901234567890123456789
        "                                                                                ", // 0 
        "                                                                                ", // 1  
        "                                                                                ", // 2  
        "                                                                                ", // 3
        "                                                                                ", // 4
        "                                                                                ", // 5   
        "                                                                                ", // 6
        "                                                                                ", // 7
        "                                                                                ", // 8 
        "                  That is the correct answer!                                   ", // 9
        "                                                                                ", // 10
        "                  you may proceed.                                              ", // 11
        "                                                                                ", // 12
        "                                                                                ", // 13
        "                                                                                ", // 14
        "              ////Press 3 on the keyboard to continue///                        ", // 15
        "                                                                                ", // 16
        "                                                                                ", // 17  
        "                                                                                ", // 18
        "                                                                                ", // 19  
        "                                                                                ", // 20
        "                                                                                ", // 21
        "                                                                                ", // 22
        "                                                                                ", // 23
        "                                                                                "  // 24
    ,
        "                                                                                ", // 0 
        "                                                                                ", // 1  
        "                                                                                ", // 2  
        "                                                                                ", // 3
        "                                                                                ", // 4
        "                                                                                ", // 5   
        "                                                                                ", // 6
        "                                                                                ", // 7
        "                                                                                ", // 8 
        "                  That is wrong answer.                                         ", // 9
        "                                                                                ", // 10
        "                ////Press 4 on the keyboard to try again///                     ", // 11
        "                                                                                ", // 12
        "               ////Press 3 on the keyboard to return to the game///             ", // 13 
        "                                                                                ", // 14
        "                                                                                ", // 15
        "                                                                                ", // 16
        "                                                                                ", // 17  
        "                                                                                ", // 18
        "                                                                                ", // 19  
        "                                                                                ", // 20
        "                                                                                ", // 21
        "                                                                                ", // 22
        "                                                                                ", // 23
        "                                                                                "  // 24
    ,
        "                                                                                ", // 0 
        "                                                                                ", // 1  
        "                                                                                ", // 2  
        "                                                                                ", // 3
        "                                                                                ", // 4
        "                                                                                ", // 5   
        "       Illegal input or empty input.                                            ", // 6
        "                                                                                ", // 7
        "       Your answer must be a numbers. Please try again.                         ", // 8 
        "                                                                                ", // 9
        "       ////Press 4 on the keyboard to try again///                              ", // 10
        "                                                                                ", // 11
        "                                                                                ", // 12
        "                                                                                ", // 13 
        "                                                                                ", // 14
        "                                                                                ", // 15
        "                                                                                ", // 16
        "                                                                                ", // 17  
        "                                                                                ", // 18
        "                                                                                ", // 19  
        "                                                                                ", // 20
        "                                                                                ", // 21
        "                                                                                ", // 22
        "                                                                                ", // 23
        "                                                                                "  // 24
};

riddle::riddle(Screen& screen) : my_screen(screen)
{
    loadRiddlesFromFile("riddles.txt");
}
void riddle::loadRiddlesFromFile(const string& filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        return;
    }

    string line;
    my_riddle temp_riddle = { 0 };
    vector<string> temp_screen;

    bool reading_screen = false;

    while (getline(file, line))
    {
        if (line.find("#RIDDLE_START") != string::npos)
        {
            temp_screen.clear();
            temp_riddle = { 0,0,0,0,0, false };
            reading_screen = false;
            continue;
        }

        if (line.find("#RIDDLE_END") != string::npos)
        {
            my_arr.push_back(temp_riddle);
            riddles_screens.push_back(temp_screen);
            reading_screen = false;
            continue;
        }

        if (line.find("#SCREEN_DATA") != string::npos)
        {
            reading_screen = true;
            continue;
        }

        if (line.find("#LOGIC_DATA") != string::npos)
        {
            reading_screen = false;
            continue;
        }

        if (reading_screen)
        {
            temp_screen.push_back(line);
        }
        else
        {
            try {
                if (line.find("INDEX:") != string::npos)
                {
                    temp_riddle.index_of_my_arr = stoi(line.substr(line.find(":") + 1));
                }
                else if (line.find("ROOM:") != string::npos)
                {
                    temp_riddle.room_of_riddle = stoi(line.substr(line.find(":") + 1));
                }
                else if (line.find("X:") != string::npos)
                {
                    temp_riddle.x_of_riddle = stoi(line.substr(line.find(":") + 1));
                }
                else if (line.find("Y:") != string::npos)
                {
                    temp_riddle.y_of_riddle = stoi(line.substr(line.find(":") + 1));
                }
                else if (line.find("ANSWER:") != string::npos)
                {
                    temp_riddle.correct_ansewr = stoi(line.substr(line.find(":") + 1));
                }
            }
            catch (...)
            {
                std::cout << "WARNING: Failed to parse number in line: " << line << std::endl;
            }
        }
    }

    file.close();
}

riddle::my_riddle riddle::correctRiddle(Point& p, int my_room)
{
    for (size_t i = 0; i < my_arr.size(); i++)
    {
        if ((p.getX() == my_arr[i].x_of_riddle) && (p.getY() == my_arr[i].y_of_riddle) && (my_room == my_arr[i].room_of_riddle))
        {
            return my_arr[i]; 
        }
    }

    if (!my_arr.empty())  
    {
        int randomIndex = rand() % my_arr.size();  

        riddle::my_riddle randomRiddle = my_arr[randomIndex]; 

        randomRiddle.x_of_riddle = p.getX();       
        randomRiddle.y_of_riddle = p.getY();
        randomRiddle.room_of_riddle = my_room;

        return randomRiddle;
    }

    return riddle::my_riddle{ -1, -1, -1, -1, -1, false };  
}

void riddle::draw_riddle(int room) const {    

    cls();
    gotoxy(0, 0);

    if (room >= 0 && room < riddles_screens.size())
    {
        if (!riddles_screens[room].empty())
        {
            for (size_t i = 0; i < riddles_screens[room].size() - 1; ++i)
            {
                cout << riddles_screens[room][i] << endl;
            }
            cout << riddles_screens[room].back();
        }
    }
    cout.flush();
}

void riddle::draw_feedback(int room) const {    
    cls();
    gotoxy(0, 0);

    for (size_t i = 0; i < MAX_Y - 1; ++i)
    {
        cout << feedback_screens[room][i] << endl;
    }
    cout << feedback_screens[room][MAX_Y - 1];
    cout.flush();
}

void riddle::run(Point& p, int my_room)
{
    last_answer_is_correct = false;

    int again = 4;   

    my_riddle current_riddle;
    int my_index;

    current_riddle = correctRiddle(p, my_room);
    if (current_riddle.index_of_my_arr == -1) return;

    const string correct_answer_str = std::to_string(current_riddle.correct_ansewr);  
    my_index = current_riddle.index_of_my_arr;

    while (again == 4)
    {
        bool illigal_input = 0; 
        draw_riddle(my_index);  
        string user_input;  
        getline(cin, user_input);
        if (user_input.length() == 0) 
        {
            illigal_input = 1;
        }
        for (size_t i = 0; i < user_input.length(); i++)  
        {
            if (isdigit(user_input[i]) == 0) 
            {
                illigal_input = 1;
                break;   
            }
        }
        if (illigal_input == 1)
        {
            draw_feedback(2); 
            char key = (char)_getch();  

            while (key != (char)special_nums_for_riddle::FOUR) 
            {
                key = (char)_getch();
            }
            continue;  
        }

        if (user_input == correct_answer_str)
        {
            last_answer_is_correct = true;
            draw_feedback(0);

            char key = (char)_getch();           

            while (key != (char)special_nums_for_riddle::Three) 
            {
                key = (char)_getch(); 
            }
            p.setChar(' ');           
            my_screen.setCharAt(p, my_room);  
            my_screen.draw(my_room);  
            again = 3;
        }
        else
        {
            last_answer_is_correct = false;
            draw_feedback(1);

            char key = (char)_getch();           

            while ((key != (char)special_nums_for_riddle::Three) && (key != (char)special_nums_for_riddle::FOUR)) 
            {
                key = (char)_getch(); 
            }
            if (key == (char)special_nums_for_riddle::Three)
            {
                my_screen.draw(my_room);  
                again = 3;
            }
            else
            {
                continue;  
            }
        }
    }
}