
#include "Print.h"
#include "Brain.h"

namespace NeuralNetwork {
	void printResult(const std::vector<double>& inData, const std::vector<double>& outData) {
		std::cout << std::endl;

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

				if (index == 0 && outData[0] > 0.9) {
					text = ": forvard";
				}
				if (index == 0 && outData[0] < -0.9) {
					text = ": back";
				}

				if (index == 1 && outData[1] < -0.9) {
					text = ": left";
				}
				if (index == 1 && outData[1] > 0.9) {
					text = ": right";
				}

				if (index == 2 && outData[2] < -0.9) {
					text = ": rotate left";
				}
				if (index == 2 && outData[2] > 0.9) {
					text = ": rotate right";
				}

				if (index == 3 && outData[3] > 0.9) {
					text = ": action";
				}

				std::cout << "\t->\t[" << std::to_string(outData[index]) << ']' + text;
			}

			std::cout << std::endl;
		}

		std::cout << "--------------" << std::endl << std::endl;
	}

	void printConfigPtr(Brain* brain) {

		if (!brain) {
			return;
		}

		std::cout << "BRAIN ---------------------------------------------------------------------------------------------" << std::endl;

		std::string tab;

		int iLayer = 0;
		for (Layer& layer : brain->getLayer()) {
			std::cout << tab << '[' << iLayer << "] ------------------------------------------------" << std::endl;

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

		std::cout << "------------------------------------------------------------------------------------------------" << std::endl;
	}

}
