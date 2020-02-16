#include "board.h"
#include <iostream>
using namespace std;

int Board::getXPosInPixels(int pPos) {
	return  ((BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2))) + (pPos * BLOCK_SIZE));
}

int Board::getYPosInPixels(int pPos) {
	return int ((MIN_VERTICAL_MARGIN * 3) + (pPos * BLOCK_SIZE));
}

// Retruns true if a given block is empty
bool Board::isFreeBlock(int pY, int pX) {
	if (mBoard[pY][pX] == POS_FREE) return true;
	else return false;
}

bool Board::isPossibleMovement(int pY, int pX) {
	for (int i1 = pY, i2 = 0; i1 < pY + PIECE_BLOCKS; ++i1, ++i2) {
		for (int j1 = pX, j2 = 0; j1 < pX + PIECE_BLOCKS; ++j1, ++j2) {
			
			if (j1 < 0 || j1 > BOARD_WIDTH - 1 || i1 > BOARD_HEIGHT - 1) {
				if (mPiece->getBlockType(i2, j2) != 0) {
					return false;
				}
			}

			if ((mPiece->getBlockType(i2, j2) != 0) && (!isFreeBlock(i1, j1))) {
				return false;
			}
		}
	}
	return true;
}

// Stores a piece at location [pX][pY] in the board.
void Board::storePiece(int pY, int pX) {
	for (int i1 = pY, i2 = 0; i1 < pY + PIECE_BLOCKS; ++i1, ++i2) {
		for (int j1 = pX, j2 = 0; j1 < pX + PIECE_BLOCKS; ++j1, ++j2) {
			if (mPiece->getBlockType(i2, j2) != 0)
				mBoard[i1][j1] = POS_FILLED;
		}
	}
}

unsigned long Board::deletePossibleLines() {
	int deleteCount = 0;
	for (int i = 0; i < BOARD_HEIGHT; ++i) {
		int j = 0;
		while (j < BOARD_WIDTH) {
			if (mBoard[i][j] != POS_FILLED) break;
			++j;
		}
		if (j == BOARD_WIDTH) {
			deleteLine(i);
			++deleteCount;
		}
	}
	switch (deleteCount) {
	case 0:
		return 0;
	case 1:
		return 40;
	case 2:
		return 100;
	case 3:
		return 300;
	case 4: 
		return 1200;
	}
}

// Checks if there are any blocks in the first row. If so, returns true.
bool Board::isGameOver() {
	for (int i = 0; i < BOARD_WIDTH; ++i) {
		if (mBoard[0][i] == POS_FILLED) return true;
	}
	return false;
}

void Board::showBoard() {
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		for (int j = 0; j < BOARD_WIDTH; j++) {
			if (mBoard[i][j] == POS_FILLED) cout << 1 << " ";
			else cout << 0 << " ";
		}
		cout << endl;
	}
	cout << "---------------------------------------------------------------------------";
	cout << endl;
}

// Initializes board, setting all positions to POS_FREE
void Board::initBoard() {
	for (int row = 0; row < BOARD_HEIGHT; ++row) {
		for (int col = 0; col < BOARD_WIDTH; ++col)
			mBoard[row][col] = POS_FREE;
	}
}

// Moves all lines down by one, overwriting pY, the line to be deleted.
void Board::deleteLine(int pY) {
	for (int i = pY; i > 0; --i) {
		for (int j = 0; j < BOARD_WIDTH; ++j)
			mBoard[i][j] = mBoard[i - 1][j];
	}
	cout << endl;
}