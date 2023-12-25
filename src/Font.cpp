#include "Font.h"
#include "SDL2/SDL_ttf.h"

Font::Font(const char* path, int size, Color c, SDL_Renderer* r) : c(c), r(r), size(size) {
	font = TTF_OpenFont(path, size);
	if (!font) printf("Failed to load font. Error: %s\n", TTF_GetError());
}

TTF_Font* Font::getTTF() { return font; }

Color Font::getColor() { return c; }

Text::Text(const char* text, Font* in_font, SDL_Renderer* r): font(in_font), r(r) {
	str = text;
	surface = TTF_RenderText_Solid(font->getTTF(), text, font->getColor().c);
	texture = SDL_CreateTextureFromSurface(r, surface);
	TTF_SizeText(font->getTTF(), str.c_str(), &rect.w, &rect.h);
	rect.x = 0;
	rect.y = 0;
}

void Text::setText(const std::string& newStr) {
	str = newStr;
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
	surface = TTF_RenderText_Solid(font->getTTF(), str.c_str(), font->getColor().c);
	texture = SDL_CreateTextureFromSurface(r, surface);
	TTF_SizeText(font->getTTF(), str.c_str(), &rect.w, &rect.h);
}

void Text::modify(std::function<void(std::string&)> func) {
	func(str);
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
	surface = TTF_RenderText_Solid(font->getTTF(), str.c_str(), font->getColor().c);
	texture = SDL_CreateTextureFromSurface(r, surface);
	TTF_SizeText(font->getTTF(), str.c_str(), &rect.w, &rect.h);
}

void Text::move(int x, int y) { rect.x = x; rect.y = y; }

void Text::moveCentered(int x, int y) {
	rect.x = int((float)x - (float)rect.w / 2);
	rect.y = int((float)y - (float)rect.h / 2);
}

void Text::draw() {
	SDL_RenderCopy(r, texture, NULL, &rect);
}

Text::~Text() {
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}