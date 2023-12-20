#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

#include "Base_Game.h"
#include "Image.h"
#include "Graphics.h"
#include "Sound.h"
#undef main

class Game : public Base_Game {
public:
    Game(const char* name, unsigned int x, unsigned int y, unsigned int width, unsigned int height, Uint32 windowFlags): effect("effect.wav"), img("test.png", 0, 0, 200, 200, renderer, 30, SDL_FLIP_VERTICAL), Base_Game(name, x, y, width, height, windowFlags) {
        Music::load("music.mp3");
    }

private:
    void logic() {
        if (kbd.checkPressed(SDL_SCANCODE_R)) effect.play();
        if (kbd.checkHeld(SDL_SCANCODE_S)) {
            Music::play();
        }
        else Music::pause();
    }

    void draw() {
        img.draw();
    }

private:
    Image img;
    Effect effect;
};

int main() {
    Game::INIT(SDL_INIT_EVERYTHING, IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_WEBP, MIX_INIT_MP3);
    Game* game = new Game("Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_RESIZABLE);

    game->loop();

    return 0;
}