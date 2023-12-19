#include "Image.h"
#include <iostream>

Image::Image(const char* file, int x, int y, int w, int h, SDL_Renderer* r, int degrees, SDL_RendererFlip flipFlag): r(r), degrees(degrees), flipFlag(flipFlag) {
	rect = new SDL_Rect();
	move(x, y);
	setSize(w, h);

	img = IMG_Load(file);
	if (!img) { std::cout << "[IMAGE] Failed to load " << file << ": " << IMG_GetError(); }
	texture = SDL_CreateTextureFromSurface(r, img);
}

Image::Image(const char* file, SDL_Renderer* r, int degrees, SDL_RendererFlip flipFlag): r(r), degrees(degrees), flipFlag(flipFlag) {
	rect = NULL;

	img = IMG_Load(file);
	if (!img) { std::cout << "[IMAGE] Failed to load " << file << ": " << IMG_GetError(); }
	texture = SDL_CreateTextureFromSurface(r, img);
}

void Image::move(int x, int y) { rect->x = x; rect->y = y; }
void Image::setSize(int w, int h) { rect->w = w; rect->h = h; }
void Image::draw() {
	SDL_RenderCopyEx(r, texture, NULL, rect, degrees, NULL, flipFlag);
}

Image::~Image() {
	delete rect;
	SDL_FreeSurface(img);
	SDL_DestroyTexture(texture);
}