#pragma once
#include "spaceship.h"
#include "alien.h"
#include <stdbool.h>

// Game structure defined
struct Game {
    struct spaceship* s;
    struct Alien *aliens;
    int alienCount;
    Texture2D AlienImage;
    int aliensDirection;
    struct Laser *alienLasers;
    int alienLaserCount;
    int alienLaserCapacity;
    double timeLastAlienFired; 
    double alienLaserShootInterval;  
    int lives;
    bool run;
    int score;
};

// Game methods 
struct Game* gameConstructor();
void HandleInput(struct Game* g);
void gameDestructor(struct Game* g);
void DrawGame(struct Game* g);
void UpdateGame(struct Game* g);
void DeleteInactiveLasers(struct Game* g);
struct Alien* CreateAliens(Texture2D texture);
void MoveAliens(struct Game* g);
void MoveDownAliens(struct Game* g, int distance);
void AlienShootLaser(struct Game* g);
void CheckCollisions(struct Game* g);
void GameOver(struct Game* g);
struct Game* InitGame();
void ResetAliens(struct Game* g);