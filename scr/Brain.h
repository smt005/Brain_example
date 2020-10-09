#pragma once

#include <vector>
#include <iostream>
#include <string>

#include "Neuron.h"
#include "BrainContainer.h"

class Brain
{
	typedef std::vector<Neuron> Layer;

public:
	Brain();
	~Brain();
	void init();
	void init(BrainContainer& brainContainer);
	void show();

	void testConfig();

	void enter(const std::vector<float>& data);
	void update();
	void result(std::vector<float>& data);
	void reset();

	BrainContainer save();

	size_t countInNeurons();
	size_t countOutNeurons();

private:
	std::vector<Layer> _layers;
};
