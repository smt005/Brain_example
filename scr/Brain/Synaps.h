#pragma once

namespace NeuralNetwork {
	class Neuron;

	class Synaps {
		friend Neuron;

	public:
		Synaps()
			: _neuron(nullptr)
			, _weight(0.0f)
		{}

		Synaps(Neuron* neuron, const double weight)
			: _neuron(neuron)
			, _weight(weight)
		{}

		Neuron& getNeuron() {
			return *_neuron; // TODO
		}
		const double getWeight() {
			return _weight;
		}

		void setWeight(const double value) {
			_weight = value;
		}

	private:
		void action(const double value);

	private:
		Neuron* _neuron;
		double _weight;
	};
}
