
#include "Synaps.h"
#include "Neuron.h"

namespace NeuralNetwork {
	void Synaps::action(const double value) {
		if (_neuron) {
			_neuron->addValue(value * _weight);
		}
	}
}
