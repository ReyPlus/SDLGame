#include "Graphics.h"
#include "SDL2/SDL.h"

static int getDistSqrd(int x1, int y1, int x2, int y2) {
	int dx = x2 - x1;
	int dy = y2 - y1;
	return dx*dx + dy*dy;
}

Color::Color(int r, int g, int b, int a) { update(r,g,b,a); }

void Color::update(int r, int g, int b, int a) {
	c.r = (Uint8)r;
	c.g = (Uint8)g;
	c.b = (Uint8)b;
	c.a = (Uint8)a;
}

Graphics::Graphics(SDL_Renderer* r) : pen(r) {}

void Graphics::putPixel(int x, int y, const Color& c) {
	SDL_SetRenderDrawColor(pen, c.c.r, c.c.g, c.c.b, c.c.a);
	SDL_RenderDrawPoint(pen, x, y);
}

void Graphics::putLine(int x1, int y1, int x2, int y2, const Color& c) {
	SDL_SetRenderDrawColor(pen, c.c.r, c.c.g, c.c.b, c.c.a);
	SDL_RenderDrawLine(pen, x1, y1, x2, y2);
}

void Graphics::putRect(int x, int y, int width, int height, const Color& c) {
	for (int i = y; i < y + height; i++) putLine(x, i, x + width, i, c);
}

void Graphics::putRect(SDL_Rect& rect, const Color& c) { putRect(rect.x, rect.y, rect.w, rect.h, c); };

void Graphics::putCircle(int x, int y, int r, const Color& c) {
	for (int ix = x - r; ix < x + r; ix++) {
		for (int iy = y - r; iy < y + r; iy++) {
			if (r*r >= getDistSqrd(x, y, ix, iy)) {
				putPixel(ix, iy, c);
			}
		}
	}
}