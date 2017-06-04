#ifndef __ROOK__
#define __ROOK__

#include <iostream>

#include "Piece.h"
#include "Coord.h"

class Rook : public Piece {
public:
	Rook(char);
	~Rook();

	bool isMovable(Coord, Coord) override;
	std::vector<Coord> possibleMoves(Coord) override;
};

#endif