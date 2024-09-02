#include <raylib.h>

int main() {
    int windowHeight = 750;
    int windowWidth = 700;
    Color blueBackgroundColor = {0, 0, 255, 255};

    InitWindow(windowWidth, windowHeight, "Space Invaders");
    SetTargetFPS(60);

    while(WindowShouldClose() == false) {
        BeginDrawing();
        EndDrawing();
        ClearBackground(blueBackgroundColor);
    }

    CloseWindow();

}