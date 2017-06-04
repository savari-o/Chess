#include "Population.h"

Population::Population(int size)
: _size(size), _popu(std::vector<std::pair<ChessAI, int>>(size, std::pair<ChessAI, int>(ChessAI(), 0)))
{}

Population::~Population() {}

std::pair<ChessAI, int> Population::operator[](int n) const {
	return (_popu[n]);
}

std::pair<ChessAI, int> &Population::operator[](int n) {
	return (_popu[n]);
}

void Population::kill(int n) {
	std::sort(_popu.begin(), _popu.end(), [](const std::pair<ChessAI, int> &a, const std::pair<ChessAI, int> &b) -> bool {
		return (a.second < b.second);
	});
	for (int i = 0; i < n; i++) {
		_popu.pop_back(); // Modifier (kill par pourcentage de chance)
	}
}

void Population::reproduct() {
	int popu_size = _popu.size();
	for (int i = popu_size; i < _size; i++) {
		_popu.push_back(std::pair<ChessAI, int>(_popu[(rand() % popu_size)].first.merge(_popu[rand() % popu_size].first), 0));
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
