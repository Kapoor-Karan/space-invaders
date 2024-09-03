#include "game.h"
#include <stdlib.h>

struct Game *gameConstructor()
{
    struct Game *g = (struct Game *)malloc(sizeof(struct Game));
    if (g != NULL) {
        g->s = constructorFunction();  
    }
    return g;
}

void HandleInput(struct Game *g)
{
    if (IsKeyDown(KEY_LEFT)) {
        moveLeft(g->s);
    } else if (IsKeyDown(KEY_RIGHT)) {
        moveRight(g->s);
    }
}

void DrawGame(struct Game *g)
{
    Draw(g->s);
}

void gameDestructor(struct Game* g) {
    if (g != NULL) {
        destructFunction(g->s);  
        free(g);  
    }
}
