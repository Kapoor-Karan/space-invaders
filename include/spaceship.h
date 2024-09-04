#pragma once
#include <raylib.h>
#include "laser.h"

// spaceship structure
struct spaceship {
    Texture2D image;
    Vector2 position;
};

// spaceship methods
struct spaceship* constructorFunction();
void destructFunction(struct spaceship* s);
void Draw(struct spaceship* s);
void moveLeft(struct spaceship* s);
void moveRight(struct spaceship* s);
void fireLaser(struct spaceship* s);  
