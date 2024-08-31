#include "bullet.h"
#include "constants.h"
#include <stdlib.h>  // For malloc, free

// Function to spawn a bullet
void spawnBullet(Bullet*** bullets, int* numBullets, int playerX) {
    Bullet* newBullet = (Bullet*)malloc(sizeof(Bullet));
    if (!newBullet) {
        printf("Failed to allocate memory for new bullet.\n");
        return;
    }

    newBullet->rect.x = playerX;
    newBullet->rect.y = SCREEN_HEIGHT - 30;  // Example value for start position
    newBullet->rect.w = 5;   // Example width
    newBullet->rect.h = 10;  // Example height
    newBullet->speed = 5;

    *bullets = realloc(*bullets, (*numBullets + 1) * sizeof(Bullet*));
    (*bullets)[*numBullets] = newBullet;
    (*numBullets)++;
}

// Function to update bullets and handle collision
void updateBullets(Bullet** bullets, int* numBullets, Enemy* enemies, int numEnemies) {
    for (int i = 0; i < *numBullets; i++) {
        bullets[i]->rect.y -= bullets[i]->speed;

        // Check for collisions with enemies here...

        // Remove bullets if they go out of screen
        if (bullets[i]->rect.y < 0) {
            free(bullets[i]);
            bullets[i] = bullets[*numBullets - 1];
            (*numBullets)--;
            i--;  // Adjust index to check the swapped bullet
        }
    }
}

// Function to render bullets
void renderBullets(SDL_Renderer* renderer, Bullet** bullets, int numBullets) {
    for (int i = 0; i < numBullets; i++) {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // White color
        SDL_RenderFillRect(renderer, &bullets[i]->rect);
    }
}
