#include <iostream>
#include "Board.h"

Board::Board(std::string tmp, std::string color)
: _scoreA(0), _scoreB(0)
{
	for (int i = 0; i < BOARD_WIDTH; i++) {
		for (int j = 0; j < BOARD_HEIGHT; j++) {
			switch (tmp[i + (j * BOARD_WIDTH)]) {
				case 'b':
					_board[i][j] = new Bishop(color[i + (j * BOARD_WIDTH)] - '0');
					break;
				case 'k':
					_board[i][j] = new Knight(color[i + (j * BOARD_WIDTH)] - '0');
					break;
				case 'r':
					_board[i][j] = new Rook(color[i + (j * BOARD_WIDTH)] - '0');
					break;
				case 'q':
					_board[i][j] = new Queen(color[i + (j * BOARD_WIDTH)] - '0');
					break;
				case 'K':
					_board[i][j] = new King(color[i + (j * BOARD_WIDTH)] - '0');
					break;
				case 'p':
					_board[i][j] = new Pawn(color[i + (j * BOARD_WIDTH)] - '0');
					break;
				default:
					_board[i][j] = nullptr;
			}
		}
	}
}

Board::~Board() {
	for (int i = 0; i < BOARD_WIDTH; i++) {
		for (int j = 0; j < BOARD_HEIGHT; j++) {
			if (_board[i][j] != nullptr) {
				delete _board[i][j];
			}
		}
	}
}

Piece *Board::get(int x, int y) {
	return (_board[x][y]);
}

void Board::set(int x, int y, Piece *p) {
	if (_board[x][y] != nullptr) {
		delete _board[x][y];
	}
	_board[x][y] = p;
}

void Board::print() const {
	std::cout << "\033[0;0H" BG_COLOR;
	for (int i = 0; i < BOARD_HEIGHT; i++) {
		std::cout << ' ';
		for (int j = 0; j < (PIECE_WIDTH + 3) * BOARD_WIDTH + 1; j++) {
			std::cout << ((j % (PIECE_WIDTH + 3) == 0) ? '+' : '-');
		}
		std::cout << "\033[K" << std::endl;
		for (int k = 0; k < PIECE_HEIGHT; k++) {
			for (int j = 0; j < BOARD_WIDTH; j++) {
				std::string bg = ((i % 2 == j % 2) ? BG_COLOR_ODD : BG_COLOR_EVEN);
				std::cout << " " BG_COLOR "|" << bg << " ";
				if (_board[j][i] != nullptr) {
					std::cout << ((_board[j][i]->getColor() == 0) ? FG_COLOR_1 : FG_COLOR_2);
					_board[j][i]->print(k);
				}
				else {
					for (int l = 0; l < PIECE_WIDTH; l++) {
						std::cout << ' ';
					}
				}
				std::cout << FG_COLOR;
			}
			std::cout << " " BG_COLOR "|" << "\033[K" << std::endl;
		}
	}
	std::cout << ' ';
	for (int i = 0; i < (PIECE_WIDTH + 3) * BOARD_WIDTH + 1; i++) {
		std::cout << ((i % (PIECE_WIDTH + 3) == 0) ? '+' : '-');
	}
	std::cout << BG_DEFAULT FG_DEFAULT << std::endl;
}

bool Board::move(int fx, int fy, int tx, int ty, bool playerMove = true) {
	if (_board[fx][fy]->isMovable(Coord(fx, fy), Coord(tx, ty))) {
		if (_board[fx][fy]->getName() != "Knight") {
			int absX = (fx == tx) ? 0 : (tx - fx) / abs(fx - tx);
			int absY = (fy == ty) ? 0 : (ty - fy) / abs(fy - ty);
			int dif = std::max(abs(fx - tx), abs(fy - ty));
			for (int i = 1; i < dif; i++) {
				if (_board[fx + i * absX][fy + i * absY] != nullptr) {
					return (false);
				}
			}
		}
		if (_board[fx][fy]->getName() == "Pawn") {
			if (_board[tx][ty] != nullptr) {
				if (fx == tx) {
					return (false);
				}
			}
			else if (fx != tx) {
				return (false);
			}
			if (playerMove) {
				int color = _board[fx][fy]->getColor();
				if ((color == 1 && ty == 0) ||
					(color == 0 && ty == BOARD_HEIGHT - 1))
				{
					Piece *p = new Queen(color);
					delete _board[fx][fy];
					_board[fx][fy] = p;
				}
			}
		}
		if (playerMove) {
			if (_board[tx][ty] != nullptr) {
				delete _board[tx][ty];
			}
			_board[fx][fy]->setMove(true);
		}
		_board[tx][ty] = _board[fx][fy];
		_board[fx][fy] = nullptr;
		return (true);
	}
	return (false);
}

Coord Board::getKingPos(int color) {
	for (int i = 0; i < BOARD_WIDTH; i++) {
		for (int j = 0; j < BOARD_HEIGHT; j++) {
			if (_board[i][j] != nullptr &&
				_board[i][j]->getName() == "King" &&
				_board[i][j]->getColor() == color) {
				return (Coord(i, j));
			}
		}
	}
	return (Coord(-1, -1));
}

bool Board::isCheck(int color) {
	Coord king = getKingPos(color);
	if (king.x < 0 || king.y < 0) {
		return (true);
	}
	for (int i = 0; i < BOARD_WIDTH; i++) {
		for (int j = 0; j < BOARD_HEIGHT; j++) {
			if (_board[i][j] != nullptr &&
				_board[i][j]->getColor() != color &&
				_board[i][j]->isMovable(Coord(i, j), Coord(king.x, king.y)))
			{
				Piece *tmp = _board[king.x][king.y];
				if (move(i, j, king.x, king.y, false)) {
					_board[i][j] = _board[king.x][king.y];
					_board[king.x][king.y] = tmp;
					return (true);
				}
			}
		}
	}
	return (false);
}

bool Board::canMove(int color) {
	for (int i = 0; i < BOARD_WIDTH; i++) {
		for (int j = 0; j < BOARD_HEIGHT; j++) {
			if (_board[i][j] != nullptr &&
				_board[i][j]->getColor() == color) {
				for (Coord pos : _board[i][j]->possibleMoves(Coord(i, j))) {
					if (pos.x >= 0 && pos.x < BOARD_WIDTH && pos.y >= 0 && pos.y < BOARD_HEIGHT) {
						Piece *tmp = _board[pos.x][pos.y];
						if ((_board[pos.x][pos.y] == nullptr || _board[pos.x][pos.y]->getColor() != color) && move(i, j, pos.x, pos.y, false)) {
							if (!isCheck(color)) {
								_board[i][j] = _board[pos.x][pos.y];
								_board[pos.x][pos.y] = tmp;
								return (true);
							}
							_board[i][j] = _board[pos.x][pos.y];
							_board[pos.x][pos.y] = tmp;
						}
					}
				}
			}
		}
	}
	return (false);
}

void Board::play(bool trainIA) {
	std::string action;

	int fx, fy, tx, ty;
	int color = 1;

	for (int i = 0; i < 100 && fx != 16; i++) {
		if (!trainIA) {
			print();
		}
		if (!canMove(color)) {
			std::cout << (isCheck(color) ? "Checkmate ! " : "Stalemate ! ") << ((color == 0) ? "Orange" : "Red") << " won !\033[K" << std::endl;
			return ;
		}
		if (isCheck(color)) {
			if (!trainIA) {
				std::cout << "Check\033[K" << std::endl;
			}
		}
		if (!trainIA) {
			std::cout << ((color == 0) ? "Red" : "Orange") << "'s turn : \033[K";
			std::cin >> action;
		}
		else {
			ChessAI &player = (color == 0 ? _a : _b);
			float board[IN_SIZE];
			for (int i = 0; i < BOARD_WIDTH; i++) {
				for (int j = 0; j < BOARD_HEIGHT; j++) {
					if (_board[i][j] != nullptr) {
						// TODO : modifier "_board[i][j]->getColor() == 0" avec "_board[i][j]->getColor() == COULEUR_DE_L'IA"
						board[i * BOARD_HEIGHT + j] = (_board[i][j]->getName() == "King" ? 1.0 : _board[i][j]->getValue() / 20.0) * (_board[i][j]->getColor() == 0 ? 1 : -1);
					}
					else {
						board[i * BOARD_HEIGHT + j] = 0;
					}
				}
			}
			player.setInputs(board);
			std::vector<float> result = player.getResult();
			action = "a1a1";
			action[0] = int((result[0] + 1) / 2 * (BOARD_WIDTH)) + 'a';
			action[1] = int((result[1] + 1) / 2 * (BOARD_HEIGHT)) + '1';
			action[2] = int((result[2] + 1) / 2 * (BOARD_WIDTH)) + 'a';
			action[3] = int((result[3] + 1) / 2 * (BOARD_HEIGHT)) + '1';
		}
		fx = tolower(action[0]) - 'a';
		fy = action[1] - '1';
		tx = tolower(action[2]) - 'a';
		ty = action[3] - '1';

		std::cout << "Action : " << action << std::endl;

		if (fx >= 0 && fx < BOARD_WIDTH && fy >= 0 && fy < BOARD_HEIGHT &&
			tx >= 0 && tx < BOARD_WIDTH && ty >= 0 && ty < BOARD_HEIGHT) {
			if (_board[fx][fy] != nullptr && _board[fx][fy]->getColor() == color) {
				if (_board[tx][ty] == nullptr || _board[fx][fy]->getColor() != _board[tx][ty]->getColor()) {
					Piece *tmp = _board[tx][ty];
					if (move(fx, fy, tx, ty, false)) {
						if (!isCheck(color)) {
							std::cout << "moved" << std::endl;
							_board[fx][fy] = _board[tx][ty];
							_board[tx][ty] = tmp;
							move(fx, fy, tx, ty);

							color == 0 ? _scoreA++ : _scoreB++;
							color = (color == 0) ? 1 : 0;
						}
						else {
							_board[fx][fy] = _board[tx][ty];
							_board[tx][ty] = tmp;
						}
					}
				}
			}
		}
	}

	updatingScore();
}

void Board::updatingScore() {
	for (int i = 0; i < BOARD_WIDTH; i++) {
		for (int j = 0; j < BOARD_HEIGHT; j++) {
			if (_board[i][j] != nullptr) {
				if (_board[i][j]->getColor() == 0) {
					_scoreA += _board[i][j]->getValue();
				}
				else if (_board[i][j]->getColor() == 1) {
					_scoreB += _board[i][j]->getValue();
				}
			}
		}
	}
}

void Board::setAI(int n, ChessAI ai) {
	if (n == 0) {
		_a = ai;
	}
	else if (n == 1) {
		_b = ai;
	}
}

int Board::getScoreA() {
	return (_scoreA);
}

int Board::getScoreB() {
	return (_scoreB);	
}
