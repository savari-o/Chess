#ifndef __PAWN__
#define __PAWN__

#include <iostream>

#include "Piece.h"
#include "Coord.h"

class Pawn : public Piece {
public:
	Pawn(char);
	~Pawn();

	bool isMovable(Coord, Coord) override;
	std::vector<Coord> possibleMoves(Coord) override;
};

#endif