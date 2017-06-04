#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <cmath>

#include "Neuron.h"

Neuron::Neuron()
: Neuron(0, NULL)
{}

Neuron::Neuron(unsigned int nb_input, Neuron *input) {
	setInputs(nb_input, input);
	_output = 0;
}

Neuron::~Neuron()
{}

void	Neuron::setOutput(double output) {
	_output = output;
}

void	Neuron::setInputs(unsigned int nb_input, Neuron *input) {
	_input.clear();

	_input = std::vector<std::pair<Neuron *, double> >(
		nb_input,
		std::pair<Neuron *, double>(
			NULL,
			0
		)
	);

	for (unsigned int i = 0; i < nb_input; ++i) {
		_input[i].first = &(input[i]);
		_input[i].second = static_cast<double>(rand()) / RAND_MAX;
	}
	_nInput = nb_input;
}

void	Neuron::setInput(unsigned int n, Neuron *neuron, double value) {
	if (n < _nInput) {
		if (neuron != NULL) {
			_input[n].first = neuron;
		}
		if (value >= 0) {
			_input[n].second = value;
		}
		else {
			_input[n].second = static_cast<double>(rand()) / RAND_MAX;
		}
	}
}

double	Neuron::getInput(unsigned int n) {
	if (n < _nInput) {
		return (_input[n].second);
	}
	return (0);
}

Neuron	*Neuron::getNeuron(unsigned int n) {
	if (n < _nInput) {
		return (_input[n].first);
	}
	return (NULL);
}

unsigned int	Neuron::getNbInput() {
	return (_nInput);
}

double		Neuron::inputSum() {
	double	s;

	s = 0;
	for (unsigned int i = 0; i < _nInput; ++i) {
		s += _input[i].first->getOutput() * _input[i].second;
	}
	return (s);
}

double	Neuron::sigmoid(double x) {
	return (2 / (1 + exp(-x)) - 1);
}

double	Neuron::getOutput() {
	if (_nInput > 0) {
		_output = sigmoid(inputSum());
	}
	return (_output);
}

double	Neuron::search() {
	for (unsigned int i = 0; i < _nInput; ++i) {
		_input[i].first->search();
	}
	getOutput();
	return (_output);
}

/***************************************************************************************************/

void		formatNumber(double n)
{
	bool neg = false;

	if (n < 0)
	{
		neg = true;
		n = -n;
		std::cout << "-";
	}
	std::cout << static_cast<int>(n) % 10 << ".";
	std::cout << static_cast<int>(n * 10) % 10;
	std::cout << static_cast<int>(n * 100) % 10;
	std::cout << static_cast<int>(n * 1000) % 10;
	if (!neg)
		std::cout << static_cast<int>(n * 10000) % 10;
}

void	Neuron::diagram()
{
	std::vector<std::vector<Neuron *> >	network;
	Neuron						*n = this;
	unsigned int				i;
	unsigned int				max;

	debug("", false);

	max = 0;

	network.push_back(std::vector<Neuron *>(1, this));
	for (i = 1; n->_nInput > 0; ++i, n = n->_input[0].first)
	{
		unsigned int j;

		network.push_back(std::vector<Neuron *>(0, NULL));

		for (j = 0; j < n->_nInput; ++j)
		{
			network[i].push_back(n->_input[j].first);
		}
		if (max < n->_nInput)
			max = n->_nInput;
	}

	for (unsigned int j = 0; j < max; ++j)
	{
		const unsigned int lines = max + 2;

		for (unsigned int layer = 0; layer < i - 1; ++layer)
			std::cout << "                    |   ";
		std::cout << std::endl;
		for (unsigned int l = 0; l < lines; ++l)
		{
			for (int layer = static_cast<int>(i - 1); layer >= 0; --layer)
			{
				if (network[static_cast<size_t>(layer)].size() > j)
				{
					std::cout << "+";
					if (l == 0 || l == lines - 1)
						std::cout << "+++++++++++++++";
					else
					{
						std::cout << " ";
						if (network[static_cast<size_t>(layer)][j]->_input.size() > l - 1)
							formatNumber(network[static_cast<size_t>(layer)][j]->_input[l - 1].second);
						else
							std::cout << "      ";
						std::cout << " ";
						if (l == lines / 2)
							formatNumber(network[static_cast<size_t>(layer)][j]->_output);
						else
							std::cout << "      ";
						std::cout << " ";
					}
					std::cout << "+";
				}
				else
				{
					std::cout << "                 ";
				}
				if (static_cast<unsigned int>(layer) > 0)
					std::cout << "   |   ";
			}
			std::cout << std::endl;
		}
		for (unsigned int layer = 0; layer < i - 1; ++layer)
			std::cout << "                    |   ";
		std::cout << std::endl;
	}
}

void	Neuron::debug(std::string prefix, bool print)
{
	for (unsigned int i = 0; i < _nInput; ++i)
	{
		if (print)
		{
			std::cout << prefix << "input  \033[35m" << i << "\033[0m = \033[33m" << _input[i].second << "\033[0m" << std::endl;
			std::cout << prefix << "\033[36mneuron\033[0m \033[35m" << i << "\033[0m \033[31m{\033[0m" << std::endl;
		}
		_input[i].first->debug(prefix + "  ", print);
		if (print)
			std::cout << prefix << "\033[31m}\033[0m" << std::endl;
	}
	if (print)
		std::cout << prefix << "output = \033[33m" << getOutput() << "\033[0m" << std::endl;
	else
		getOutput();
}
