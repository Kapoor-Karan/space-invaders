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
        s->laserCapacity = 10;  // Initial capacity for 10 lasers
        s->laserCount = 0;
        s->lastFireTime = 0.0f;
        s->lasers = (struct Laser*)malloc(s->laserCapacity * sizeof(struct Laser));
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

void fireLaser(struct spaceship* s) {
    if (GetTime() - s->lastFireTime >= 0.35) {
        // Check if we need to expand the laser array
        if (s->laserCount >= s->laserCapacity) {
            s->laserCapacity *= 2;
            s->lasers = (struct Laser*)realloc(s->lasers, s->laserCapacity * sizeof(struct Laser));
        }

        // Add the new laser
        s->lasers[s->laserCount].position.x = s->position.x + s->image.width / 2 - 2;
        s->lasers[s->laserCount].position.y = s->position.y;
        s->lasers[s->laserCount].speed = -6.0f;
        s->laserCount++;

        s->lastFireTime = GetTime();
    }
}

