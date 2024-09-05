#include "game.h"
#include <stdlib.h>

// Game constructor function
struct Game *gameConstructor()
{
    struct Game *g = (struct Game *)malloc(sizeof(struct Game));
    if (g == NULL) {
        return NULL;  // Return NULL if allocation fails
    }

    g->s = constructorFunction();
    if (g->s == NULL) {
        free(g);
        return NULL;  // Return NULL if spaceship constructor fails
    }

    g->alienCount = 3 * 4;
    g->aliens = CreateAliens();
    if (g->aliens == NULL) {
        destructFunction(g->s);  // Clean up if aliens creation fails
        free(g);
        return NULL;
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
    if (g->s != NULL) {
        Draw(g->s);
    }

    if (g->s != NULL) {
        for (int i = 0; i < g->s->laserCount; i++) {
            DrawLaser(&g->s->lasers[i]);  // Draw each laser
        }
    }

    if (g->aliens != NULL) {
        for (int i = 0; i < g->alienCount; i++) {
            DrawAlien(&g->aliens[i]);  // Call the DrawAlien function for each alien
        }
    }
}


// Game destructor functiom
void gameDestructor(struct Game* g) {
    if (g != NULL) {
        if (g->s != NULL) {
            destructFunction(g->s);
        }
        
        if (g->aliens != NULL) {
            for (int i = 0; i < g->alienCount; i++) {
                UnloadTexture(g->aliens[i].image);  // Unload alien textures if applicable
            }
            free(g->aliens);
        }

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

struct Alien* CreateAliens() {
    int rows = 3;
    int columns = 4;
    // Total number of aliens
    int totalAliens = rows * columns;

    // Dynamically allocate memory for aliens
    struct Alien* aliens = (struct Alien*)malloc((totalAliens) * sizeof(struct Alien));

    if (aliens == NULL) {
        return NULL;  // Memory allocation failed
    }

    int index = 0;

    for (int row = 0; row < rows; row++) {
        for (int column = 0; column < columns; column++) {

            // Set alien position
            float x = 75 + column * 55;
            float y = 110 + row * 55;

            // Initialize the alien
            aliens[index].position = (Vector2){x, y};
            aliens[index].image = LoadTexture("../assets/enemy.png");
            index++;
        }
    }

    return aliens;  // Return the pointer to the array of aliens
}
