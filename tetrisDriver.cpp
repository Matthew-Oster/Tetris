#include "game.h"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#ifndef LINUX
#include <Windows.h>
#endif
#include <iostream>
#include <ctime>
using namespace std;


int main(int argc, char* argv[]) {
	srand(time(NULL));

	IO mIO;
	mIO.loadMedia("gameOver.png");

	int screenHeight = mIO.GetScreenHeight();
	Tetromino mTetromino(rand() % 7);
	Board mBoard(&mTetromino, screenHeight);
	Game mGame(&mBoard, &mTetromino, &mIO, screenHeight);

	unsigned long mTime1 = SDL_GetTicks();
	int WAIT_TIME = 1000;
	int next_level = 200;

	while (!mIO.IsKeyDown(SDLK_ESCAPE)) {
		mIO.ClearScreen();
		mGame.DrawScene();
		mIO.UpdateScreen();

		
		int mKey = mIO.PollKey();

		switch (mKey) {
		case(SDLK_RIGHT): {
			if (mBoard.isPossibleMovement(mGame.posY, mGame.posX + 1))
				mGame.posX++;
			break;
		}
		case(SDLK_LEFT): {
			if (mBoard.isPossibleMovement(mGame.posY, mGame.posX - 1))
				mGame.posX--;
			break;
		}
		case(SDLK_DOWN): {
			if (mBoard.isPossibleMovement(mGame.posY + 1, mGame.posX))
				mGame.posY++;
			else {
				mBoard.storePiece(mGame.posY, mGame.posX);
				mGame.score += mBoard.deletePossibleLines();

				if (mBoard.isGameOver()) {
					SDL_Delay(1000);
					mIO.endGame();
					return 0;
				}

				if (mGame.score >= next_level) {
					WAIT_TIME /= 2;
					next_level *= 2;
				}

				mGame.GetNewPiece();
			}
			break;
		}
		case(SDLK_c): {
			while (mBoard.isPossibleMovement(mGame.posY + 1, mGame.posX)) { mGame.posY++; }
			mBoard.storePiece(mGame.posY, mGame.posX);
			mGame.score += mBoard.deletePossibleLines();

			if (mBoard.isGameOver()) {
				SDL_Delay(1000);
				mIO.endGame();
				return 0;
			}
			
			if (mGame.score >= next_level) {
				WAIT_TIME /= 2;
				next_level *= 2;
			}

			mGame.GetNewPiece();
			break;
		}
		case(SDLK_z): {
			mGame.mTetromino->rotate();
			if (!mBoard.isPossibleMovement(mGame.posY, mGame.posX))
				mGame.mTetromino->undoRotate();
			break;
		}
		}
		
		// Vertical movement
		unsigned long mTime2 = SDL_GetTicks();
		if ((mTime2 - mTime1) > WAIT_TIME) {
			if (mBoard.isPossibleMovement(mGame.posY + 1, mGame.posX)) {
				mGame.posY++;
			}
			else {
				mBoard.storePiece(mGame.posY, mGame.posX);
				mGame.score += mBoard.deletePossibleLines();

				if (mBoard.isGameOver()) {
					SDL_Delay(1000);
					mIO.endGame();
					return 0;
				}

				mGame.GetNewPiece();

				if (mGame.score >= next_level) {
					WAIT_TIME /= 2;
					next_level *= 2;
				}
			}

			mTime1 = SDL_GetTicks();
		}
	}
	SDL_Delay(2000);
	return 0;
}