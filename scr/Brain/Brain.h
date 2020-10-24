#pragma once

#include "Neuron.h"
#include <vector>
#include <memory>
#include <string>

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

		void load(const std::string& fileName);
		void save(const std::string& fileName);

	public:
		int generationInfo = 0;
		int itemIndexInfo = 0;
		double errorInfo = 0;
		double mattingInfo = 0;

	public:
		static BrainPtr loadBrain(const std::string& fileName = "brain.json");
		static void saveBrain(Brain& brain, const std::string& fileName = "brain.json");

	public:
		static double valueNeuronActivation;
		static double valueSynapsWeight;

	private:
		std::vector<Layer> _layers;
	};
}
