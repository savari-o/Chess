#include <iostream>
#include <ctime>

#include "Board.h"
#include "ChessAI.h"
#include "Population.h"

#define POPULATION 500

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
	board.setAI(1, a.first);
	board.setAI(0, b.first);

	board.play(true);

	a.second = board.getScoreB();
	b.second = board.getScoreA();
}

int main(int argc, char *argv[]) {
	if (argc > 1) {
		srand(argv[1][0]);
	}
	else {
		srand(time(NULL));
	}

	Population p1(POPULATION);
	Population p2(POPULATION);

	std::vector<int> score1;
	std::vector<int> score2;
	for (int gen = 0; gen < 1000; gen++) {
		std::cout << "<# GENERATION n°" << gen << " #>" << std::endl;
		score1.clear();
		score2.clear();
		int size1 = 0;
		int size2 = 0;
		for (int i = 0; i < POPULATION - 1; i++) {
			runAI(p1[i], p2[i]);
			if (p1[i].second > 0) {
				while (size1 < p1[i].second) {
					score1.push_back(0);
					size1++;
				}
				score1[p1[i].second - 1]++;
			}
			if (p2[i].second > 0) {
				while (size2 < p2[i].second) {
					score2.push_back(0);
					size2++;
				}
				score2[p2[i].second - 1]++;
			}
		}
		for (int i = 0; i < size1 || i < size2; i++) {
			std::cout << "Score : " << i + 1;
			if (i < size1) {
				std::cout << "\t\tOccurences white : " << score1[i];
			}
			if (i < size2) {
				std::cout << "\t\tOccurences black : " << score2[i];
			}
			std::cout << std::endl;
		}
		p1.kill(POPULATION / 2);
		p2.kill(POPULATION / 2);
		p1.reproduct();
		p2.reproduct();
	}
	return (0);
}
