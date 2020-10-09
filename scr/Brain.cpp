
#include "Brain.h"
#include <iostream>

Brain::Brain() {
}

Brain::~Brain() {

}

void Brain::init() {
	Layer in;
	in.emplace_back(0, 0);
	in.emplace_back(0, 1);
	in.emplace_back(0, 2);

	Layer hide;
	hide.emplace_back(1, 0);
	hide.emplace_back(1, 1);
	hide.emplace_back(1, 2);
	hide.emplace_back(1, 3);

	Layer out;
	out.emplace_back(2, 0);
	out.emplace_back(2, 1);
	out.emplace_back(2, 2);
	out.emplace_back(2, 3);

	_layers.push_back(in);
	_layers.push_back(hide);
	_layers.push_back(out);

	testConfig();
}

void Brain::init(BrainContainer& brainContainer) {
	_layers.clear();

	// Создание слоёв
	int clountLayer = brainContainer.layers.size();
	_layers.resize(clountLayer);

	// Создание нейронов
	for (size_t i = 0; i < clountLayer; ++i) {
		_layers[i].resize(brainContainer.layers[i].neurons.size());
	}

	// Присвоение параметров и связей
	for (size_t i = 0; i < clountLayer; ++i) {
		LayerContainer& layerC = brainContainer.layers[i];
		Layer& layer = _layers[i];

		for (size_t n = 0; n < layerC.neurons.size(); ++n) {
			NeuronContainer& neuronC = layerC.neurons[n];
			Neuron& neuron = layer[n];

			neuron._id[0] = neuronC.id[0];
			neuron._id[1] = neuronC.id[1];

			neuron._valueActivation = neuronC.valueAtivation;

			for (auto synaps : neuronC.synapses) {
				if (synaps.layer != -1) {
					Layer& layerSelect = _layers[synaps.layer];
					Neuron& neuronSelect = layerSelect[synaps.index];
					neuron.connectNeuron(&neuronSelect, synaps.weightSynaps);
				}
			}
		}
	}
}

void Brain::show() {
	
	std::cout << "BRAIN ---" << std::endl;

	int iLayer = 0;
	for (Layer& layer : _layers) {
		std::cout << '[' << iLayer << "] ----------------" << std::endl;

		int iN = 0;
		for (Neuron& neuron : layer) {
			std::cout << '[' << iLayer << iN << "](" << neuron._id[0] << neuron._id[1] << ") |";

			if (neuron._valueActivation != LONG_MAX) {
				std::cout << neuron._valueActivation << std::endl;
			}
			else {
				std::cout << 'X' << std::endl;
			}

			++iN;

			for (Synaps& synaps : neuron._synapses) {
				std::cout << "		--------- " << synaps._value << "	--- [" << synaps._neuron->_id[0] << synaps._neuron->_id[1] << ']' << std::endl;
			}
		}

		++iLayer;
	}
}

void Brain::testConfig() {
	// Входной слой в скрытый

	_layers[0][0]._valueActivation = 0.75;
	_layers[0][1]._valueActivation = 0.75;
	_layers[0][2]._valueActivation = 0.75;

	// 101
	_layers[0][0].connectNeuron(&_layers[1][0], 0.75f);
	_layers[0][2].connectNeuron(&_layers[1][0], 0.75f);

	// 010
	_layers[0][1].connectNeuron(&_layers[1][0], -1.5f);

	// 100
	_layers[0][0].connectNeuron(&_layers[1][1], -0.75f);

	// 001
	_layers[0][2].connectNeuron(&_layers[1][1], 0.75f);

	// 110
	_layers[0][0].connectNeuron(&_layers[1][2], -0.75f);
	_layers[0][1].connectNeuron(&_layers[1][2], -0.75f);

	// 011
	_layers[0][1].connectNeuron(&_layers[1][2], 0.75);
	_layers[0][2].connectNeuron(&_layers[1][2], 0.75f);

	// 111
	_layers[0][0].connectNeuron(&_layers[1][3], 0.334f);
	_layers[0][1].connectNeuron(&_layers[1][3], 0.334f);
	_layers[0][2].connectNeuron(&_layers[1][3], 0.334f);

	// Скрытый в выходной

	_layers[1][0]._valueActivation = 1.5;
	_layers[1][1]._valueActivation = 0.75;
	_layers[1][2]._valueActivation = 0.75;
	_layers[1][3]._valueActivation = 0.9;

	_layers[1][0].connectNeuron(&_layers[2][0], 1.0f);
	_layers[1][1].connectNeuron(&_layers[2][1], 1.0f);
	_layers[1][2].connectNeuron(&_layers[2][2], 1.0f);
	_layers[1][3].connectNeuron(&_layers[2][3], 1.0f);

}

void Brain::enter(const std::vector<float>& data) {
	size_t count = countInNeurons();
	if (count == 0) {
		return;
	}

	size_t index = 0;
	for (float value : data) {
		if (index < count) {
			_layers[0][index] = value;
		}
		++index;
	}
}

void Brain::update() {
	for (Layer& layer : _layers) {
		for (Neuron& neuron : layer) {
			neuron.update();
		}
	}
}

void Brain::result(std::vector<float>& data) {
	data.clear();
	size_t count = countOutNeurons();

	if (count == 0) {
		return;
	}

	data.reserve(count);

	size_t countLayers = _layers.size() - 1;
	for (Neuron& neuron : _layers[countLayers]) {
		data.push_back(neuron.getValue());
	}
}

void Brain::reset() {
	for (Layer& layer : _layers) {
		for (Neuron& neuron : layer) {
			neuron.resetValue();
		}
	}
}

BrainContainer Brain::save() {
	BrainContainer brainContainer;

	if (_layers.size() == 0) {
		return brainContainer;
	}

	brainContainer.initDefault();

	for (int iL = 0; iL < _layers.size(); ++iL) {
		auto& layer = _layers[iL];
		auto& layerCont = brainContainer.layers[iL];

		for (int iN = 0; iN < layer.size(); ++iN) {
			layerCont.neurons[iN].id[0] = layer[iN]._id[0];
			layerCont.neurons[iN].id[1] = layer[iN]._id[1];
			layerCont.neurons[iN].valueAtivation = layer[iN]._valueActivation;

			for (int iS = 0; iS < layer[iN]._synapses.size(); ++iS) {
				layerCont.neurons[iN].synapses[iS].weightSynaps = layer[iN]._synapses[iS]._value;
				layerCont.neurons[iN].synapses[iS].layer = layer[iN]._synapses[iS]._neuron->_id[0];
				layerCont.neurons[iN].synapses[iS].index = layer[iN]._synapses[iS]._neuron->_id[1];
			}
		}
	}

	return brainContainer;
}

size_t Brain::countInNeurons() {
	if (_layers.empty()) return 0;
	return _layers[0].size();
}

size_t Brain::countOutNeurons() {
	size_t countLayers = _layers.size();
	if (countLayers <= 1) {
		return 0;
	}
	--countLayers;
	return _layers[countLayers].size();
}
