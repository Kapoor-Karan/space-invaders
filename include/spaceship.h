#pragma onve
#include <raylib.h>

struct spaceship
{
    Texture2D image;
    Vector2 position;
};

struct spaceship* constructorFunction();
void destructorFunction(struct spaceship s);
void Draw(struct spaceship* s);
void moveLeft(struct spaceship* s);
void moveRight(struct spaceship* s);
void fireLaser(struct spaceship* s);