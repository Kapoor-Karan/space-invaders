cmake_minimum_required(VERSION 3.10)
project(MyRaylibGame)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(MyRaylibGame src/main.c src/spaceship.c)

target_link_libraries(MyRaylibGame raylib)