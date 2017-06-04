#ifndef __POPULATION__
#define __POPULATION__

#include <iostream>
#include "ChessAI.h"

class Population {
public:
	Population(int);
	~Population();

	std::pair<ChessAI, int> operator[](int) const;
	std::pair<ChessAI, int> &operator[](int);

	void kill(int);
	void reproduct();

	void setScore(int, int);
	void setSize(int);

private:
	int _size;
	std::vector<std::pair<ChessAI, int>> _popu;
};

#endif
