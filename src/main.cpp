#include <iostream>
#include "Base_Game.h"
#include "SDL2/SDL.h"
#include "Graphics.h"
#undef main

class Game : public Base_Game {
public:
    Game(const char* name, unsigned int x, unsigned int y, unsigned int width, unsigned int height, Uint32 flags): lineColor(0,255,0), circleColor(255,255,255), rectColor(255,0,0), Base_Game(name, x, y, width, height, flags) {}

private:
    void logic() {}

    void draw() {
        //gfx->putPixel(100, 100, pixColor);
        //gfx->putLine(0, 300, 800, 300, pixColor);
        gfx->putLine(0, 250, 800, 250, lineColor);
        gfx->putLine(0, 350, 800, 350, lineColor);
        //gfx->putLine(400, 0, 400, 600, pixColor);
        gfx->putLine(350, 0, 350, 600, lineColor);
        gfx->putLine(450, 0, 450, 600, lineColor);
        gfx->putRect(350, 250, 100, 100, rectColor);
        gfx->putCircle(400, 300, 50, circleColor);
    }

private:
    Color circleColor;
    Color rectColor;
    Color lineColor;
};

int main() {
    Game* game = new Game("Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_RESIZABLE);
    Game::INIT();

    game->loop();

    return 0;
}