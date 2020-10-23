#pragma once

#include "Synaps.h"
#include <vector>

namespace NeuralNetwork {
	class Neuron {
		friend Synaps;

	public:
		Neuron()
			: _layer(-1)
			, _index(-1)
			, _valueActivation(FLT_MAX)
			, _value(0.0f)
		{}
		
		Neuron(const int layer, const int index, const double valueActivation)
			: _layer(layer)
			, _index(index)
			, _valueActivation(valueActivation > 0.0 ? valueActivation : 0.0)
			, _value(0.0f)
		{}

		void set(const int layer, const int index) {
			_layer = layer;
			_index = index;
		}

		void set(const int layer, const int index, const double valueActivation) {
			_layer = layer;
			_index = index;
			_valueActivation = valueActivation;
		}

		inline void addSynaps(Neuron* neuron, const double weight) {
			if (weight != 0.0f) {
				_synapses.emplace_back(neuron, weight);
			}
		}

		inline void addValue(const double value) {
			_value += value;
		}

		inline const double getValue() {
			return _value;
		}

		inline const double getValueActivation() {
			return _valueActivation;
		}

		inline void setValueActivation(const double valueActivation) {
			_valueActivation = valueActivation;
		}

		inline const int getLayerNum() {
			return _layer;
		}

		inline void setLayerNum(const int value) {
			_layer = value;
		}

		inline const int getIndexNum() {
			return _index;
		}

		inline void setIndexNum(const int value) {
			_index = value;
		}

		inline std::vector<Synaps>& getSynapses() {
			return _synapses;
		}

		inline void resetValue() {
			_value = 0.0f;
		}

		void action();

	private:
		double funActivation();

	private:
		int _layer;
		int _index;
		std::vector<Synaps> _synapses;
		double _valueActivation;
		double _value;
	};
}
