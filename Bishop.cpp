#include <iostream>
#include "Bishop.h"

Bishop::Bishop(char color)
: Piece("Bishop",
"     .-.    "
"    .' '.   "
"    (   )   "
"    `. .'   "
"     | |    "
"   '--^--'  ", 3, color)
{}

Bishop::~Bishop() {

}

bool Bishop::isMovable(Coord from, Coord to) {
	return (abs(from.x - to.x) == abs(from.y - to.y));
}

std::vector<Coord> Bishop::possibleMoves(Coord pos) {
	std::vector<Coord> list;

	for (int i = 0; i < BOARD_WIDTH && i < BOARD_HEIGHT; i++) {
		if (i != 0) {
			if (pos.x + i >= 0 && pos.x + i < BOARD_WIDTH &&
				pos.y + i >= 0 && pos.y + i < BOARD_HEIGHT) {
				list.push_back(Coord(pos.x + i, pos.y + i));
			}
			if (pos.x - i >= 0 && pos.x - i < BOARD_WIDTH &&
				pos.y - i >= 0 && pos.y - i < BOARD_HEIGHT) {
				list.push_back(Coord(pos.x - i, pos.y - i));
			}
			if (pos.x - i >= 0 && pos.x - i < BOARD_WIDTH &&
				pos.y + i >= 0 && pos.y + i < BOARD_HEIGHT) {
				list.push_back(Coord(pos.x - i, pos.y + i));
			}
			if (pos.x + i >= 0 && pos.x + i < BOARD_WIDTH &&
				pos.y - i >= 0 && pos.y - i < BOARD_HEIGHT) {
				list.push_back(Coord(pos.x + i, pos.y - i));
			}
		}
	}
	return (list);
}
