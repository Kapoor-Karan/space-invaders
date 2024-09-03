#pragma once
#include "spaceship.h"

struct Game
{
    struct spaceship* s;
};

struct Game* gameConstructor(struct Game g);
struct Game* HandleInput(struct Game g);
struct Game* gameDestructor(struct Game g);
void DrawGame(struct Game g);