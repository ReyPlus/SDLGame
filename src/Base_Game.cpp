#include "Base_Game.h"

#include <iostream>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"
#include "Graphics.h"
#include "Sound.h"
#include <unordered_map>

void Mouse::getPos(int& x, int& y) {
	x = this->x;
	y = this->y;
}

void Mouse::updatePress(SDL_MouseButtonEvent& be) {
	if (be.button == SDL_BUTTON_LEFT) {
		leftHeld = true;
		return;
	}

	rightHeld = true;
	return;
}

void Mouse::updateRelease(SDL_MouseButtonEvent& be) {
	if (be.button == SDL_BUTTON_LEFT) {
		leftHeld = false;
		return;
	}

	rightHeld = false;
	return;
}

bool Mouse::leftPressed() {
	static bool pressed = false;

	if (leftHeld) {
		if (!pressed) {
			pressed = true;
			return true;
		}
	}
	else {
		pressed = false;
	}

	return false;
}

bool Mouse::rightPressed() {
	static bool pressed = false;

	if (rightHeld) {
		if (!pressed) {
			pressed = true;
			return true;
		}
	}
	else {
		pressed = false;
	}

	return false;
}

bool Keyboard::checkPressed(SDL_Scancode key) {
	static std::unordered_map<SDL_Scancode, bool> releaseState;
	if (releaseState.find(key) == releaseState.end()) releaseState[key] = false;

	if (checkHeld(key)) {
		if (!releaseState[key]) {
			releaseState[key] = true;
			return true;
		}
	}
	else {
		releaseState[key] = false;
	}

	return false;
}

bool Keyboard::checkHeld(SDL_Scancode key) {
	return state[key];
}

bool Base_Game::s_initialized = false;

bool Base_Game::INIT(Uint32 SDLflags, int IMGflags, int MIXflags) {
	s_initialized = false;
	if (s_initialized) return true;

	if (SDL_Init(SDLflags) < 0) {
		std::cout << "[ERROR] SDL init failed." << std::endl;
		return s_initialized;
	}

	if (IMG_Init(IMGflags) < 0) {
		std::cout << "[ERROR] SDL init failed." << std::endl;
		return s_initialized;
	}

	if (Mix_Init(MIXflags) && MIXflags != MIXflags) {
		printf("Mix_Init: Failed to init required ogg and mod support!\n");
		printf("Mix_Init: %s\n", Mix_GetError());
		return s_initialized;
		// handle error
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return s_initialized;
	}

	if (TTF_Init() == -1) {
		printf("SDL_ttf failed to initialize. Error: %s\n", TTF_GetError());
		return s_initialized;
	}

	s_initialized = true;
	return s_initialized;
}

Base_Game::Base_Game(const char* name, unsigned int x, unsigned int y, unsigned int width, unsigned int height, Uint32 windowFlags) {
	if (!s_initialized) { std::cout << "Base_Game INIT method not properly completed."; return; }
	window = SDL_CreateWindow(name, (int)x, (int)y, (int)width, (int)height, windowFlags);
	if (!window) {
		std::cout << "[ERROR] Window creation failed." << std::endl;
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		std::cout << "[ERROR] Renderer creation failed." << std::endl;
		return;
	}

	gfx = new Graphics(renderer);
	kbd.state = SDL_GetKeyboardState(NULL);
}

void Base_Game::render() {
	SDL_RenderPresent(renderer);
}

void Base_Game::clear() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void Base_Game::poll() {
	static SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT:
			ended = true;
		case SDL_KEYDOWN:
			kbd.state = SDL_GetKeyboardState(NULL);
			break;
		case SDL_KEYUP:
			kbd.state = SDL_GetKeyboardState(NULL);
			break;
		case SDL_MOUSEMOTION:
			SDL_GetMouseState(&mouse.x, &mouse.y);
			break;
		case SDL_MOUSEBUTTONDOWN:
			mouse.updatePress(e.button);
			break;
		case SDL_MOUSEBUTTONUP:
			mouse.updateRelease(e.button);
			break;
		}
	}
}

void Base_Game::loop() {
	while (!ended) {
		logic();
		clear();
		draw();
		render();
		poll();
	}
}

Base_Game::~Base_Game() {
	delete gfx;
	IMG_Quit();

	Music::free();
	Mix_Quit();
	TTF_Quit();
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}