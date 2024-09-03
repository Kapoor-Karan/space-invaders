#include "laser.h"
#include <stdlib.h>

struct Laser *laserConstructor(Vector2 position, int speed)
{
    struct Laser *l = (struct Laser*) (malloc(sizeof(struct Laser)));
    l->position = position;
    l->speed = speed;
    l->active = true;
    return l;
}

void updateLaser(struct Laser *l)
{
    l->position.y += l->speed;
    if(l->active) {
        if(l->position.y > GetScreenHeight() || l->position.y < 0) {
            l->active = false;
        }
    }
}

void DrawLaser(struct Laser *l)
{
    Color color = {243,216,63,255};
    if(l->active)
        DrawRectangle(l->position.x, l->position.y, 4, 15, color);
}
