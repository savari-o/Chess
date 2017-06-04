#include <iostream>
#include "ChessAI.h"

ChessAI::ChessAI() {
	for (int i = 0; i < IN_SIZE; i++) {
		_input[i].setOutput(0);
	}

	for (int i = 0; i < HI_SIZE; i++) {
		_hidden[0][i].setInputs(IN_SIZE, _input);
		for (int j = 0; j < IN_SIZE; j++) {
			_hidden[0][i].setInput(j, NULL, (rand() % 1000) / 1000.0);
		}

		for (int j = 1; j < HI_NBR; j++) {
			_hidden[j][i].setInputs(HI_SIZE, _hidden[j - 1]);
			for (int k = 0; k < IN_SIZE; k++) {
				_hidden[j][i].setInput(k, NULL, (rand() % 1000) / 1000.0);
			}
		}
	}

	for (int i = 0; i < OUT_SIZE; i++) {
		_output[i].setInputs(HI_SIZE, _hidden[HI_NBR - 1]);
		for (int j = 0; j < HI_SIZE; j++) {
			_output[i].setInput(j, NULL, (rand() % 1000) / 1000.0);
		}
	}
}

ChessAI::~ChessAI() {

}

void ChessAI::set(int layer, int node, Neuron n) {
	if (layer >= 0 && layer < HI_NBR && node >= 0 && node < HI_SIZE) {
		_hidden[layer][node] = n;
		if (layer == 0) {
			_hidden[layer][node].setInputs(IN_SIZE, _input);
			for (int i = 0; i < IN_SIZE; i++) {
				_hidden[layer][node].setInput(i, NULL, n.getInput(i));
			}
		}
		else {
			_hidden[layer][node].setInputs(HI_SIZE, _hidden[layer - 1]);
			for (int i = 0; i < HI_SIZE; i++) {
				_hidden[layer][node].setInput(i, NULL, n.getInput(i));
			}
		}
	}
}

void ChessAI::setInputs(float *inputs) {
	for (int i = 0; i < IN_SIZE; i++) {
		_input[i].setOutput(inputs[i]);
	}
}

void ChessAI::setOutput(int node, Neuron n) {
	if (node >= 0 && node < OUT_SIZE) {
		_output[node] = n;
		_output[node].setInputs(HI_SIZE, _hidden[HI_NBR - 1]);
		for (int i = 0; i < HI_SIZE; i++) {
			_output[node].setInput(i, NULL, n.getInput(i));
		}
	}
}

Neuron &ChessAI::get(int layer, int node) {
	return (_hidden[layer][node]);
}

Neuron &ChessAI::getOutput(int node) {
	return (_output[node]);
}

std::vector<float> ChessAI::getResult() {
	std::vector<float> result;
	for (int i = 0; i < OUT_SIZE; i++) {
		result.push_back(_output[i].getOutput());
	}
	return (result);
}

ChessAI ChessAI::merge(ChessAI other) {
	ChessAI newIA;
	int mutating = 500;

	for (int i = 0; i < HI_SIZE; i++) {
		for (int j = 0; j < HI_NBR; j++) {
			if (j == 0) {
				for (int k = 0; k < IN_SIZE; k++) {
					float f = 0;
					if (rand() % mutating == 0) {
						std::cout << "Mutate : " << i << ";" << j << " : " << k << std::endl;
						f = (rand() % 1000) / 1000.0;
					}
					else if (rand() % 2 == 0) {
						f = get(j, i).getInput(k);
					}
					else {
						f = other.get(j, i).getInput(k);
					}
					newIA.get(j, i).setInput(k, NULL, f);
				}
			}
			else {
				for (int k = 0; k < HI_SIZE; k++) {
					float f = 0;
					if (rand() % mutating == 0) {
						std::cout << "Mutate : " << i << ";" << j << " : " << k << std::endl;
						f = (rand() % 1000) / 1000.0;
					}
					else if (rand() % 2 == 0) {
						f = get(j, i).getInput(k);
					}
					else {
						f = other.get(j, i).getInput(k);
					}
					newIA.get(j, i).setInput(k, NULL, f);
				}
			}
		}
	}
	for (int i = 0; i < OUT_SIZE; i++) {
		for (int j = 0; j < HI_SIZE; j++) {
			float f = 0;
			if (rand() % mutating == 0) {
				std::cout << "Mutate : " << i << " : " << j << std::endl;
				f = (rand() % 1000) / 1000.0;
			}
			else if (rand() % 2 == 0) {
				f = getOutput(i).getInput(j);
			}
			else {
				f = other.getOutput(i).getInput(j);
			}
			newIA.getOutput(i).setInput(j, NULL, f);
		}
	}
	return (newIA);
}
