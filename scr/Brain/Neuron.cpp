
#include "Neuron.h"
#include <cmath>
#include <cmath>

namespace NeuralNetwork {
	void Neuron::action() {
		double valueActivation = funActivation();
		if (valueActivation > 0.0) {
			for (Synaps& synaps : _synapses) {
				synaps.action(valueActivation);
			}
		}

		_value = 0.0f;
	}

	double Neuron::funActivation() {
		if (_value > 0.0) {
			const double power = -_value + _valueActivation + 0.6;
			//const double power = -_value + 0.6;
			double returnValue = 1.0 / (1.0 + std::pow(1000000.0, power));
			returnValue += _value / 100.0;
			return returnValue;
		}
		else if (_value < 0.0) {
			const double power = -_value + _valueActivation + 0.6;
			//const double power = -_value + 0.6;
			double returnValue = (1.0 / (1.0 + std::pow(1000000.0, power))) - 1.0;
			returnValue += _value / 100.0;
			return returnValue;
		}

		return 0.0;
	}

}
