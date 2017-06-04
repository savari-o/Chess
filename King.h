#ifndef __KING__
#define __KING__

#include <iostream>

#include "Piece.h"
#include "Coord.h"

class King : public Piece {
public:
	King(char);
	~King();

	bool isMovable(Coord, Coord) override;
	std::vector<Coord> possibleMoves(Coord) override;
};

#endif