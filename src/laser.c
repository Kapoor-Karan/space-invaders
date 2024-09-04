#include "laser.h"
#include <stdlib.h>

// Laser constructor function
struct Laser *laserConstructor(Vector2 position, int speed)
{
    struct Laser *l = (struct Laser*) (malloc(sizeof(struct Laser)));
    l->position = position;
    l->speed = speed;
    l->active = true;
    return l;
}

// Method to update laser's speed and it's active status
void updateLaser(struct Laser *l)
{
    l->position.y += l->speed;
    if(l->active) {
        if(l->position.y > GetScreenHeight() || l->position.y < 0) {
            l->active = false;
        }
    }
}

// Method to draw laser on screen
void DrawLaser(struct Laser *l)
{
    Color color = {243,216,63,255};
    if(l->active)
        DrawRectangle(l->position.x, l->position.y, 4, 15, color);
}
