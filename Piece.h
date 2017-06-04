#ifndef __PIECE__
#define __PIECE__

#include <iostream>
#include <vector>

#include "Coord.h"
#include "Constants.h"

class Bishop;
class King;
class Knight;
class Pawn;
class Queen;
class Rook;

class Piece {
public:
	Piece(std::string, std::string, int, int);
	virtual ~Piece();

	virtual bool isMovable(Coord, Coord) = 0;
	virtual std::vector<Coord> possibleMoves(Coord) = 0;
	void print(int) const;
	int getColor() const;
	std::string getName() const;
	int getValue() const;
	void setMove(bool);

protected:
	std::string _figure;
	std::string _name;
	int _value;
	int _color;
	bool _hasMove;
};

#endif