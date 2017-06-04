#include <iostream>
#include "Queen.h"

Queen::Queen(char color)
: Piece("Queen",
"    o   o   "
"o   /\\ /\\  o"
"\\`.'  `  `'/"
" \\        / "
"  \\_.--._/  "
"  '.____.'  ", 10, color)
{}

Queen::~Queen() {

}

bool Queen::isMovable(Coord from, Coord to) {
	return (abs(from.x - to.x) == abs(from.y - to.y) || abs(from.x - to.x) * abs(from.y - to.y) == 0);
}

std::vector<Coord> Queen::possibleMoves(Coord pos) {
	std::vector<Coord> list;

	for (int i = 0; i < std::max(BOARD_WIDTH, BOARD_HEIGHT); i++) {
		if (i != 0 && i < BOARD_WIDTH && i < BOARD_HEIGHT) {
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
		if (i != pos.x && i < BOARD_WIDTH) {
			list.push_back(Coord(i, pos.y));
		}
		if (i != pos.y && i < BOARD_HEIGHT) {
			list.push_back(Coord(pos.x, i));
		}
	}

	return (list);
}
