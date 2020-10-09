
#pragma once

class Neuron;

class Synaps
{
public:
	Synaps();
	Synaps(Neuron* neuron, float value);

	void set(Neuron* neuron, float value);
	void transmit(const float value);

private:
public:
	float _value = 0.0f;
	Neuron* _neuron = nullptr;
};
