#ifndef ENEMY_H
#define ENEMY_H

typedef struct {
    SDL_Rect rect;
    int health;
    int speed;
} Enemy;

void spawnEnemies(Enemy* enemies, int numEnemies);

#endif