#include "game.h"
#include <random>
#include <iostream>
using namespace std;

Game::Game(Board* pBoard, Tetromino* pTetromino, IO* pIO, int pScreenHeight) {
	mBoard = pBoard;
	mTetromino = pTetromino;
	mIO = pIO;
	screenHeight = pScreenHeight;

	InitGame();
}

void Game::DrawScene() {
	DrawBoard();
	DrawPiece(posY, posX);
}

int Game::GetRand(int pA, int pB) {
	return pA + (rand() % pB - pA + 1);
}

void Game::InitGame() {
	// First Piece
	posY = mTetromino->initialYPos();
	posX = (BOARD_WIDTH / 2) - 2;

	// Next Piece
	mTetromino->chooseNextPiece();
}

void Game::GetNewPiece() {
	mTetromino->getNewPiece();
	mTetromino->chooseNextPiece();
	posY = mTetromino->initialYPos();
	posX = (BOARD_WIDTH / 2) - 2;
}

void Game::DrawPiece(int pY, int pX) {
	color mColor = GREEN;
	
	int mPixelsX = mBoard->getXPosInPixels(pX);
	int mPixelsY = mBoard->getYPosInPixels(pY);

	for (int i = 0; i < PIECE_BLOCKS; i++) {
		for (int j = 0; j < PIECE_BLOCKS; j++) {
			if (mTetromino->getBlockType(i, j) != 0) {
				mIO->DrawRectangle	(mPixelsX + j * BLOCK_SIZE, mPixelsY + i * BLOCK_SIZE,
									BLOCK_SIZE, BLOCK_SIZE, mColor, true);
			}
		}
	}

}

// *** maybe come back later ***
void Game::DrawBoard() {
	int mX1 = BOARD_POSITION - (BLOCK_SIZE * (BOARD_WIDTH / 2)) - 1; // Left border position
	int mX2 = BOARD_POSITION + (BLOCK_SIZE * (BOARD_WIDTH / 2));	 // Right border position
	int mY = MIN_VERTICAL_MARGIN * 3;								 // Bottom border position

	// Draw borders
	mIO->DrawRectangle(mX1 - BOARD_LINE_WIDTH, MIN_VERTICAL_MARGIN * 3, BOARD_LINE_WIDTH, (BLOCK_SIZE * BOARD_HEIGHT), BLUE, true);
	mIO->DrawRectangle(mX2, MIN_VERTICAL_MARGIN * 3, BOARD_LINE_WIDTH, (BLOCK_SIZE * BOARD_HEIGHT), BLUE, true);
	mIO->DrawRectangle(mX2 + (BOARD_LINE_WIDTH * 2), MIN_VERTICAL_MARGIN * 3, ((mX2 - mX1) - ((BLOCK_SIZE * BOARD_WIDTH) / 2) + BOARD_LINE_WIDTH), 
		(BLOCK_SIZE * 5), BLUE, false);

	mX1 += 1;
	for (int i = 0; i < BOARD_HEIGHT; i++)
	{
		for (int j = 0; j < BOARD_WIDTH; j++)
		{
			if (!mBoard->isFreeBlock(i, j)) {
				mIO->DrawRectangle(mX1 + (j * BLOCK_SIZE), (mY + (BLOCK_SIZE * BOARD_HEIGHT)) - ((BOARD_HEIGHT - i) * BLOCK_SIZE),
					BLOCK_SIZE, BLOCK_SIZE, RED, true);
			}
		}
	}
	for (int i = 0; i < PIECE_BLOCKS; i++) {
		for (int j = 0; j < PIECE_BLOCKS; j++) {
			if (tetrominos[mTetromino->next_piece][i][j] != 0) {
				mIO->DrawRectangle(mX2 + (BOARD_LINE_WIDTH * 2) + j * BLOCK_SIZE, (MIN_VERTICAL_MARGIN * 3 ) + i * BLOCK_SIZE,
					BLOCK_SIZE, BLOCK_SIZE, GREEN, true);
			}
		}
	}
}