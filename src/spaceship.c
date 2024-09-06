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

        // Check if laser array memory allocation failed
        if (s->lasers == NULL) {
            free(s);  // Free spaceship if laser allocation failed
            return NULL;
        }
    }
    return s;
}

// spaceship destructor function
void destructFunction(struct spaceship* s)
{
    if (s != NULL) {
        UnloadTexture(s->image);

        // Free the laser array if it exists
        if (s->lasers != NULL) {
            free(s->lasers);
        }

        // Free the spaceship itself
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
    double currentTime = GetTime();
    
    // Check if enough time has passed since the last shot
    if (currentTime - s->lastFireTime >= 0.35) {
        // Check if laser array needs to be expanded
        if (s->laserCount >= s->laserCapacity) {
            s->laserCapacity *= 2;
            s->lasers = (struct Laser*)realloc(s->lasers, s->laserCapacity * sizeof(struct Laser));

            // Check if realloc failed
            if (s->lasers == NULL) {
                return;  // Don't proceed if realloc fails
            }
        }

        // Add the new laser
        struct Laser newLaser;
        newLaser.position.x = s->position.x + s->image.width / 2 - 2;
        newLaser.position.y = s->position.y;
        newLaser.speed = -6.0f;
        newLaser.active = true;  // Mark the laser as active

        // Assign the new laser to the array
        s->lasers[s->laserCount] = newLaser;
        s->laserCount++;

        // Update last fire time
        s->lastFireTime = currentTime;
    }
}

Rectangle getRectSpaceship(struct spaceship* s) {
    Rectangle temp = {s->position.x, s->position.y, s->image.width, s->image.height};
    return temp;
}
