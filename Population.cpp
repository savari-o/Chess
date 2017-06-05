#include "Population.h"

Population::Population(int size)
: _size(size)
{
	for (int i = 0; i < size; i++) {
		_popu.push_back(std::pair<ChessAI, int>(ChessAI(), 0));
	}
}

Population::~Population() {}

std::pair<ChessAI, int> Population::operator[](int n) const {
	return (_popu[n]);
}

std::pair<ChessAI, int> &Population::operator[](int n) {
	return (_popu[n]);
}

void Population::kill(int n) {
	std::sort(_popu.begin(), _popu.end(), [](const std::pair<ChessAI, int> &a, const std::pair<ChessAI, int> &b) -> bool {
		return (a.second > b.second);
	});
	// int size = _popu.size();
	for (int i = 0; i < n; i++) {
		_popu.pop_back();
		// int rnd = size / (rand() % size + 1) - 1;
		// _popu.erase(_popu.end() - 1 - rnd);
		// size--;
	}
}

void Population::reproduct() {
	int popu_size = _popu.size();
	for (int i = popu_size; i < _size; i++) {
		int rnd1 = popu_size / (rand() % popu_size + 1) - 1;
		int rnd2 = popu_size / (rand() % popu_size + 1) - 1;
		_popu.push_back(std::pair<ChessAI, int>(_popu[rnd1].first.merge(_popu[rnd2].first), 0));
	}
}

void Population::setScore(int n, int score) {
	_popu[n].second = score;
}

void Population::setSize(int size) {
	if (size < _size) {
		kill(_size - size);
	}
	_size = size;
	reproduct();
}
