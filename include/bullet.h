#ifndef BULLET_H
#define BULLET_H

#include <SDL2/SDL.h>
#include "enemy.h"

typedef struct {
    SDL_Rect rect;
    int speed;
} Bullet;

void spawnBullet(Bullet** bullets, int* numBullets, int playerX);
void updateBullets(Bullet* bullets, int* numBullets, Enemy* enemies, int numEnemies);
void renderBullets(SDL_Renderer* renderer, Bullet* bullets, int numBullets);

#endif