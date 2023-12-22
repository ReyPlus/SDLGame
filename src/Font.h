#pragma once

#include "Graphics.h"
#include "SDL2/SDL_ttf.h"
#include <string>
#include <functional>

class Font {
public:
	Font(const char* path, int size, Color c, SDL_Renderer* r);
	Color getColor();
	TTF_Font* getTTF();
private:
	TTF_Font* font;
	struct Color c;
	SDL_Renderer* r;
	int size;

	friend class Text;
};

class Text {
public:
	Text(const char* text, Font* font, SDL_Renderer* r);
	void setText(const std::string& newStr);
	void modify(std::function<void(std::string&)> func);
	void move(int x, int y);
	void moveCentered(int x, int y);
	void draw();
	~Text();
private:
	Font* font;
	std::string str;
	SDL_Renderer* r;
	SDL_Rect rect;
	SDL_Surface* surface = NULL;
	SDL_Texture* texture = NULL;
};