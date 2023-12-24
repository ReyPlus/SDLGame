#pragma once

#include "SDL2/SDL.h"

struct Color {
	Color(int r, int g, int b, int a = 255);
	SDL_Color c;
	void update(int r, int g, int b, int a = 255);
};

class Graphics {
public:
	Graphics(struct SDL_Renderer*);
	void putPixel(int x, int y, const Color& c);
	void putLine(int x1, int y1, int x2, int y2, const Color& c);

	void putRect(int x, int y, int width, int height, const Color& c);
	void putRect(SDL_Rect& rect, const Color& c);

	void putCircle(int x, int y, int r, const Color& c);
private:
	struct SDL_Renderer* pen;
};