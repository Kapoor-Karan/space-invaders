#pragma once
#include <raylib.h>
#include <stdbool.h>

struct Laser
{
    Vector2 position;
    int speed;
    bool active;
};

struct Laser* laserConstructor(Vector2 position, int speed);
void updateLaser(struct Laser* l);
void DrawLaser(struct Laser* l);