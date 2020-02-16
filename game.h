#pragma once
#include "board.h"
#include "tetrominos.h"
#include "IO.h"
#include <time.h>
using namespace std;


class Game {
public:
	Game(Board *pBoard, Tetromino *pTetromino, IO *pIO, int pScreenHeight);

	void DrawScene();
	void GetNewPiece();

	int posY, posX;				// Position of falling piece
	unsigned long score;

	Board* mBoard = NULL;
	Tetromino* mTetromino = NULL;
	IO* mIO = NULL;

private:

	int GetRand(int pA, int pB);
	void InitGame();
	void DrawPiece(int pY, int pX);
	void DrawBoard();

	int screenHeight;			// Screen height in pixels
};