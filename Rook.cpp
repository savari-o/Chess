#include <iostream>
#include "Rook.h"

Rook::Rook(char color)
: Piece("Rook",
"    _   _   "
"   | |_| |  "
"   |     |  "
"   |     |  "
"  /_.---._\\ "
"  '._____.' ", 5, color)
{}

Rook::~Rook() {

}

bool Rook::isMovable(Coord from, Coord to) {
	return (abs(from.x - to.x) * abs(from.y - to.y) == 0);
}


std::vector<Coord> Rook::possibleMoves(Coord pos) {
	std::vector<Coord> list;

	for (int i = 0; i < BOARD_WIDTH; i++) {
		if (i != pos.x) {
			list.push_back(Coord(i, pos.y));
		}
	}
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		if (i != pos.y) {
			list.push_back(Coord(pos.x, i));
		}
	}
	return (list);
}
