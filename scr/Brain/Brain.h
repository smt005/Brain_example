#pragma once

#include "Neuron.h"
#include <vector>
#include <memory>

namespace NeuralNetwork {
	class Brain;

	typedef std::vector<Neuron> Layer;
	typedef std::shared_ptr<Brain> BrainPtr;

	class Brain {
	public:
		Brain() {}
		Brain(const std::vector<size_t>& layersSetting, const bool set—onnections) {
			generate(layersSetting, set—onnections);
		}

		void generate(const std::vector<size_t>& layersSetting, const bool set—onnections);
		void action(const std::vector<double>& in, std::vector<double>& out);
		void resetBrain();
		void mutateValue(const double mutateValue);
		BrainPtr getCopy(const double mutateValue);

		inline std::vector<Layer>& getLayer() {
			return _layers;
		}

	public:
		int generationInfo;
		int itemIndexInfo;
		double errorInfo;

	public:
		static double valueNeuronActivation;
		static double valueSynapsWeight;

	private:
		std::vector<Layer> _layers;
	};
}
