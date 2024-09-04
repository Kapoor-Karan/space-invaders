#include "spaceship.h"
#include <stdlib.h>

// spaceship constructor function
struct spaceship* constructorFunction()
{
    struct spaceship* s = (struct spaceship*) malloc(sizeof(struct spaceship));  // Allocate memory for the struct itself
    if (s != NULL) {
        s->image = LoadTexture("../assets/player.png");
        s->position.x = (GetScreenWidth() - s->image.width) / 2;
        s->position.y = (GetScreenHeight() - s->image.height);
    }
    return s;
}

// spaceship destructor function
void destructFunction(struct spaceship* s)
{
    if (s != NULL) {
        UnloadTexture(s->image);
        free(s);  
    }
}

// Method to draw spaceship on screen
void Draw(struct spaceship* s)
{
    DrawTextureV(s->image, s->position, WHITE);
}

// Method to move the spaceship to left
void moveLeft(struct spaceship* s)
{
    s->position.x -= 7;

    if(s->position.x < 0) {
        s->position.x = 0;
    }
}

// Method to move the spaceship to right
void moveRight(struct spaceship* s)
{
    s->position.x += 7;

    if(s->position.x > GetScreenWidth() - s->image.width) {
        s->position.x = GetScreenWidth() - s->image.width;
    }
}
