cmake_minimum_required(VERSION 3.28.1)

project(SDLGame)

target_sources(${PROJECT_NAME} PRIVATE 
Base_Game.cpp
Base_GUI.cpp
FileHandler.cpp
Font.cpp
Graphics.cpp
Image.cpp
Sound.cpp
Base_Game.h
Base_GUI.h
FileHandler.h
Font.h
Graphics.h
Image.h
Sound.h)