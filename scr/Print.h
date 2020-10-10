
#pragma once

#include <iostream>
#include <string>
#include <vector>

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

			if (index == 0 && outData[0] > 0.5) {
				text = ": forvard";
			}
			if (index == 0 && outData[0] < -0.5) {
				text = ": back";
			}

			if (index == 1 && outData[1] < -0.5) {
				text = ": left";
			}
			if (index == 1 && outData[1] > 0.5) {
				text = ": right";
			}

			if (index == 2 && outData[2] < -0.5) {
				text = ": rotate left";
			}
			if (index == 2 && outData[2] > 0.5) {
				text = ": rotate right";
			}

			if (index == 3 && outData[3] > 0.5) {
				text = ": action";
			}

			std::cout << "\t->\t[" << std::to_string(outData[index]) << ']' + text;
		}

		std::cout << std::endl;
	}

	std::cout << "--------------" << std::endl << std::endl;
}

void printConfig(BrainContainer& bestBrain)
{
	// 0, 0, 0 - стоять
	{
		Brain brain;
		brain.init(bestBrain);

		std::vector<float> inData;
		inData.push_back(0.0f);
		inData.push_back(0.0f);
		inData.push_back(0.0f);

		brain.enter(inData);
		brain.update();

		std::vector<float> outData;
		brain.result(outData);

		printResult(inData, outData);
	}

	// 1, 0, 1 - вперёд
	{
		Brain brain;
		brain.init(bestBrain);

		std::vector<float> inData;
		inData.push_back(1.0f);
		inData.push_back(0.0f);
		inData.push_back(1.0f);

		brain.enter(inData);
		brain.update();

		std::vector<float> outData;
		brain.result(outData);

		printResult(inData, outData);
	}

	// 0, 1, 0 - назад
	{
		Brain brain;
		brain.init(bestBrain);

		std::vector<float> inData;
		inData.push_back(0.0f);
		inData.push_back(1.0f);
		inData.push_back(0.0f);

		brain.enter(inData);
		brain.update();

		std::vector<float> outData;
		brain.result(outData);

		printResult(inData, outData);
	}

	// 1, 0, 0 - смещение влево
	{
		Brain brain;
		brain.init(bestBrain);

		std::vector<float> inData;
		inData.push_back(1.0f);
		inData.push_back(0.0f);
		inData.push_back(0.0f);

		brain.enter(inData);
		brain.update();

		std::vector<float> outData;
		brain.result(outData);

		printResult(inData, outData);
	}

	// 0, 0, 1 - смещение вправо
	{
		Brain brain;
		brain.init(bestBrain);

		std::vector<float> inData;
		inData.push_back(0.0f);
		inData.push_back(0.0f);
		inData.push_back(1.0f);

		brain.enter(inData);
		brain.update();

		std::vector<float> outData;
		brain.result(outData);

		printResult(inData, outData);
	}

	// 1, 1, 0 - поворот на лево
	{
		Brain brain;
		brain.init(bestBrain);

		std::vector<float> inData;
		inData.push_back(1.0f);
		inData.push_back(1.0f);
		inData.push_back(0.0f);

		brain.enter(inData);
		brain.update();

		std::vector<float> outData;
		brain.result(outData);

		printResult(inData, outData);
	}

	// 0, 1, 1 - поворот на право
	{
		Brain brain;
		brain.init(bestBrain);

		std::vector<float> inData;
		inData.push_back(0.0f);
		inData.push_back(1.0f);
		inData.push_back(1.0f);

		brain.enter(inData);
		brain.update();

		std::vector<float> outData;
		brain.result(outData);

		printResult(inData, outData);
	}

	// 1, 1, 1 - действие
	{
		Brain brain;
		brain.init(bestBrain);

		std::vector<float> inData;
		inData.push_back(1.0f);
		inData.push_back(1.0f);
		inData.push_back(1.0f);

		brain.enter(inData);
		brain.update();

		std::vector<float> outData;
		brain.result(outData);

		printResult(inData, outData);
	}
}
