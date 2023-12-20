#include "Sound.h"
#include "SDL2/SDL_mixer.h"

Mix_Music* Music::music;

Effect::Effect(const char* path) {
	effect = Mix_LoadWAV(path);
	if (effect == NULL) { printf("Failed to load Sound Effect. SDL_mixer Error: %s\n", Mix_GetError()); }
}

void Effect::play() {
	Mix_PlayChannel(-1, effect, 0);
}

Effect::~Effect() {
	Mix_FreeChunk(effect);
}

bool Music::load(const char* path) {
	if (music != NULL) { Mix_FreeMusic(music); music = nullptr; }

	music = Mix_LoadMUS(path);
	if (music == NULL) { printf("Failed to load Music. SDL_mixer Error: %s\n", Mix_GetError()); return false; }
	return true;
}

void Music::play() {
	if (!Mix_PlayingMusic()) { Mix_PlayMusic(music, -1); return; }
	if (Mix_PausedMusic()) Mix_ResumeMusic();
}

void Music::pause() {
	if (Mix_PlayingMusic() && !Mix_PausedMusic()) Mix_PauseMusic();
}

void Music::end() {
	if (Mix_PlayingMusic()) Mix_HaltMusic();
}

void Music::free() {
	if (music != NULL) {
		Mix_FreeMusic(music);
		music = nullptr;
	}
}