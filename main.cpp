#include <iostream>
#include <ctime>

#include "Board.h"
#include "ChessAI.h"
#include "Population.h"

#define POPULATION 1000

void runAI(std::pair<ChessAI, int> &a, std::pair<ChessAI, int> &b) {
	Board board("rkbqKbkr"
			"pppppppp"
			"        "
			"        "
			"        "
			"        "
			"pppppppp"
			"rkbqKbkr",
			"00000000"
			"00000000"
			"        "
			"        "
			"        "
			"        "
			"11111111"
			"11111111");
	board.setAI(0, a.first);
	board.setAI(1, b.first);

	board.play(true);

	a.second = board.getScoreA();
	b.second = board.getScoreB();
}

int main(int argc, char *argv[]) {
	if (argc > 1) {
		srand(argv[1][0]);
	}
	else {
		srand(time(NULL));
	}

	Population p(POPULATION);
	for (int i = 0; i < POPULATION - 1; i += 2) {
		std::cout << "Playing with n°" << i << " and n°" << i + 1;
		runAI(p[i], p[i + 1]);
		std::cout << "\t\tScore " << i << " : " << p[i].second << "\t\tScore " << i + 1 << " : " << p[i + 1].second << std::endl;
	}
	if (POPULATION % 2 == 1) {
		std::cout << "Playing with n°0 and n°" << POPULATION - 1 << std::endl;
		runAI(p[0], p[POPULATION - 1]);
		std::cout << "\t\tScore 0 : " << p[0].second << "\t\tScore " << POPULATION - 1 << " : " << p[POPULATION - 1].second << std::endl;
	}
	return (0);
}
