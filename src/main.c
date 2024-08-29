#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "player.h"
#include "enemy.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define MAX_ENEMIES 10

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Initialize SDL_image
    if (IMG_Init(IMG_INIT_PNG) == -1) {
        printf("SDL_image could not initialize! SDL_Error: %s\n", IMG_GetError());
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("Space Invaders", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Create a renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // Load enemy image
    SDL_Surface* enemyImage = IMG_Load("../assets/enemy.png");
    if (enemyImage == NULL) {
        printf("Failed to load enemy image: %s\n", IMG_GetError());
        return 1;
    }

    // Create texture from enemy image
    SDL_Texture* enemyTexture = SDL_CreateTextureFromSurface(renderer, enemyImage);
    SDL_FreeSurface(enemyImage);
    if (enemyTexture == NULL) {
        printf("Failed to create enemy texture: %s\n", SDL_GetError());
        return 1;
    }

    // Load player image
    SDL_Surface* playerImage = IMG_Load("../assets/player.png");
    if (playerImage == NULL) {
        printf("Failed to load player image: %s\n", IMG_GetError());
        return 1;
    }

    // Create texture from player image
    SDL_Texture* playerTexture = SDL_CreateTextureFromSurface(renderer, playerImage);
    SDL_FreeSurface(playerImage);
    if (playerTexture == NULL) {
        printf("Failed to create player texture: %s\n", SDL_GetError());
        return 1;
    }

    // Create enemies
    Enemy enemies[MAX_ENEMIES];
    spawnEnemies(enemies, MAX_ENEMIES);

    // Initialize player
    Player player;
    initializePlayer(&player);

    // Game loop
    bool quit = false;
    while (!quit) {
        // Handle player input
        handlePlayerInput(&player);

        // Update enemies
        for (int i = 0; i < MAX_ENEMIES; i++) {
            enemies[i].rect.y += enemies[i].speed;
            if (enemies[i].rect.y > SCREEN_HEIGHT) {
                // Enemy has reached the bottom, handle it
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Render enemies
        for (int i = 0; i < MAX_ENEMIES; i++) {
            SDL_RenderCopy(renderer, enemyTexture, NULL, &enemies[i].rect);
        }

        // Render player
        SDL_RenderCopy(renderer, playerTexture, NULL, &player.rect);

        // Update the screen
        SDL_RenderPresent(renderer);
    }

    // Clean up
    SDL_DestroyTexture(playerTexture);
    SDL_DestroyTexture(enemyTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}