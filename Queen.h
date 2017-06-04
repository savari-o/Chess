#ifndef __QUEEN__
#define __QUEEN__

#include <iostream>

#include "Piece.h"
#include "Coord.h"

class Queen : public Piece {
public:
	Queen(char);
	~Queen();

	bool isMovable(Coord, Coord) override;
	std::vector<Coord> possibleMoves(Coord) override;
};

#endif