cmake_minimum_required(VERSION 3.28.1)

project(SDLGame)

# Subdirectories
add_subdirectory(src)

add_executable(${PROJECT_NAME} src/main.cpp)