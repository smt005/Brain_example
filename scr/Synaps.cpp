
#include <iostream>

#include "Synaps.h"
#include "Neuron.h"

Synaps::Synaps()
	: _value(0.0f)
	, _neuron(nullptr)
{
}

Synaps::Synaps(Neuron* neuron, float value)
	: _value(value)
	, _neuron(neuron)
{
}

void Synaps::set(Neuron* neuron, float value) {
	_value = value;
	_neuron = neuron;
}

void Synaps::transmit(const float value) {

	float res = value * _value;
	_neuron->addValue(res);
}
