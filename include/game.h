#pragma once
#include "spaceship.h"

struct Game {
    struct spaceship* s;
};

struct Game* gameConstructor();
void HandleInput(struct Game* g);
void gameDestructor(struct Game* g);
void DrawGame(struct Game* g);
