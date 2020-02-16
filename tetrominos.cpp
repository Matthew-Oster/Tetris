#include "tetrominos.h"
#include <iostream>
#include <algorithm>
#include <deque>
#include <random>
using namespace std;

int tetrominos[7][5][5] = {
	// Square
	{
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 2, 1, 0},
		{0, 0, 1, 1, 0},
		{0, 0, 0, 0, 0}
	},
	// I
	{
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0},
		{0, 1, 2, 1, 1},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0}
	},
	// L
	{
		{0, 0, 0, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 2, 0, 0},
		{0, 0, 1, 1, 0},
		{0, 0, 0, 0, 0}
	},
	// L mirrored
	{
		{0, 0, 0, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 2, 0, 0},
		{0, 1, 1, 0, 0},
		{0, 0, 0, 0, 0}
	},
	// Z
	{
		{0, 0, 0, 0, 0},
		{0, 0, 0, 1, 0},
		{0, 0, 2, 1, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0}
	},
	// Z mirrored
	{
		{0, 0, 0, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 0, 2, 1, 0},
		{0, 0, 0, 1, 0},
		{0, 0, 0, 0, 0}
	},
	// T
	{
		{0, 0, 0, 0, 0},
		{0, 0, 1, 0, 0},
		{0, 1, 2, 1, 0},
		{0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0}
	}
};

void Tetromino::getNewPiece() {
	if (piece_history.size() >= 4)
		piece_history.pop_front();
	piece_history.push_back(next_piece);
	piece_num = next_piece;
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j)
			piece[i][j] = tetrominos[next_piece][i][j];
	}
}

void Tetromino::chooseNextPiece() {
	while (find(piece_history.begin(), piece_history.end(), next_piece) != piece_history.end())
		next_piece = rand() % 7;
}

int Tetromino::getBlockType(int pY, int pX) {
	return piece[pY][pX];
}

void Tetromino::rotate() {
	if (piece_num == 0) return;
	for (int i = 0; i < 5; ++i) {
		for (int j = i + 1; j < 5; ++j) 
			swap(piece[i][j], piece[j][i]);
		swap(piece[i][0], piece[i][4]);
		swap(piece[i][1], piece[i][3]);
	}
}

void Tetromino::undoRotate() {
	for (int i = 0; i < 5; ++i) {
		swap(piece[i][0], piece[i][4]);
		swap(piece[i][1], piece[i][3]);
	}

	for (int i = 0; i < 5; ++i) {
		for (int j = i + 1; j < 5; ++j)
			swap(piece[i][j], piece[j][i]);
	}
}

int Tetromino::initialYPos() {
	int translate_up = 0;
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j)
			if (piece[i][j] != 0) return translate_up;
		--translate_up;
	}
}

// Test Function

void Tetromino::print() {
	for (int i = 0; i < 5; ++i) {
		for (int j = 0; j < 5; ++j)
			cout << piece[i][j];
		cout << endl;
	}
}
