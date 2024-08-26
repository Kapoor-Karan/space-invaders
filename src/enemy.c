#include <SDL2/SDL.h>
#include "enemy.h"
#include "constants.h"

#define ENEMY_WIDTH 30
#define ENEMY_HEIGHT 30

void spawnEnemies(Enemy* enemies, int numEnemies) {
    for (int i = 0; i < numEnemies; i++) {
        enemies[i].rect.x = rand() % (SCREEN_WIDTH - ENEMY_WIDTH);
        enemies[i].rect.y = 0;
        enemies[i].rect.w = ENEMY_WIDTH;
        enemies[i].rect.h = ENEMY_HEIGHT;
        enemies[i].health = 1;
        enemies[i].speed = 2;
    }
}