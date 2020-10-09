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
	int id[2] = {-1, -1};
	float valueAtivation = LONG_MAX;
	std::vector<SynapsContainer> synapses;

	void setId(int l, int i) {
		id[0] = l;
		id[1] = i;
	}

	void addNeuron(int layer_, int index_, float weightSynaps_) {
		synapses.emplace_back(layer_,index_, weightSynaps_);
	}
};

struct LayerContainer
{
	std::vector<NeuronContainer> neurons;
};

struct BrainContainer
{
	std::vector<LayerContainer> layers;
	void initDefault() {

		// Создание слоёв
		layers.resize(3);

		// Создание нейронов в слоях
		layers[0].neurons.resize(3);
		layers[1].neurons.resize(4);
		layers[2].neurons.resize(4);


		for (size_t iL = 0; iL < layers.size(); ++iL) {
			size_t iLnext = iL + 1;

			if (iLnext < layers.size()) {
				auto& layer = layers[iL];
				auto& layerNext = layers[iLnext];

				int iN = 0;
				for (auto& neuron : layer.neurons) {
					neuron.id[0] = iL;
					neuron.id[1] = iN;
					int iNNext = 0;
					for (auto& neuronNext : layerNext.neurons) {
						neuron.addNeuron(iLnext, iNNext, 0.0f);
						++iNNext;
					}

					++iN;
				}
			}
		}

		// Показать
		//show();
	}

	void show() {
		std::cout << "SAVE ---" << std::endl;

		int iLayer = 0;
		for (auto& layer : layers) {
			std::cout << '[' << iLayer << "] ----------------" << std::endl;

			int iN = 0;
			for (auto& neuron : layer.neurons) {
				std::cout << '[' << iLayer << iN << "](" << neuron.id[0] << neuron.id[1] << ") |";

				if (neuron.valueAtivation != LONG_MAX) {
					std::cout << neuron.valueAtivation << std::endl;
				}
				else {
					std::cout << 'X' << std::endl;
				}

				++iN;

				for (auto& synaps : neuron.synapses) {
					if (synaps.weightSynaps != 0.0f && synaps.layer != -1 && synaps.index != -1) {
						std::cout << "		--------- " << synaps.weightSynaps << "	--- [" << synaps.layer << synaps.index << ']' << std::endl;
					}
				}
			}

			++iLayer;
		}
	}
};

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
