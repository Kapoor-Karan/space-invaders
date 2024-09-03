#include <raylib.h>
#include "spaceship.h"

int main() {
    int windowHeight = 750;
    int windowWidth = 700;
    Color blueBackgroundColor = {0, 0, 0, 255};

    InitWindow(windowWidth, windowHeight, "Space Invaders");
    SetTargetFPS(60);

    struct spaceship* s;
    s = constructorFunction();

    while(WindowShouldClose() == false) {
        BeginDrawing();
        ClearBackground(blueBackgroundColor);
        Draw(s);
        
        EndDrawing();
    }

    CloseWindow();

}