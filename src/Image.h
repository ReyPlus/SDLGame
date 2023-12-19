#include "SDL2/SDL_image.h"

class Image {
public:
	Image(const char* file, int x, int y, int w, int h, SDL_Renderer* r, int degrees = 0, SDL_RendererFlip flipFlag = SDL_FLIP_NONE);
	Image(const char* file, SDL_Renderer* r, int degrees = 0, SDL_RendererFlip flipFlag = SDL_FLIP_NONE);

	void move(int x, int y);
	void setSize(int w, int h);
	void draw();

	~Image();
private:
	SDL_Renderer* r;
	SDL_Rect* rect;
	SDL_Surface* img;
	int degrees = 0;
	SDL_RendererFlip flipFlag;
	SDL_Texture* texture;
};