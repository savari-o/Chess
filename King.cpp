#include <iostream>
#include "King.h"

King::King(char color)
: Piece("King",
"     (O)    "
"  .-. ^ .-. "
" :   `.'   :"
" `.       .'"
"  )_.---._( "
"  `._____.' ", 0, color)
{}

King::~King() {

}

bool King::isMovable(Coord from, Coord to) {
	return (abs(from.x - to.x) <= 1 && abs(from.y - to.y) <= 1);
}

std::vector<Coord> King::possibleMoves(Coord pos) {
	std::vector<Coord> list;

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if ((i != 0 || j != 0) &&
				pos.x + i >= 0 && pos.y + j >= 0 &&
				pos.x + i < BOARD_WIDTH && pos.y + j < BOARD_HEIGHT) {
				list.push_back(Coord(pos.x + i, pos.y + j));
			}
		}
	}
	return (list);
}
