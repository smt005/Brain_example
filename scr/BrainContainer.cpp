
#include "BrainContainer.h"

inline float random_f(const float& min = 0.0f, const float& max = 1.0f, const int& accuracy = 1000) {
	int var = rand() % accuracy;
	float k = static_cast<float>(var) / static_cast<float>(accuracy);
	float range = max - min;
	return min + range * k;
}

void BrainContainer::initDefault() {

	// Создание слоёв
	layers.resize(2);

	// Создание нейронов в слоях
	layers[0].neurons.resize(3);
	layers[1].neurons.resize(4);
	//layers[2].neurons.resize(4);


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

void BrainContainer::generate() {
	for (auto& layer : layers) {
		for (auto& neuron : layer.neurons) {
			neuron.valueAtivation = random_f(-5.0f, 5.0f);

			for (auto& synaps : neuron.synapses) {
				synaps.weightSynaps = random_f(-5.0f, 5.0f);
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

void cross(const BrainContainer& bestBrain, BrainContainer& newBrain) {
	for (int iL = 0; iL < newBrain.layers.size(); ++iL) {
		auto& layerBest = bestBrain.layers[iL];
		auto& layerNew = newBrain.layers[iL];

		for (int iN = 0; iN < layerNew.neurons.size(); ++iN) {
			auto& neyronBest = layerBest.neurons[iN];
			auto& neyronNew = layerNew.neurons[iN];
			float activValue = (neyronBest.valueAtivation + neyronNew.valueAtivation) * 0.5f;
			neyronNew.valueAtivation = activValue;

			for (int iS = 0; iS < neyronNew.synapses.size(); ++iS) {
				auto& synapsBest = neyronBest.synapses[iS];
				auto& synapsNew = neyronNew.synapses[iS];

				float weightValue = (synapsBest.weightSynaps + synapsNew.weightSynaps) * 0.5;
				synapsNew.weightSynaps = weightValue;
			}
		}
	}
}