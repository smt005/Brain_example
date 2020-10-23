
#include "Brain.h"

namespace NeuralNetwork {

	inline double random_f(const double& min = 0.0f, const double& max = 1.0f, const int& accuracy = 1000) {
		int var = rand() % accuracy;
		double k = static_cast<double>(var) / static_cast<double>(accuracy);
		double range = max - min;
		return min + range * k;
	}

	double Brain::valueNeuronActivation = 1.0;
	double Brain::valueSynapsWeight = 1.0;

	void Brain::generate(const std::vector<size_t>& layersSetting, const bool setСonnections) {
		_layers.clear();

		// Создание слоёв
		size_t countLayers = layersSetting.size();
		_layers.resize(countLayers);

		for (size_t indexLayer = 0; indexLayer < countLayers; ++indexLayer) {
			size_t countNeurons = layersSetting[indexLayer];
			_layers[indexLayer].resize(countNeurons);
		}

		if (!setСonnections) {
			// Инициализация нейронов
			for (size_t indexLayer = 0; indexLayer < countLayers; ++indexLayer) {
				Layer& layer = _layers[indexLayer];
				for (size_t iNeuron = 0; iNeuron < _layers[indexLayer].size(); ++iNeuron) {
					layer[iNeuron].set(
						indexLayer,
						iNeuron);
				}
			}
		} else {
			// Инициализация нейронов
			for (size_t indexLayer = 0; indexLayer < countLayers; ++indexLayer) {
				Layer& layer = _layers[indexLayer];
				for (size_t iNeuron = 0; iNeuron < _layers[indexLayer].size(); ++iNeuron) {
					layer[iNeuron].set(
						indexLayer,
						iNeuron,
						random_f(0.1f, valueNeuronActivation)
					);
				}
			}

			// Установка связей
			for (size_t indexLayer = 0; indexLayer < countLayers; ++indexLayer) {
				Layer& layer = _layers[indexLayer];

				size_t indexNextLayer = indexLayer + 1;
				if (indexNextLayer >= countLayers) {
					continue;
				}

				for (size_t iNeuron = 0; iNeuron < layer.size(); ++iNeuron) {
					Neuron& neuron = layer[iNeuron];

					Layer& nextLayer = _layers[indexNextLayer];
					for (size_t iSynapsNeuron = 0; iSynapsNeuron < nextLayer.size(); ++iSynapsNeuron) {
						Neuron& synapsNeuron = nextLayer[iSynapsNeuron];

						double weightSynaps = random_f(-valueSynapsWeight, valueSynapsWeight);
						if (weightSynaps == 0.0f) {
							continue;
						}

						neuron.addSynaps(&synapsNeuron, weightSynaps);
					}
				}
			}
		}
	}

	void Brain::action(const std::vector<double>& in, std::vector<double>& out) {
		size_t countLayers = _layers.size();
		size_t countData = in.size();

		if (countLayers < 2 || countData == 0) {
			return;
		}

		resetBrain();

		const size_t inLayer = 0;
		const size_t outLayer = _layers.size() - 1;

		// Ввести данные
		{
			Layer& neurons = _layers[inLayer];
			size_t countNeurons = neurons.size();

			for (size_t indexNeuron = 0; indexNeuron < countNeurons; ++indexNeuron) {
				if (indexNeuron <= (countData - 1)) {
					neurons[indexNeuron].addValue(in[indexNeuron]);
				}
			}
		}

		// Активировать нейроны
		for (size_t indexLayer = 0; indexLayer < outLayer; ++indexLayer) {
			Layer& neurons = _layers[indexLayer];
			size_t countNeurons = neurons.size();

			for (size_t indexNeuron = 0; indexNeuron < countNeurons; ++indexNeuron) {
				neurons[indexNeuron].action();
			}
		}

		// Получить данные
		if (outLayer > 0) {
			Layer& neurons = _layers[outLayer];
			size_t countNeurons = neurons.size();

			out.reserve(countNeurons);

			for (size_t indexNeuron = 0; indexNeuron < countNeurons; ++indexNeuron) {
				out.push_back(neurons[indexNeuron].getValue());
			}
		}
	}

	void Brain::resetBrain() {
		for (Layer& layer : _layers) {
			for (Neuron& neuron : layer) {
				neuron.resetValue();
			}
		}
	}

	void Brain::mutateValue(const double mutateValue) {
		for (auto& neurons: _layers) {
			for (auto& neuron : neurons) {
				double valueActivation = neuron.getValueActivation();
				valueActivation += valueActivation * random_f(-mutateValue, mutateValue);
				neuron.setValueActivation(valueActivation);

				for (auto& synaps : neuron.getSynapses()) {
					double weight = synaps.getWeight();
					weight += weight * random_f(-mutateValue, mutateValue);
					synaps.setWeight(weight);
				}
			}
		}
	}

	BrainPtr Brain::getCopy(const double mutateValue) {
		std::vector<size_t> layersSetting;

		layersSetting.resize(_layers.size());

		size_t i = 0;
		for (const auto neurons : _layers) {
			layersSetting[i] = neurons.size();
			++i;
		}

		BrainPtr newBrain = std::make_shared<Brain>(layersSetting, false);

		for (size_t iL = 0; iL < _layers.size(); ++iL) {
			auto& newLayers = newBrain->_layers;
			auto& newNeurons = newLayers[iL];
			auto& neurons = _layers[iL];

			for (size_t iN = 0; iN < neurons.size(); ++iN) {
				auto& newNeuron = newNeurons[iN];
				auto& neuron = neurons[iN];

				const double valueActivation = neuron.getValueActivation();
				newNeuron.setValueActivation(valueActivation);

				/*const int layerNum = newNeuron.getLayerNum();
				newNeuron.setLayerNum(layerNum);

				const int indexNum = newNeuron.getIndexNum();
				newNeuron.setIndexNum(indexNum);*/

				auto& newSynapses = newNeuron.getSynapses();
				auto& synapses = neuron.getSynapses();

				for (size_t iS = 0; iS < synapses.size(); ++iS) {
					auto& synaps = synapses[iS];

					auto weight = synaps.getWeight();
					auto& synapsNeyron = synaps.getNeuron();

					auto layer = synapsNeyron.getLayerNum();
					auto index = synapsNeyron.getIndexNum();

					Neuron& newSynapsNeuron = newLayers[layer][index];

					newNeuron.addSynaps(&newSynapsNeuron, weight);
				}
			}
		}

		if (mutateValue != 0.0) {
			newBrain->mutateValue(mutateValue);
		}

		return newBrain;
	}
}
