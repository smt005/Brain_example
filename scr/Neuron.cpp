
#include "Neuron.h"
#include <iostream>

Neuron::Neuron()
	: _value(0.0f)
	, _valueActivation(0.25f)
{
	_id[0] = -1;
	_id[1] = -1;
}

Neuron::Neuron(const int layer, const int index)
	: _value(0.0f)
	, _valueActivation(0.25f)
{
	_id[0] = layer;
	_id[1] = index;
}

Neuron::~Neuron() {

}

void Neuron::addValue(const float value) {

	_value += value;
}

float Neuron::getValue() {
	return _value;
}

void Neuron::connectNeuron(Neuron * neuron, const float valueSynaps) {
	_synapses.emplace_back(neuron, valueSynaps);
}

void Neuron::update() {
	if (_synapses.empty() || std::abs(_value) < std::abs(_valueActivation)) {
		return;
	}

	float outValue = _value;

	for (Synaps& synaps : _synapses) {
		synaps.transmit(outValue);
	}
}
