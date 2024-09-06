cmake_minimum_required(VERSION 3.10)
project(SpaceInvaders)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(SpaceInvaders src/main.c src/spaceship.c src/game.c src/laser.c src/alien.c)

target_link_libraries(SpaceInvaders raylib)