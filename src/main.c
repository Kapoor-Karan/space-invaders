#include <raylib.h>

int main() {
    int windowHeight = 800;
    int windowWidth = 800;

    InitWindow(windowWidth, windowHeight, "Space Invaders");
    SetTargetFPS(60);

    while(WindowShouldClose() == false) {
        BeginDrawing();
        EndDrawing();

    }

    CloseWindow();

}