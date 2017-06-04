#include <iostream>
#include "Pawn.h"

Pawn::Pawn(char color)
: Piece("Pawn",
"            "
"    .-\"-.   "
"    `. .'   "
"    .' '.   "
"   .'___'.  "
"   `-----'  ", 1, color)
{}

Pawn::~Pawn() {

}

bool Pawn::isMovable(Coord from, Coord to) {
	if (_color == 1) {
		if (from.x == to.x) {
			if (from.y == to.y + 1 || (!_hasMove && from.y == to.y + 2)) {
				return (true);
			}
		}
		else if (from.y == to.y + 1 && abs(from.x - to.x) <= 1) {
			return (true);
		}
	}
	else {
		if (from.x == to.x) {
			if (from.y == to.y - 1 || (!_hasMove && from.y == to.y - 2)) {
				return (true);
			}
		}
		else if (from.y == to.y - 1 && abs(from.x - to.x) <= 1) {
			return (true);
		}
	}
	return (false);
}

std::vector<Coord> Pawn::possibleMoves(Coord pos) {
	std::vector<Coord> list;

	if (_color == 1) {
		if (pos.y < BOARD_HEIGHT - 1) {
			list.push_back(Coord(pos.x, pos.y - 1));
			if (pos.x > 0) {
				list.push_back(Coord(pos.x - 1, pos.y - 1));
			}
			if (pos.x < BOARD_WIDTH - 1) {
				list.push_back(Coord(pos.x + 1, pos.y - 1));
			}
		}
		if (!_hasMove && pos.y < BOARD_HEIGHT - 2) {
			list.push_back(Coord(pos.x, pos.y - 2));
		}
	}
	else {
		if (pos.y > 0) {
			list.push_back(Coord(pos.x, pos.y + 1));
			if (pos.x > 0) {
				list.push_back(Coord(pos.x - 1, pos.y + 1));
			}
			if (pos.x < BOARD_WIDTH - 1) {
				list.push_back(Coord(pos.x + 1, pos.y + 1));
			}
		}
		if (!_hasMove && pos.y > 1) {
			list.push_back(Coord(pos.x, pos.y + 2));
		}
	}
	return (list);
}
