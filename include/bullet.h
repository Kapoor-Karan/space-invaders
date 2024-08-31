#ifndef BULLET_H
#define BULLET_H

#include <SDL2/SDL.h>  // Assuming you need SDL types here
#include "enemy.h"     // Include if you need Enemy type

// Define the Bullet structure
typedef struct Bullet {
    SDL_Rect rect;  // Rectangle for position and size
    int speed;      // Speed of the bullet
} Bullet;

// Function declarations
void spawnBullet(Bullet*** bullets, int* numBullets, int playerX);
void updateBullets(Bullet** bullets, int* numBullets, Enemy* enemies, int numEnemies);
void renderBullets(SDL_Renderer* renderer, Bullet** bullets, int numBullets);

#endif // BULLET_H
