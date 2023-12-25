cmake_minimum_required(VERSION 3.28.1)

project(SDLGame)

add_library(${PROJECT_NAME} STATIC src/Base_GUI.cpp)

# Subdirectories
add_subdirectory(src)