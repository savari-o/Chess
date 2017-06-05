#ifndef __CHESSAI__
#define __CHESSAI__

#include <algorithm>
#include "Neuron.h"

#define IN_SIZE		64
#define HI_SIZE		64
#define HI_NBR		1
#define OUT_SIZE	4

class ChessAI {
public:
	ChessAI();
	~ChessAI();

	void set(int, int, Neuron);
	void setInputs(float *);
	void setOutput(int, Neuron);

	Neuron &get(int, int);
	Neuron &getInput(int);
	Neuron &getOutput(int);
	std::vector<float> getResult();

	ChessAI merge(ChessAI);

	ChessAI &operator=(ChessAI other);

private:
	Neuron _input[IN_SIZE];
	Neuron _hidden[HI_NBR][HI_SIZE];
	Neuron _output[OUT_SIZE];

};

#endif
