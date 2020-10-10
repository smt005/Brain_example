
#pragma once

#include <vector>
#include <iostream>

#include "Neuron.h"

struct SynapsContainer
{
	SynapsContainer() {}
	SynapsContainer(int layer_, int index_, float weightSynaps_)
		: layer(layer_)
		, index(index_)
		, weightSynaps(weightSynaps_)
	{
	}

	int layer = -1;
	int index = -1;
	float weightSynaps = LONG_MAX;
};

struct NeuronContainer
{
	int id[2] = { -1, -1 };
	float valueAtivation = LONG_MAX;
	std::vector<SynapsContainer> synapses;

	void setId(int l, int i) {
		id[0] = l;
		id[1] = i;
	}

	void addNeuron(int layer_, int index_, float weightSynaps_) {
		synapses.emplace_back(layer_, index_, weightSynaps_);
	}
};

struct LayerContainer
{
	std::vector<NeuronContainer> neurons;
};

struct BrainContainer
{
	std::vector<LayerContainer> layers;
	void initDefault();
	void generate();
	void show();
};

void cross(const BrainContainer& bestBrain, BrainContainer& newBrain);