#include <iostream>
#include "SDL2/SDL_scancode.h"

struct Mouse {
	int x, y;
	bool leftHeld = false, rightHeld = false;
	void getPos(int& x, int& y);
	void updatePress(struct SDL_MouseButtonEvent& be);
	void updateRelease(struct SDL_MouseButtonEvent& be);
	bool leftPressed();
	bool rightPressed();
};

struct Keyboard {
	const unsigned char* state;
	bool checkPressed(SDL_Scancode key);
	bool checkHeld(SDL_Scancode key);
};

class Base_Game {
public:
	static bool INIT(Uint32 SDLflags, int IMGflags, int MIXflags);
	Base_Game(const char* name, unsigned int x, unsigned int y, unsigned int width, unsigned int height, Uint32 windowFlags);
	virtual void loop();
	virtual ~Base_Game();

protected:
	void render();
	void clear();
	virtual void poll();
	virtual void logic() = 0;
	virtual void draw() = 0;

protected:
	Mouse mouse{ 0,0 };
	Keyboard kbd;
	bool ended = false;
	class Graphics* gfx = nullptr;
	struct SDL_Window* window = nullptr;
	struct SDL_Renderer* renderer = nullptr;

private:
	static bool s_initialized;
};