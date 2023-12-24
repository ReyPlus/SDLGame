#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

#include "Base_Game.h"
#include "Image.h"
#include "Graphics.h"
#include "Base_GUI.h"
#include "Sound.h"
#include "Font.h"
#undef main

class Button : public Base_Clickable {
public:
    Button(int x, int y, int w, int h, Color c, Graphics* gfx) : c(c), Base_Clickable(x, y, w, h, gfx) {}
    void click() { printf("Button was Clicked\n"); }
    void moveCentered(int x, int y) {
        rect.x = int((float)x - (float)rect.w / 2);
        rect.y = int((float)y - (float)rect.h / 2);
    }
    void draw() { gfx->putRect(rect, c); }
private:
    Color c;
};

class Switch : public Base_Switch {
public:
    Switch(int x, int y, int w, int h, Graphics* gfx) : offC(224, 79, 79), onC(74, 119, 224), Base_Switch(x, y, w, h, gfx) {}
    void draw() {
        gfx->putRect(rect, switched? onC : offC);
    }
private:
    Color offC;
    Color onC;
};

class Game : public Base_Game {
public:
    Game(const char* name, unsigned int x, unsigned int y, unsigned int width, unsigned int height, Uint32 windowFlags) : mySwitch(0,0,100,50, gfx), greenButton(0, 0, 100, 50, { 84, 214, 81 }, gfx), Base_Game(name, x, y, width, height, windowFlags) {
        greenButton.moveCentered(width/2, height/2);
    }
private:
    void logic() {
        if (mouse.leftPressed()) {
            greenButton.checkClicked(mouse.x, mouse.y);
            mySwitch.checkClicked(mouse.x, mouse.y);
        }
    }

    void draw() {
        greenButton.draw();
        mySwitch.draw();
    }

private:
    Switch mySwitch;
    Button greenButton;
};

int main() {
    Game::INIT(SDL_INIT_EVERYTHING, IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_WEBP, MIX_INIT_MP3);
    Game* game = new Game("Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_RESIZABLE);

    game->loop();

    return 0;
}