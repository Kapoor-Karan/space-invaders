#pragma once
#include "spaceship.h"

// Game structure defined
struct Game {
    struct spaceship* s;
};

// Game methods 
struct Game* gameConstructor();
void HandleInput(struct Game* g);
void gameDestructor(struct Game* g);
void DrawGame(struct Game* g);
void UpdateGame(struct Game* g);
void DeleteInactiveLasers(struct Game* g);
