#include "Graphics.h"
#include "SDL2/SDL.h"

static int getDistSqrd(int x1, int y1, int x2, int y2) {
	int dx = x2 - x1;
	int dy = y2 - y1;
	return dx*dx + dy*dy;
}

Color::Color(int r, int g, int b, int a) : r(r), g(g), b(b), a(a) {}

void Color::update(int r, int g, int b, int a) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Graphics::Graphics(SDL_Renderer* r) : pen(r) {}

void Graphics::putPixel(int x, int y, const Color& c) {
	SDL_SetRenderDrawColor(pen, c.r, c.g, c.b, c.a);
	SDL_RenderDrawPoint(pen, x, y);
}

void Graphics::putLine(int x1, int y1, int x2, int y2, const Color& c) {
	SDL_SetRenderDrawColor(pen, c.r, c.g, c.b, c.a);
	SDL_RenderDrawLine(pen, x1, y1, x2, y2);
}

void Graphics::putRect(int x, int y, int width, int height, const Color& c) {
	for (int i = y; i < y + height; i++) putLine(x, i, x + width, i, c);
}

void Graphics::putCircle(int x, int y, int r, const Color& c) {
	for (int ix = x - r; ix < x + r; ix++) {
		for (int iy = y - r; iy < y + r; iy++) {
			if (r*r >= getDistSqrd(x, y, ix, iy)) {
				putPixel(ix, iy, c);
			}
		}
	}
}