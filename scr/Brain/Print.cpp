
#include "Print.h"
#include "Brain.h"
#include <string>

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

	void stringResult(std::stringstream& textStream, const std::vector<double>& inData, const std::vector<double>& bestData, Brain& brain) {
		std::vector<double> outData;
		brain.action(inData, outData);

		if (outData.size() != bestData.size()) {
			textStream << "stringResult ERROR: outData.size() != bestData.size()" << std::endl;
			return;
		}

		size_t sizeIn = inData.size();
		size_t sizeOut = outData.size();
		size_t size = sizeIn > sizeOut ? sizeIn : sizeOut;

		for (size_t index = 0; index < size; ++index) {
			if (index < sizeIn) {
				textStream << '[' << (inData[index] > 0.5 ? "1" : "0") << ']';
			}
			else {
				textStream << "     ";
			}

			if (index < sizeOut) {

				double value = outData[index];

				//---
				std::string valueStr;
				if (outData[index] > 0.5) {
					valueStr = " 1";
				}
				else if (outData[index] < -0.5) {
					valueStr = "-1";
				}
				else {
					valueStr = " 0";
				}

				//---
				std::string bestValueStr;
				if (bestData[index] > 0.5) {
					bestValueStr = " 1";
				} else if (bestData[index] < -0.5) {
					bestValueStr = "-1";
				}
				else {
					bestValueStr = " 0";
				}

				std::string visibleValue; {
					visibleValue = '|';
					for (double i = 0.05; i < std::abs(value/100000); i = i + 0.05) {
						visibleValue += '.';
					}
				}

				//textStream << "\t->\t[" << outData[index] << "]\t[" << std::to_string(bestData[index]) << "]\t" << visibleValue << '\n';
				
				textStream << "\t->\t[" << outData[index] << "]\t[" << valueStr << '/' << bestValueStr << "] " << visibleValue << '\n';
				//textStream << " -> [" << outData[index] << "] [" << valueStr << '/' << bestValueStr << "] " << visibleValue << std::endl;

				/*double bestValue = bestData[index];
				double value = outData[index];

				//double error = 1.0 / (1.0 + std::abs( bestValue - value ));
				double error = bestValue / (bestValue + std::abs(bestValue - value) * 2.0);
				error = std::abs(error);
				error *= 100.0;
				error = floor(error * 100) / 100;

				std::string visibleError;
				if (error >=  0.0 && error <= 100.0) {
					visibleError = '|';

					for (double i = 5; i <= 100.0; i = i + 10.0) {
						if (i < error) {
							visibleError += '-';
						}
						else {
							visibleError += ' ';
						}
					}
					
					visibleError += '|';
				} else {
					visibleError = "| ERROR |";
				}

				std::string importantError;
				if (std::abs(bestValue) > 0.5) {
					importantError = " - " + visibleError;
				}

				double bestRoundValue = floor(bestData[index] * 10) / 10;
				std::string bestValueStr = std::to_string(bestRoundValue);

				//textStream << "\t->\t[" << outData[index] << "]\t/ [" << bestData[index] << "]\t\t->\t" << error << "%\t" << visibleError << text << importantError  << '\n';
				textStream << "\t->\t[" << outData[index] << "]\t/\t[" << bestValueStr << "]\t->\t" << error << "%\t" << visibleError << text << importantError << '\n';*/
			}
		}

		//textStream << "\n";
		textStream << std::endl;
	}
}
