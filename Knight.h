#ifndef __KNIGHT__
#define __KNIGHT__

#include <iostream>

#include "Piece.h"
#include "Coord.h"

class Knight : public Piece {
public:
	Knight(char);
	~Knight();

	bool isMovable(Coord, Coord) override;
	std::vector<Coord> possibleMoves(Coord) override;
};

#endif