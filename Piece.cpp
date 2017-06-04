#include <iostream>
#include "Piece.h"

Piece::Piece(std::string name, std::string figure, int value, int color)
: _figure(figure), _name(name), _value(value), _color(color), _hasMove(false)
{}

Piece::~Piece() {

}

void Piece::print(int n) const {
	std::cout << _figure.substr(n * PIECE_WIDTH, PIECE_WIDTH);
}

int Piece::getColor() const {
	return (_color);
}

std::string Piece::getName() const {
	return (_name);
}

int Piece::getValue() const {
	return (_value);
}

void Piece::setMove(bool move) {
	_hasMove = move;
}
