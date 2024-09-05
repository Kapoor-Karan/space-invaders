#pragma once
#include <raylib.h>

struct Alien {
    Vector2 position;
    Texture2D image;  
};

// Function declarations
struct Alien *alienConstructor(Vector2 position);
void DrawAlien(struct Alien* a);
void UnloadAlien(struct Alien* a);
