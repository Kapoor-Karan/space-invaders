cmake_minimum_required(VERSION 3.5)
project(SpaceInvaders)

add_executable(SpaceInvaders src/main.c src/enemy.c src/player.c)

include_directories(include)

target_link_libraries(SpaceInvaders SDL2 SDL2_image SDL2_ttf)