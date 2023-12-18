#include <iostream>
#include "Base_Game.h"
#include "SDL2/SDL.h"
#undef main

class Game : public Base_Game {
public:
    Game() {}

    

private:
    void logic() {

    }

    void draw() {

    }
};

int main() {
    Game* game = new Game();
    Game::INIT();

    game->loop();

    return 0;
}