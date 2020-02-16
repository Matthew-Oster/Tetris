#pragma once
#include "tetrominos.h"
#include <iostream>
using namespace std;

#ifndef BOARD_FORMAT
#define BOARD_LINE_WIDTH 6			// Width of two lines that delimit the board
#define BLOCK_SIZE 16				// Width and height of each block in a piece
#define BOARD_POSITION 320			// Center position of board from the left of the screen
#define BOARD_WIDTH 10				// Board width in blocks
#define BOARD_HEIGHT 16				// Board height in blocks
#define MIN_VERTICAL_MARGIN 20		// Min vertical margin for board limit
#define MIN_HORIZONTAL_MARGIN 20	// Min horizontal margin for board limit
#define PIECE_BLOCKS 5				// Number of vertical/horizontal blocks in matrix piece
#endif

class Board {
public:
	
	Board(Tetromino* pPiece = NULL, int pScreenHeight = 0) :
		mPiece(pPiece), mScreenHeight(pScreenHeight) {}

	int getXPosInPixels(int pPos);
	int getYPosInPixels(int pPos);
	bool isFreeBlock(int pY, int pX);
	bool isPossibleMovement(int pY, int pX);
	void storePiece(int pY, int pX);
	unsigned long deletePossibleLines();
	bool isGameOver();
	void showBoard();

private:
	void initBoard();
	void deleteLine(int pY);

	enum {POS_FREE, POS_FILLED};
	int mBoard[BOARD_HEIGHT][BOARD_WIDTH];
	Tetromino *mPiece;
	int mScreenHeight;
};