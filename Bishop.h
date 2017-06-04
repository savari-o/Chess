#ifndef __BISHOP__
#define __BISHOP__

#include <iostream>

#include "Piece.h"
#include "Coord.h"

class Bishop : public Piece {
public:
	Bishop(char);
	~Bishop();

	bool isMovable(Coord, Coord) override;
	std::vector<Coord> possibleMoves(Coord) override;
};

#endif
