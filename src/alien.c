#include "alien.h"
#include <stdlib.h>

struct Alien *alienConstructor(Vector2 position)
{
    struct Alien *a = (struct Alien*) (malloc(sizeof(struct Alien)));
    a->position = position;
    a->image = LoadTexture("../assets/enemy.png");
    return a;
}

void DrawAlien(struct Alien* a) {
    DrawTexture(a->image, a->position.x, a->position.y, WHITE);
}

void UpdateAlien(struct Alien* a, int direction) {
    a->position.x += direction;
}

Rectangle getRectAlien(struct Alien* a) {
    Rectangle temp = {a->position.x, a->position.y, a->image.width, a->image.height};
    return temp;
}