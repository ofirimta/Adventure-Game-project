#include "Files.h"
#include <sstream>

LevelData Files::loadLevel(int room)
{
    LevelData data;
    data.isValid = false;

    string filename = "adv-world_";
    if (room < 10)
        filename += "0";
    filename += std::to_string(room) + ".screen.txt";

    std::ifstream file(filename);
    if (!file.is_open())
    {
        return data;
    }

    data.isValid = true;
    string line;
    int row = 0;
    bool readingData = false;

    bool foundLegend = false;  

    while (std::getline(file, line))
    {
        if (line.empty()) continue;

        if (line.find("[DATA]") != string::npos)
        {
            readingData = true;
            continue;
        }

        if (!readingData)
        {
            for (size_t i = 0; i < line.length(); i++)
            {
                if (line[i] == 'L')
                {
                    if (!foundLegend)
                    {
                        data.legendLoc.setX((int)i);
                        data.legendLoc.setY(row);
                        foundLegend = true; 
                    }

                    line[i] = ' ';   
                }
            }

            data.currentroom.push_back(line);
            row++;
        }
        else
        {
            std::stringstream ss(line);
            string type;
            ss >> type;

            if (type == "PLAYER1")  
            {
                int x, y;
                ss >> x >> y;
                data.p1Start.setX(x);
                data.p1Start.setY(y);
            }
            else if (type == "PLAYER2") 
            {
                int x, y;
                ss >> x >> y;
                data.p2Start.setX(x);
                data.p2Start.setY(y);
            }
            else if (type == "DOOR") 
            {
                DoorData& d = data.doorData;

                ss >> d.id >> d.keysRequired >> d.switchesRequired >> d.keysNumber >> d.switchesNumber;
                ss >> d.switchCode;

                if (d.switchCode == "-")
                {
                    d.switchCode = "";
                }

                ss >> d.switch_x >> d.switch_y;

                data.hasDoor = true;
            }
            else if (type == "RIDDLE") 
            {
                RiddleData r;
                int x, y;
                ss >> x >> y;
                r.loc = Point(x, y, 0, 0, '?');
                data.riddles.push_back(r);
            }
            else if (type == "DARK")   
            {
                ss >> data.darkX1 >> data.darkY1 >> data.darkX2 >> data.darkY2;
                data.isDark = true;
            }
        }
    }

    file.close();
    return data;
}