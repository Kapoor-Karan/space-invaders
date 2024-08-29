#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL.h>

typedef struct {
    SDL_Rect rect;
    int speed;
} Player;

void initializePlayer(Player* player);
void handlePlayerInput(Player* player);
void renderPlayer(SDL_Renderer* renderer, Player* player);

#endif