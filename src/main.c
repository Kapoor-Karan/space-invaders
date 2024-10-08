#include <raylib.h>
#include "game.h"
#include <stdlib.h>  

// main function
int main() {
    int windowHeight = 750; // game window height
    int windowWidth = 700;  // game window width
    Color whiteBackgroundColor = {0, 0, 0, 255}; // game window background colour

    InitWindow(windowWidth, windowHeight, "Space Invaders"); // Initialising the windows
    SetTargetFPS(60);

    struct Game* g = gameConstructor();  
    if (g == NULL) {
        return -1;  
    }

    g->s = constructorFunction();  
    // Game Loop
    while (WindowShouldClose() == false) {

        HandleInput(g);
        UpdateGame(g);
        BeginDrawing();
        ClearBackground(whiteBackgroundColor);
        Vector2 pos = {50,15};
        DrawGame(g);
        EndDrawing();
    }
    gameDestructor(g);
    free(g);  
    CloseWindow();

    return 0;  
}
