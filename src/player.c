#include "player.h"
#include "constants.h"
#include <SDL2/SDL.h>

#define PLAYER_WIDTH 50
#define PLAYER_HEIGHT 50

void initializePlayer(Player* player) {
    player->rect.x = (SCREEN_WIDTH - PLAYER_WIDTH) / 2;
    player->rect.y = SCREEN_HEIGHT - PLAYER_HEIGHT;
    player->rect.w = PLAYER_WIDTH;
    player->rect.h = PLAYER_HEIGHT;
    player->speed = 15;
}

void handlePlayerInput(Player* player) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            exit(0); // Exit the game
        } else if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                    player->rect.x -= player->speed;
                    break;
                case SDLK_RIGHT:
                    player->rect.x += player->speed;
                    break;
                case SDLK_SPACE:
                    // Handle shooting
                    break;
            }
        }
    }
}

void renderPlayer(SDL_Renderer* renderer, Player* player) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &player->rect);
}