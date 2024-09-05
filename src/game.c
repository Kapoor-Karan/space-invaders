#include "game.h"
#include <stdlib.h>

// Game constructor function
struct Game *gameConstructor()
{
    struct Game *g = (struct Game *)malloc(sizeof(struct Game));
    if (g != NULL) {
        g->s = constructorFunction();  
    }
    return g;
}

// Function to handle user inputs
void HandleInput(struct Game *g)
{
    if (IsKeyDown(KEY_LEFT)) {
        moveLeft(g->s);
    } else if (IsKeyDown(KEY_RIGHT)) {
        moveRight(g->s);
    } else if (IsKeyDown(KEY_SPACE)) {
        fireLaser(g->s);
    }
}

// Drawing Game on screen
void DrawGame(struct Game *g)
{
    Draw(g->s);

    for (int i = 0; i < g->s->laserCount; i++) {
        DrawLaser(&g->s->lasers[i]);  // Draw each laser
    }
}

// Game destructor functiom
void gameDestructor(struct Game* g) {
    if (g != NULL) {
        destructFunction(g->s);  
        free(g);  
    }
}

void UpdateGame(struct Game* g) {
    for (int i = 0; i < g->s->laserCount; i++) {
        updateLaser(&g->s->lasers[i]);  // Draw each laser
    }
}

void DeleteInactiveLasers(struct Game* g) {
    int newLaserCount = 0;  // Count of active lasers
    for (int i = 0; i < g->s->laserCount; i++) {
        if (g->s->lasers[i].active) {
            // Keep active lasers by shifting them to the front
            g->s->lasers[newLaserCount] = g->s->lasers[i];
            newLaserCount++;
        }
    }
    // Update the count of lasers after removing inactive ones
    g->s->laserCount = newLaserCount;
}
