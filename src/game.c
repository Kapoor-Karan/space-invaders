#include "game.h"
#include <stdlib.h>
#include <stdio.h>

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
    g->AlienImage = LoadTexture("../assets/enemy.png");
    if (g->AlienImage.id == 0) {
        // Error loading texture
        printf("Failed to load alien texture\n");
    }
    g->alienCount = 5 * 10;
    g->aliensDirection = 1;
    g->alienLaserCapacity = 10;
    g->alienLasers = (struct Laser*)malloc(g->alienLaserCapacity * sizeof(struct Laser));
    g->alienLaserCount = 0;
    g->timeLastAlienFired = 0.0;
    g->alienLaserShootInterval = 0.5;
    g->aliens = CreateAliens(g->AlienImage);
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
    // Draw the spaceship and its lasers if the spaceship exists
    if (g->s != NULL) {
        Draw(g->s);  // Draw the spaceship

        for (int i = 0; i < g->s->laserCount; i++) {
            DrawLaser(&g->s->lasers[i]);  // Draw each spaceship laser
        }
    }

    // Draw aliens if they exist
    if (g->aliens != NULL) {
        for (int i = 0; i < g->alienCount; i++) {
            DrawAlien(&g->aliens[i]);  // Draw each alien
        }
    }

    // Draw alien lasers
    for (int i = 0; i < g->alienLaserCount; i++) {
        DrawLaser(&g->alienLasers[i]);  // Draw each alien laser
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
    // Update spaceship lasers
    for (int i = 0; i < g->s->laserCount; i++) {
        updateLaser(&g->s->lasers[i]);
    }

    // Move aliens and handle alien laser shooting
    MoveAliens(g);
    AlienShootLaser(g);

    // Update alien lasers
    for (int i = 0; i < g->alienLaserCount; i++) {
        updateLaser(&g->alienLasers[i]);
    }

    // Remove inactive spaceship and alien lasers
    DeleteInactiveLasers(g);   // Assuming this function now handles both spaceship and alien lasers
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


struct Alien* CreateAliens(Texture2D texture) {
    int rows = 5;
    int columns = 10;
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
            float x = 75 + (column * 55);
            float y = 110 + (row * 55);

            // Initialize the alien
            aliens[index].position = (Vector2){x, y};
            aliens[index].image = texture;
            index++;
        }
    }

    return aliens;  // Return the pointer to the array of aliens
}

void MoveAliens(struct Game* g) {
    for (int i = 0; i < g->alienCount; i++) {
        if((g->aliens[i].position.x + g->AlienImage.width) > GetScreenWidth()) {
            g->aliensDirection = -1;
            MoveDownAliens(g,4);
        } else if(g->aliens[i].position.x < 0) {
            g->aliensDirection = 1;
            MoveDownAliens(g,4);
        }
        UpdateAlien(&g->aliens[i], g->aliensDirection);
    }
}

void MoveDownAliens(struct Game *g, int distance)
{
    for (int i = 0; i < g->alienCount; i++) {
        g->aliens[i].position.y += distance;
    }
}

void AlienShootLaser(struct Game *g)
{
    double currentTime = GetTime();
        if(currentTime - g->timeLastAlienFired >= g->alienLaserShootInterval && g->alienCount > 0) {
        int randomIndex = GetRandomValue(0, 49);
        struct Alien* alien = &g->aliens[randomIndex];
        struct Laser newLaser;
        newLaser.position.x = alien->position.x + alien->image.width / 2;
        newLaser.position.y = alien->position.y + alien->image.height;
        newLaser.speed = 6;
        newLaser.active = true;
        g->alienLasers[g->alienLaserCount++] = newLaser;
        if (g->alienLaserCount >= g->alienLaserCapacity) {
            g->alienLaserCapacity *= 2;
            g->alienLasers = (struct Laser*)realloc(g->alienLasers, g->alienLaserCapacity * sizeof(struct Laser));
        }
        g->timeLastAlienFired = currentTime;
    }
}
