#include "spaceship.h"
#include <stdlib.h>

struct spaceship* constructorFunction()
{
    struct spaceship* s = (struct spaceship*) malloc(sizeof(Texture2D) + sizeof(Vector2));
    s->image = LoadTexture("../assets/player.png");
    s->position.x = (GetScreenWidth() - s->image.width)/2;
    s->position.x = (GetScreenHeight() - s->image.height)/2;
}

void destructFunction(struct spaceship s)
{
    UnloadTexture(s.image);
}

void Draw(struct spaceship s)
{
    DrawTextureV(s.image, s.position, WHITE);
}