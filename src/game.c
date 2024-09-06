#include "game.h"
#include <stdlib.h>
#include <stdio.h>

// Game constructor function
struct Game *gameConstructor()
{
    struct Game* g = InitGame();
    return g; 
}


// Function to handle user inputs
void HandleInput(struct Game *g)
{
    if(g->run) {
        if (IsKeyDown(KEY_LEFT)) {
            moveLeft(g->s);
        } else if (IsKeyDown(KEY_RIGHT)) {
            moveRight(g->s);
        } else if (IsKeyDown(KEY_SPACE)) {
            fireLaser(g->s);
        }
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

    if(g->run){
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
        CheckCollisions(g);
        // Remove inactive spaceship and alien lasers
        DeleteInactiveLasers(g);   // Assuming this function now handles both spaceship and alien lasers
        if (g->alienCount == 0) {
            // Respawn aliens
            ResetAliens(g);
        }
    } 
    // else if(IsKeyDown(KEY_ENTER)) {
        // Reset(g);
        // g = InitGame();
    // }
}


void DeleteInactiveLasers(struct Game* g) {
    // Handle spaceship lasers
    int newLaserCount = 0;  // Count of active spaceship lasers
    for (int i = 0; i < g->s->laserCount; i++) {
        if (g->s->lasers[i].active) {
            // Keep active spaceship lasers by shifting them to the front
            g->s->lasers[newLaserCount] = g->s->lasers[i];
            newLaserCount++;
        }
    }
    // Update the count of spaceship lasers after removing inactive ones
    g->s->laserCount = newLaserCount;

    // Handle alien lasers
    int newAlienLaserCount = 0;  // Count of active alien lasers
    for (int i = 0; i < g->alienLaserCount; i++) {
        if (g->alienLasers[i].active) {
            // Keep active alien lasers by shifting them to the front
            g->alienLasers[newAlienLaserCount] = g->alienLasers[i];
            newAlienLaserCount++;
        }
    }
    // Update the count of alien lasers after removing inactive ones
    g->alienLaserCount = newAlienLaserCount;
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


void CheckCollisions(struct Game* g) {
    // Checking for spaceship lasers
    for (int i = 0; i < g->s->laserCount; i++) {
        struct Laser* laser = &g->s->lasers[i];

        // Check collision with aliens
        for (int j = 0; j < g->alienCount; j++) {
            struct Alien* alien = &g->aliens[j];
            Rectangle r1 = {alien->position.x, alien->position.y, alien->image.width, alien->image.height};
            Rectangle r2 = {laser->position.x, laser->position.y, 4, 15};
            if (CheckCollisionRecs(r1, r2)) {

                // Remove the alien
                for (int k = j; k < g->alienCount - 1; k++) {
                    g->aliens[k] = g->aliens[k + 1];  // Shift remaining aliens
                }
                g->alienCount--;  // Decrease the alien count
                g->score += 1;
                laser->active = false;  // Mark laser as inactive
                break;  // Exit the loop since the alien is removed
            }
        }
    }
    for (int i = 0; i < g->alienLaserCount; i++) {
        struct Laser* laser = &g->alienLasers[i];
        // Check collision with spaceship
        if (CheckCollisionRecs(getRectLaser(laser), getRectSpaceship(g->s))) {
            g->lives--;
            laser->active = false;
            printf("Lives Left : %d\n", g->lives);
            if(g->lives == 0) {
                GameOver(g); 
            }
        }
    }

    // spaceship and alien collision
    for (int i = 0; i < g->alienCount; i++) {
        struct Alien* alien = &g->aliens[i];
        if (CheckCollisionRecs(getRectAlien(alien), getRectSpaceship(g->s))) {

            GameOver(g);
        }
    }
}

void GameOver(struct Game* g) {
    g->run = false;
    printf("\n Your score was : %d ", g->score);
    printf("\n");
}

struct Game* InitGame()
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
    g->score = 0;
    g->run = true;
    g->alienCount = 5 * 10;
    g->aliensDirection = 1;
    g->lives = 3;
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

// void Reset(struct Game* g) {
//     ResetSpaceship(g->s);
//     g->alienLaserCount = 0;
//     g->alienCount = 0;
// }

void ResetAliens(struct Game* g)
{
    // Recreate the aliens with the same texture
    g->alienCount = 5 * 10;  // Reset alien count
    free(g->aliens);  // Free the previous alien memory
    g->aliens = CreateAliens(g->AlienImage);  // Respawn aliens from the starting point
}
