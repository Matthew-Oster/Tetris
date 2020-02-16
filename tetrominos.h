#pragma once
#include <algorithm>
#include <deque>
using namespace std;

extern int tetrominos[7][5][5];

class Tetromino {
public:
	Tetromino(const int pieceNum = 0) : piece_num(pieceNum) {
		int i = 0;
		int j = 0;
		for (auto& row : piece) {
			for (auto& e : row) {
				e = tetrominos[piece_num][i][j];
				++j;
			}
			j = 0;
			++i;
		}

		piece_history.resize(3);
		piece_history.push_back(piece_num);
	}

	void getNewPiece();
	void chooseNextPiece();
	int getBlockType(int pY, int pX);
	void rotate();
	void undoRotate();
	int initialYPos();
	void print(); //Test Function

	int next_piece;				// which of the 7 shapes the next tetromino is
	int piece_num;				// which of the 7 shapes the current tetromino is

private:
	
	deque<int> piece_history;	// history of 3 previous tetromino shapes
	int piece[5][5];			// matrix storing tetromino
};