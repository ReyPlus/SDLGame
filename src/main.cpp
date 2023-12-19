#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "Base_Game.h"
#include "Image.h"
#include "Graphics.h"
#undef main

class Game : public Base_Game {
public:
    Game(const char* name, unsigned int x, unsigned int y, unsigned int width, unsigned int height, Uint32 SDLflags, int IMGflags): img("test.png", 0, 0, 200, 200, renderer, 30, SDL_FLIP_VERTICAL), Base_Game(name, x, y, width, height, SDLflags, IMGflags) {}

private:
    void logic() {}

    void draw() {
        img.draw();
    }

private:
    Image img;
};

int main() {
    Game* game = new Game("Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_RESIZABLE, IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_WEBP);

    game->loop();

    return 0;
}