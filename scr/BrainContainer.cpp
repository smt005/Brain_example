
#include "BrainContainer.h"

void BrainContainer::initDefault() {

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
}

void BrainContainer::show() {
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
