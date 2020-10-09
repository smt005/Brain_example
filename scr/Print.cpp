
#include "Print.h"

void log(const std::string text) {
	std::cout << text << std::endl;
}

void printResult(const std::vector<float>& inData, const std::vector<float>& outData) {
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

			if (index == 0 && outData[0] > 0.0) {
				text = ": forvard";
			}
			if (index == 0 && outData[0] < 0.0) {
				text = ": back";
			}

			if (index == 1 && outData[1] < 0.0) {
				text = ": left";
			}
			if (index == 1 && outData[1] > 0.0) {
				text = ": right";
			}

			if (index == 2 && outData[2] < 0.0) {
				text = ": rotate left";
			}
			if (index == 2 && outData[2] > 0.0) {
				text = ": rotate right";
			}

			if (index == 3 && outData[3] > 0.0) {
				text = ": action";
			}

			std::cout << "\t->\t[" << std::to_string(outData[index]) << ']' + text;
		}

		std::cout << std::endl;
	}

	std::cout << "--------------" << std::endl << std::endl;
}
