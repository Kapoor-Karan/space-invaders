#include <raylib.h>
#include "game.h"
#include <stdlib.h>  

int main() {
    int windowHeight = 750;
    int windowWidth = 700;
    Color whiteBackgroundColor = {0, 0, 0, 255};

    InitWindow(windowWidth, windowHeight, "Space Invaders");
    SetTargetFPS(60);

    struct Game* g = (struct Game*)malloc(sizeof(struct Game));  
    if (g == NULL) {
        return -1;  
    }

    g->s = constructorFunction();  

    while (WindowShouldClose() == false) {

        HandleInput(g);
        
        BeginDrawing();
        ClearBackground(whiteBackgroundColor);
        DrawGame(g);
        EndDrawing();
    }

    destructFunction(g->s);  
    free(g);  
    CloseWindow();

    return 0;  
}
