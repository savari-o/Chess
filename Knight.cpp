#include <iostream>
#include "Knight.h"

Knight::Knight(char color)
: Piece("Knight",
"     |\\.    "
"    /   '.  "
"   /_.'-  \\ "
"      /   | "
"     /____| "
"    `.____.'", 4, color)
{}

Knight::~Knight() {

}

bool Knight::isMovable(Coord from, Coord to) {
	return ((abs(from.x - to.x) == 2 && abs(from.y - to.y) == 1) ||
			(abs(from.y - to.y) == 2 && abs(from.x - to.x) == 1));
}

std::vector<Coord> Knight::possibleMoves(Coord pos) {
	std::vector<Coord> list;

	Coord arr[8] = {{-2, -1}, {-1, -2}, {2, -1}, {1, -2}, {-2, 1}, {-1, 2}, {2, 1}, {1, 2}};

	for (Coord move : arr) {
		if (pos.x + move.x >= 0 && pos.x + move.x < BOARD_WIDTH &&
			pos.y + move.y >= 0 && pos.y + move.y < BOARD_HEIGHT) {
			list.push_back(Coord(pos.x + move.x, pos.y + move.y));
		}
	}
	return (list);
}
