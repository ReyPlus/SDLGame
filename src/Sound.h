#pragma once
#include "SDL2/SDL_mixer.h"

class Effect {
public:
	Effect(const char* path);

	void play();

	~Effect();
private:
	Mix_Chunk* effect;
};

class Music {
public:
	static bool load(const char* path);
	static void play();
	static void pause();
	static void end();
	static void free();
private:
	Music() {}
	~Music() {}
	static Mix_Music* music;
};