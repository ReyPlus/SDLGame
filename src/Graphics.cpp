#include "Graphics.h"
#include "SDL2/SDL.h"

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