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

class HProgressBar : public Base_Bar {
public:
    HProgressBar(int x, int y, int w, int h, Color filled, Color notFilled, Graphics* gfx, double start = 0.0, double min = 0.0, double max = 100.0, double step = 1.0) : filled(filled), notFilled(notFilled), Base_Bar(x, y, w, h, gfx, start, min, max, step) {}

    void draw() {
        gfx->putRect(rect, notFilled);
        if (current > min) gfx->putRect(rect.x, rect.y, current*rect.w/max, rect.h, filled);
    }
private:
    Color filled;
    Color notFilled;
};

class HSlider : public Base_Slider {
public:
    HSlider(int x, int y, int w, int h, Color filled, Color notFilled, Graphics* gfx, double start = 0.0, double min = 0.0, double max = 100.0, double step = 1.0) : filled(filled), notFilled(notFilled), handle(x + start * rect.w / max, y - 5, 10, h + 10, gfx), Base_Slider(x, y, w, h, gfx, start, min, max, step) {}

    void draw() {
        gfx->putRect(rect, notFilled);
        if (current > min) gfx->putRect(rect.x, rect.y, current * rect.w / max, rect.h, filled);
        handle.draw();
    }

    bool isDragged(int x, int y) {
        if (handle.isHovering(x, y) && x >= rect.x && x <= rect.x + rect.w) {
            handle.modifyXCentered(x);
            setCurrent(x - rect.x);
            return true;
        }

        return false;
    }

    bool isClicked(int x, int y) { return false; }
private:
    class Handle : public Base_Container {
    public:
        Handle(int x, int y, int w, int h, Graphics* gfx): Base_Container(x, y, w, h, gfx) {}
        void draw() { gfx->putRect(rect, {255,255,255}); }
        void modifyXCentered(int x) {
            modifyPos(x - rect.w/2, rect.y);
        }
        bool isHovering(int x, int y) {
            return (x <= rect.x + rect.w) && (x >= rect.x) && (y <= rect.y + rect.h) && (y >= rect.y);
        }
    private:

    };

    Color filled;
    Color notFilled;
    Handle handle;
};

class Game : public Base_Game {
public:
    Game(const char* name, unsigned int x, unsigned int y, unsigned int width, unsigned int height, Uint32 windowFlags) : bar(20, 5, 100, 20, { 77, 185, 247 }, { 13, 78, 115 }, gfx, 20.0, 0.0, 100.0, 5.0), slider(20, 40, 100, 20, { 77, 185, 247 }, { 13, 78, 115 }, gfx, 20.0, 0.0, 100.0, 5.0), Base_Game(name, x, y, width, height, windowFlags) {
        
    }
private:
    void logic() {
        if (kbd.checkPressed(SDL_SCANCODE_UP)) {
            bar.takeSteps(1);
        }

        if (kbd.checkPressed(SDL_SCANCODE_DOWN)) {
            bar.takeSteps(-1);
        }

        if (mouse.leftHeld) slider.isDragged(mouse.x, mouse.y);
    }

    void draw() {
        bar.draw();
        slider.draw();
    }

private:
    HProgressBar bar;
    HSlider slider;
};

int main() {
    Game::INIT(SDL_INIT_EVERYTHING, IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_WEBP, MIX_INIT_MP3);
    Game* game = new Game("Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_RESIZABLE);

    game->loop();

    return 0;
}