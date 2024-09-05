#pragma once
#include <raylib.h>

struct Alien {
    Texture2D image;
    Vector2 position;
};

struct Alien* alienConstructor(Vector2 position);
void Update(struct Alien* a);
void DrawAlien(struct Alien* a);