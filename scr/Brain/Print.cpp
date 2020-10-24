
#include "Print.h"
#include "Brain.h"

namespace NeuralNetwork {

	void printError(Brain& brain) {
		std::cout << "brain config, ERROR: " << brain.errorInfo << ", id: [" << brain.generationInfo << ", " << brain.itemIndexInfo << "] matting:" << brain.mattingInfo << std::endl << std::endl;
	}

	void printResult(const std::vector<double>& inData, Brain& brain) {
		std::vector<double> outData;
		brain.action(inData, outData);
		printResult(inData, outData);
	}

	void printResult(const std::vector<double>& inData, const std::vector<double>& outData, const double error, const int generation, const int index) {
		if (error > 0.0) {
			std::cout << "brain config, ERROR: " << error << ", id: [" << generation << ", " << index << ']' << std::endl;
		}

		size_t sizeIn = inData.size();
		size_t sizeOut = outData.size();
		size_t size = sizeIn > sizeOut ? sizeIn : sizeOut;

		for (size_t index = 0; index < size; ++index) {
			if (index < sizeIn) {
				std::cout << '[' << std::to_string(inData[index]) << ']';
			}
			else {
				std::cout << "          ";
			}

			if (index < sizeOut) {

				std::string text;

				if (index == 0 && outData[0] > 0.5) {
					text = ": ------";
				}
				if (index == 0 && outData[0] < -0.5) {
					text = ": ------";
				}

				if (index == 1 && outData[1] < -0.5) {
					text = ": ------";
				}
				if (index == 1 && outData[1] > 0.5) {
					text = ": ------";
				}

				if (index == 2 && outData[2] < -0.5) {
					text = ": ------";
				}
				if (index == 2 && outData[2] > 0.5) {
					text = ": ------";
				}

				if (index == 3 && outData[3] > 0.5) {
					text = ": ------";
				}

				double roundValue = floor(outData[index] * 10) / 10;
				//double roundValue = round(outData[index]);
				std::cout << "\t->\t[" << std::to_string(outData[index]) << "]		[" << roundValue << ']' << text;
			}

			std::cout << std::endl;
		}

		std::cout << std::endl;
	}

	void printConfigPtr(Brain& brain) {
		std::cout << "brain config, ERROR: " << brain.errorInfo << ", id: [" << brain.generationInfo << ", " << brain.itemIndexInfo << ']' << std::endl;

		std::string tab;

		int iLayer = 0;
		for (Layer& layer : brain.getLayer()) {
			std::cout << tab << "layer: [" << iLayer << "] ---" << std::endl;

			int iN = 0;
			for (Neuron& neuron : layer) {
				std::cout << tab << '[' << iLayer << iN << "](" << neuron.getLayerNum() << neuron.getIndexNum() << ") |";

				if (neuron.getValueActivation() != LONG_MAX) {
					std::cout << tab << neuron.getValueActivation() << std::endl;
				}
				else {
					std::cout << tab << 'X' << std::endl;
				}

				++iN;

				for (Synaps& synaps : neuron.getSynapses()) {
					std::cout << tab << "		--------- " << synaps.getWeight() << "	--- [" << synaps.getNeuron().getLayerNum() << synaps.getNeuron().getIndexNum() << ']' << std::endl;
				}
			}

			++iLayer;
			tab += "\t";
		}

		std::cout << std::endl;
	}

}
