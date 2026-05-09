#include "Obstacle.h"

Obstacle::Obstacle(Screen& screen, const Point& startPos, int room, bool visited[MAX_Y][MAX_X])
    : my_screen(screen)
{
    findAllPoints(startPos, room, visited);
}


void Obstacle::findAllPoints(const Point& p, int room, bool visited[MAX_Y][MAX_X])
{
    std::vector<Point> openList; 
    openList.push_back(p);

    while (!openList.empty())
    {
        Point p = openList.back();
        openList.pop_back();

        int x = p.getX();
        int y = p.getY();

        if (x < 0 || x >= MAX_X || y < 0 || y >= MAX_Y) 
            continue;

        if (visited[y][x]) 
            continue;

        char ch = my_screen.getCharAt(p, room);
        if (ch != OBSTACLE_CHAR)
            continue;

        visited[y][x] = true;

        p.setChar(OBSTACLE_CHAR);
        body.push_back(p);
        openList.push_back(Point(x + 1, y, 0, 0, ' ')); 
        openList.push_back(Point(x - 1, y, 0, 0, ' ')); 
        openList.push_back(Point(x, y + 1, 0, 0, ' ')); 
        openList.push_back(Point(x, y - 1, 0, 0, ' ')); 
    }
}

bool Obstacle::isPartOfObstacle(const Point& targetP) const
{
    for (const Point& p : body)
    {
        if (p.getX() == targetP.getX() && p.getY() == targetP.getY())
        {
            return true;
        }
    }
    return false;
}

void Obstacle::eraseFromScreen(int room)
{
    for (const Point& p : body)
    {
        Point toDelete = p;
        toDelete.setChar(' ');
        my_screen.setCharAt(toDelete, room);
        toDelete.draw(' ');
    }
}

void Obstacle::drawToScreen(int room)
{
    for (const Point& p : body)
    {
        my_screen.setCharAt(p, room);
        p.draw();
    }
}

bool Obstacle::push(Direction dir, int force, int room)
{
    if (force < getSize()) 
        return false;

    int dx = 0, dy = 0;

    switch (dir) 
    {
    case Direction::UP:
        dy = -1;
        break;
    case Direction::DOWN:
        dy = 1;
        break;
    case Direction::LEFT:
        dx = -1;
        break;
    case Direction::RIGHT:
        dx = 1;
        break;
    default:
        return false;
    }

    if (isMovementPossible(dir, room, dx, dy) == false) 
    {
        return false;
    }
    eraseFromScreen(room); 
    for (Point& p : body) 
    {
        p.setX(p.getX() + dx);
        p.setY(p.getY() + dy);
    }
    drawToScreen(room); 

    return true;
}

bool Obstacle::isMovementPossible(Direction dir, int room, int dx, int dy)
{
    for (const Point& p : body) 
    {

        Point nextPos(p.getX() + dx, p.getY() + dy, 0, 0, ' '); 

        if (nextPos.getX() < 0 || nextPos.getX() >= MAX_X || nextPos.getY() < 0 || nextPos.getY() >= MAX_Y) 
            return false;

        char charAtNewPos = my_screen.getCharAt(nextPos, room);

        if (charAtNewPos != ' ' && !isPartOfObstacle(nextPos)) 
        {
            return false;
        }
    }
    return true;
}