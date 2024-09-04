#include "game.h"
#include <stdlib.h>

// Game constructor function
struct Game *gameConstructor()
{
    struct Game *g = (struct Game *)malloc(sizeof(struct Game));
    if (g != NULL) {
        g->s = constructorFunction();  
    }
    return g;
}

// Function to handle user inputs
void HandleInput(struct Game *g)
{
    if (IsKeyDown(KEY_LEFT)) {
        moveLeft(g->s);
    } else if (IsKeyDown(KEY_RIGHT)) {
        moveRight(g->s);
    }
}

// Drawing Game on screen
void DrawGame(struct Game *g)
{
    Draw(g->s);
}

// Game destructor functiom
void gameDestructor(struct Game* g) {
    if (g != NULL) {
        destructFunction(g->s);  
        free(g);  
    }
}
