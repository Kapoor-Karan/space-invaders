#include <raylib.h>
#include "game.h"
#include <stdlib.h>  
#include "alien.h"

// main function
int main() {
    int windowHeight = 750; // game window height
    int windowWidth = 700;  // game window width
    Color whiteBackgroundColor = {0, 0, 0, 255}; // game window background colour

    InitWindow(windowWidth, windowHeight, "Space Invaders"); // Initialising the windows
    SetTargetFPS(60);

    struct Game* g = (struct Game*)malloc(sizeof(struct Game));  
    if (g == NULL) {
        return -1;  
    }

    g->s = constructorFunction();  
    Vector2 pos = {100,100};
    struct Alien *a = alienConstructor(pos);
    // Game Loop
    while (WindowShouldClose() == false) {

        HandleInput(g);
        UpdateGame(g);
        BeginDrawing();
        ClearBackground(whiteBackgroundColor);
        DrawGame(g);
        DrawAlien(a);
        EndDrawing();
    }

    destructFunction(g->s);  
    free(g);  
    CloseWindow();

    return 0;  
}
