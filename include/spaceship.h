#pragma onve
#include <raylib.h>

struct spaceship
{
    Texture2D image;
    Vector2 position;
};

spaceship* constructorFunction();
void destructorFunction(spaceship s);
void Draw(spaceship s);
void moveLeft(spaceship s);
void moveRight(spaceship s);
void fireLaser(spaceship s);