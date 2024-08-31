#include "bullet.h"
#include "constants.h"

void spawnBullet(Bullet*** bullets, int* numBullets, int playerX) {
    Bullet* newBullet = (Bullet*)malloc(sizeof(Bullet));
    newBullet->rect.x = playerX + (PLAYER_WIDTH / 2) - (BULLET_WIDTH / 2);
    newBullet->rect.y = SCREEN_HEIGHT - PLAYER_HEIGHT;
    newBullet->rect.w = BULLET_WIDTH;
    newBullet->rect.h = BULLET_HEIGHT;
    newBullet->speed = 5;

    (*bullets)[*numBullets] = newBullet;
    (*numBullets)++;
}

void updateBullets(Bullet** bullets, int* numBullets, Enemy* enemies, int numEnemies) {
    for (int i = 0; i < *numBullets; i++) {
        bullets[i]->rect.y -= bullets[i]->speed;

        // Check for collisions with enemies
        for (int j = 0; j < numEnemies; j++) {
            if (SDL_HasIntersection(&bullets[i]->rect, &enemies[j].rect)) {
                // Bullet hit an enemy
                enemies[j].health--;
                if (enemies[j].health <= 0) {
                    // Enemy is destroyed
                }
                bullets[i]->rect.y = -1; // Mark bullet as destroyed
                break;
            }
        }

        // Remove destroyed bullets
        if (bullets[i]->rect.y < 0) {
            free(bullets[i]);
            bullets[i] = bullets[*numBullets - 1];
            (*numBullets)--;
            i--; // Adjust index to check the swapped bullet
        }
    }
}

void renderBullets(SDL_Renderer* renderer, Bullet** bullets, int numBullets) {
    for (int i = 0; i < numBullets; i++) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &bullets[i]->rect);
    }
}
