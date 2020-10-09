#pragma once

#include <vector>
#include <string>
#include "Synaps.h"

class Neuron
{
public:
	Neuron();
	Neuron(const int layer, const int index);
	~Neuron();

	int _id[2];

	inline float& operator=(const float value) {
		_value = value;
		return _value;
	}

	void addValue(const float value);
	float getValue();
	void resetValue() { _value = 0.0f; }

	void connectNeuron(Neuron* neuron, const float valueSynaps);

	void update();

private:
public:
	float _value;
	float _valueActivation;

	std::vector<Synaps> _synapses;
};

