#ifndef __BOARD__
#define __BOARD__

#include <iostream>
#include <vector>

#include "Piece.h"
#include "Bishop.h"
#include "King.h"
#include "Knight.h"
#include "Pawn.h"
#include "Queen.h"
#include "Rook.h"

#include "Constants.h"
#include "ChessAI.h"

class Board {
public:
	Board(std::string, std::string);
	~Board();

	void print() const;
	Piece *get(int, int);
	void set(int, int, Piece *);

	void play(bool = false);

	bool move(int, int, int, int, bool);
	bool canMove(int);

	Coord getKingPos(int);
	bool isCheck(int);

	void setAI(int, ChessAI);
	int getScoreA();
	int getScoreB();
	void updatingScore();

private:
	Piece *_board[BOARD_WIDTH][BOARD_HEIGHT];
	ChessAI _a;
	ChessAI _b;
	int _scoreA;
	int _scoreB;
};

#endif
