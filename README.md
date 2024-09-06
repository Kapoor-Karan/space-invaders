
Space Invaders Game (C Version)
This is a Space Invaders game developed in C using the raylib library for rendering and game management. The player controls a spaceship and shoots at waves of aliens. Once all aliens are destroyed, they respawn, and the game continues. The goal is to achieve the highest possible score before losing all lives.

Table of Contents
Features
Installation
Controls
Project Structure
Gameplay Mechanics
Credits
Features
Player-controlled spaceship that moves left and right, shoots lasers.
Waves of aliens that move across the screen and shoot back.
Obstacles that block lasers and get destroyed when hit.
Mystery ship that appears occasionally, giving bonus points when destroyed.
Score and Highscore tracking.
Endless waves: When all aliens are destroyed, they respawn, and the game continues.
Sound effects for explosions and shooting.
Game over condition when player loses all lives.
Installation
Prerequisites
Make sure you have the following installed on your system:

C compiler (like GCC or Clang)
Make (optional, if using the provided Makefile)
raylib: The game uses the raylib library for rendering. You can install it via:
On Linux (Ubuntu/Debian):
bash
Copy code
sudo apt install libraylib-dev
On Windows: You can download precompiled raylib binaries from the official raylib website and link it in your project.
Installation Steps
Clone the repository:

bash
Copy code
git clone https://github.com/yourusername/space-invaders-c.git
cd space-invaders-c
Install raylib: Follow the instructions from raylib.

Compile the project: If you are using the Makefile provided:

bash
Copy code
make
Otherwise, you can manually compile using:

bash
Copy code
gcc -o space_invaders main.c game.c spaceship.c laser.c alien.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
Run the game:

bash
Copy code
./space_invaders
Controls
Move Left: Left Arrow
Move Right: Right Arrow
Shoot: Space
Project Structure
makefile
Copy code
├── assets/              # Game assets (images, sounds)
│   ├── player.png       # Spaceship sprite
│   ├── enemy.png        # Alien sprite
│   ├── explosion.wav    # Explosion sound effect
│   └── ...              # Other assets
├── src/                 # Source files
│   ├── main.c           # Entry point of the game
│   ├── game.c           # Game logic
│   ├── spaceship.c      # Spaceship logic
│   ├── alien.c          # Alien logic
│   ├── laser.c          # Laser logic
│   └── ...              # Other source files
├── include/             # Header files
│   ├── game.h           # Header file for game logic
│   ├── spaceship.h      # Header file for spaceship logic
│   ├── alien.h          # Header file for alien logic
│   └── ...              # Other headers
├── Makefile             # For compiling the project (optional)
└── README.md            # This README file
Gameplay Mechanics
Spaceship Movement: The player can move the spaceship left and right using arrow keys and shoot lasers to destroy aliens.
Alien Waves: Aliens move horizontally across the screen, switching directions when they reach the edges. If they move down enough or shoot the player, the game becomes more difficult.
Obstacles: Obstacles can block both player and alien lasers. They degrade over time as they take damage.
Respawning Aliens: After all aliens are destroyed, they respawn at the top of the screen.
Scoring: Points are awarded based on the type of alien destroyed and bonus points for the mystery ship.
Lives: The player starts with multiple lives and loses one if hit by an alien laser. The game ends when all lives are lost.
Credits
raylib: For providing an easy-to-use game development framework.
Game Development: Developed by [Your Name].
Inspiration: Classic Space Invaders arcade game.
