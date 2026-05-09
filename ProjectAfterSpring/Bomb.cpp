#include "Bomb.h"
#include "Player.h"

void Bomb::activate(const Point& drop_location, int room)
{
    location.setX(drop_location.getX());
    location.setY(drop_location.getY());

    room_index = room;
    is_active = true;
    countdown = 5; 
    location.draw();
}

void Bomb::update(Player& p1, Player& p2) 
{
    if (!is_active) 
    {
        return;
    }

    if (countdown > 0) 
    {
        countdown--;
    }

    if (countdown == 0) 
    {
        explode(p1, p2); 
        is_active = false; 
    }
}

void Bomb::explode(Player& p1, Player& p2)
{
    location.draw(' '); 
    Point current_pos = location;
    current_pos.setChar(' ');
    s.setCharAt(current_pos, room_index);

    checkDamagePlayer(p1, room_index);
    checkDamagePlayer(p2, room_index);

    for (int y = -EXPLOSION_RADIUS; y <= EXPLOSION_RADIUS; y++) {
        for (int x = -EXPLOSION_RADIUS; x <= EXPLOSION_RADIUS; x++) {

            Point target_pos = location;
            target_pos.setX(location.getX() + x);
            target_pos.setY(location.getY() + y);

            if (target_pos.getX() < 0 || target_pos.getX() >= MAX_X ||
                target_pos.getY() < 0 || target_pos.getY() >= MAX_Y)
            {
                continue;
            }

            char char_at_target = s.getCharAt(target_pos, room_index);

            if (char_at_target == WALL_CHAR)
            {
                target_pos.setChar(' ');
                s.setCharAt(target_pos, room_index);
                target_pos.draw(' ');
            }


        }
    }

}

void Bomb::checkDamagePlayer(Player& p, int room)
{
    if (p.isAlive() && p.getCurrentRoomIndex() == room)
    {
        int dx = abs(p.getLocation().getX() - location.getX());
        int dy = abs(p.getLocation().getY() - location.getY());

        if (dx <= 3 && dy <= 3)
        {
            p.hitByBomb();
            s.setHealthAt(p, room); 
        }
    }

}