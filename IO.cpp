#include "IO.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
using namespace std;

static int mColors[COLOR_MAX][3] = { {0x00, 0x00, 0x00}, {0xFF, 0x00, 0x00}, {0x00, 0xFF, 0x00},
							{0x00, 0x00, 0xFF}, {0x00, 0xFF, 0xFF}, {0xFF, 0x00, 0xFF},
							{0xFF, 0xFF, 0x00}, {0xFF, 0xFF, 0xFF} };

SDL_Window* IO::window;
SDL_Renderer* IO::gRenderer;
SDL_Surface* IO::gSurface;
SDL_Texture* IO::gTexture;

IO::IO() {
	if (InitGraph() == false) {
		cout << "Error setting up video.";
		exit(0);
	}
}

IO::IO(const IO& source) {
	InitGraph();
	loadMedia("gameOver.png");
}

// Draw rectangle
// *** Perhaps come back to later. px2 and pY2 might be wrong *** 
void IO::DrawRectangle(int pX1, int pY1, int pX2, int pY2, enum color pC, bool filled) {
	SDL_Rect gRect = { pX1, pY1, pX2, pY2 };
	
	SDL_SetRenderDrawColor(gRenderer, mColors[pC][0], mColors[pC][1], mColors[pC][2], 0xFF);
	if (filled == true) SDL_RenderFillRect(gRenderer, &gRect);
	else SDL_RenderDrawRect(gRenderer, &gRect);
}

// Clear screen to black
void IO::ClearScreen() {
	SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(gRenderer);
}

int IO::GetScreenHeight() {
	return 720;
}

bool IO::InitGraph() {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		cout << "SDL couldn't initialize! SDL_Error:\n " << SDL_GetError();
		return false;
	}
	else {
		window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			720, 576, SDL_WINDOW_SHOWN);
		if (window == NULL) {
			cout << "Couldn't initialize window! SDL_Error:\n" << SDL_GetError();
			return false;
		}
		else {
			gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL) {
				cout << "Couldn't initialize renderer! SDL_ERROR:\n" << SDL_GetError();
				return false;
			}
			else {
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					cout << "SDL_image could not initialize! SDL_image Error: " << SDL_GetError();
					return false;
				}
			}
		}
	}

	return true;
}

int IO::PollKey() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_KEYDOWN: {
			return e.key.keysym.sym;
		}
		case SDL_QUIT: {
			endGame();
			SDL_Delay(2000);
			exit(3);
		}
		}
	}
	return -1;
}

int IO::GetKey() {
	SDL_Event e;
	while (true)
	{
		SDL_WaitEvent(&e);
		if (e.type == SDL_KEYDOWN)
			break;
		if (e.type == SDL_QUIT) {
			SDL_Delay(2000);
			exit(3);
		}
	};
	return e.key.keysym.sym;
}

int IO::IsKeyDown(int pKey) {
	SDL_PumpEvents();
	int mNumkeys;
	const Uint8* mKeytable = SDL_GetKeyboardState(&mNumkeys);
	return mKeytable[pKey];
}

void IO::UpdateScreen() {
	SDL_RenderPresent(gRenderer);
}

bool IO::loadMedia(string path) {
	gSurface = IMG_Load(path.c_str());
	if (gSurface == NULL) {
		cout << "Failed to load image! Error: " << IMG_GetError();
	}
	else {
		gTexture = SDL_CreateTextureFromSurface(gRenderer, gSurface);
		SDL_FreeSurface(gSurface);
		if (gTexture == NULL) {
			cout << "Failed to create texture! Error: " << SDL_GetError();
			return false;
		}
	}
	return true;
}

void IO::endGame() {
	SDL_RenderClear(gRenderer);
	SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);
	SDL_RenderPresent(gRenderer);
	SDL_Delay(2000);
}

IO::~IO() {
	SDL_DestroyWindow(window);
	window = NULL;

	SDL_DestroyRenderer(gRenderer);
	gRenderer = NULL;

	if (gSurface != NULL) SDL_FreeSurface(gSurface);
	gSurface = NULL;

	SDL_DestroyTexture(gTexture);
	gTexture = NULL;

	SDL_Quit();
}