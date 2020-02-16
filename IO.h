#pragma once

#include <SDL.h>
#include <string>
using namespace std;

enum color {BLACK, RED, GREEN, BLUE, CYAN, PURPLE, YELLOW, WHITE, COLOR_MAX};

class IO {
public:
	IO();
	IO(const IO &source);
	void DrawRectangle(int pX1, int pY1, int pX2, int pY2, enum color pC, bool filled);
	void ClearScreen();
	int GetScreenHeight();
	bool InitGraph();
	int PollKey();
	int GetKey();
	int IsKeyDown(int pKey);
	void UpdateScreen();
	bool loadMedia(string path);
	void endGame();
	~IO();

private:

	static SDL_Window* window;
	static SDL_Renderer* gRenderer;
	static SDL_Surface* gSurface;
	static SDL_Texture* gTexture;
};
