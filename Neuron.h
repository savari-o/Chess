#ifndef __NEURON__
#define __NEURON__

#include <vector>

class Neuron {
public:
	Neuron();
	Neuron(unsigned int nb_input, Neuron *input);
	~Neuron();

	void			setOutput(double output);
	void			setInputs(unsigned int n, Neuron *neuron);
	void			setInput(unsigned int n, Neuron *neuron, double value = -1);

	double			getOutput();
	double			getInput(unsigned int n);
	Neuron			*getNeuron(unsigned int n);
	unsigned int	getNbInput();

	double			sigmoid(double x);
	double			inputSum();

	double			search();

	void			diagram();
	void			debug(std::string prefix, bool print);

private:
	std::vector<std::pair<Neuron *, double> >	_input;
	double										_output;
	unsigned int								_nInput;
};

#endif
