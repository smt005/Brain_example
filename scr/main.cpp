
#include <iostream>
#include <string>

#include "Brain.h"
#include "Neuron.h"

inline void log(const std::string text) {
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

float getRes(Brain& brain) {
	float globalValue = 0.0f;

	// 0, 0, 0 - стоять
	{
		float value = 100.0f;
		brain.reset();

		std::vector<float> inData;
		inData.push_back(0.0f);
		inData.push_back(0.0f);
		inData.push_back(0.0f);

		brain.enter(inData);
		brain.update();

		std::vector<float> outData;
		brain.result(outData);
		printResult(inData, outData);

		if (outData[0] != 0.0f) {
			value -= 25.0f;
		}
		if (outData[1] != 0.0f) {
			value -= 25.0f;
		}
		if (outData[2] != 0.0f) {
			value -= 25.0f;
		}
		if (outData[3] != 0.0f) {
			value -= 25.0f;
		}
		globalValue += value;
	}

	// 1, 0, 1 - вперёд
	{
		float value = 100.0f;
		brain.reset();

		std::vector<float> inData;
		inData.push_back(1.0f);
		inData.push_back(0.0f);
		inData.push_back(1.0f);

		brain.enter(inData);
		brain.update();

		std::vector<float> outData;
		brain.result(outData);
		printResult(inData, outData);

		if (outData[0] <= 0.0f) {
			value -= 25.0f;
		}
		if (outData[1] != 0.0f) {
			value -= 25.0f;
		}
		if (outData[2] != 0.0f) {
			value -= 25.0f;
		}
		if (outData[3] != 0.0f) {
			value -= 25.0f;
		}
		globalValue += value;
	}


	// 0, 1, 0 - назад
	{
		float value = 100.0f;
		brain.reset();

		std::vector<float> inData;
		inData.push_back(0.0f);
		inData.push_back(1.0f);
		inData.push_back(0.0f);

		brain.enter(inData);
		brain.update();

		std::vector<float> outData;
		brain.result(outData);
		printResult(inData, outData);

		if (outData[0] >= 0.0f) {
			value -= 25.0f;
		}
		if (outData[1] != 0.0f) {
			value -= 25.0f;
		}
		if (outData[2] != 0.0f) {
			value -= 25.0f;
		}
		if (outData[3] != 0.0f) {
			value -= 25.0f;
		}
		globalValue += value;
	}

	// 1, 0, 0 - смещение влево
	{
		float value = 100.0f;
		brain.reset();

		std::vector<float> inData;
		inData.push_back(1.0f);
		inData.push_back(0.0f);
		inData.push_back(0.0f);

		brain.enter(inData);
		brain.update();

		std::vector<float> outData;
		brain.result(outData);
		printResult(inData, outData);

		if (outData[0] != 0.0f) {
			value -= 25.0f;
		}
		if (outData[1] >= 0.0f) {
			value -= 25.0f;
		}
		if (outData[2] >= 0.0f) {
			value -= 25.0f;
		}
		if (outData[3] != 0.0f) {
			value -= 25.0f;
		}
		globalValue += value;
	}

	// 1, 1, 0 - поворот на лево
	{
		float value = 100.0f;
		brain.reset();

		std::vector<float> inData;
		inData.push_back(1.0f);
		inData.push_back(1.0f);
		inData.push_back(0.0f);

		brain.enter(inData);
		brain.update();

		std::vector<float> outData;
		brain.result(outData);
		printResult(inData, outData);

		if (outData[0] != 0.0f) {
			value -= 25.0f;
		}
		if (outData[1] >= 0.0f) {
			value -= 25.0f;
		}
		if (outData[2] >= 0.0f) {
			value -= 25.0f;
		}
		if (outData[3] != 0.0f) {
			value -= 25.0f;
		}
		globalValue += value;
	}

	// 0, 0, 1 - смещение влево
	{
		float value = 100.0f;
		brain.reset();

		std::vector<float> inData;
		inData.push_back(0.0f);
		inData.push_back(0.0f);
		inData.push_back(1.0f);

		brain.enter(inData);
		brain.update();

		std::vector<float> outData;
		brain.result(outData);
		printResult(inData, outData);

		if (outData[0] != 0.0f) {
			value -= 25.0f;
		}
		if (outData[1] <= 0.0f) {
			value -= 25.0f;
		}
		if (outData[2] <= 0.0f) {
			value -= 25.0f;
		}
		if (outData[3] != 0.0f) {
			value -= 25.0f;
		}
		globalValue += value;
	}

	// 0, 1, 1 - поворот на право
	{
		float value = 100.0f;
		brain.reset();

		std::vector<float> inData;
		inData.push_back(0.0f);
		inData.push_back(1.0f);
		inData.push_back(1.0f);

		brain.enter(inData);
		brain.update();

		std::vector<float> outData;
		brain.result(outData);
		printResult(inData, outData);

		if (outData[0] != 0.0f) {
			value -= 25.0f;
		}
		if (outData[1] <= 0.0f) {
			value -= 25.0f;
		}
		if (outData[2] <= 0.0f) {
			value -= 25.0f;
		}
		if (outData[3] != 0.0f) {
			value -= 25.0f;
		}
		globalValue += value;
	}

	// 1, 1, 1 - действие
	{
		float value = 100.0f;
		brain.reset();

		std::vector<float> inData;
		inData.push_back(1.0f);
		inData.push_back(1.0f);
		inData.push_back(1.0f);

		brain.enter(inData);
		brain.update();

		std::vector<float> outData;
		brain.result(outData);
		printResult(inData, outData);

		if (outData[0] != 0.0f) {
			value -= 25.0f;
		}
		if (outData[1] != 0.0f) {
			value -= 25.0f;
		}
		if (outData[2] != 0.0f) {
			value -= 25.0f;
		}
		if (outData[3] <= 0.0f) {
			value -= 25.0f;
		}
		globalValue += value;
	}

	return (globalValue / 8.0f);
}

int main() {

	log("BEGIN");

	/*
	0, 0, 0 - стоять
	1, 0, 1 - вперёд
	0, 1, 0 - назад
	1, 0, 0 - смещение влево
	0, 0, 1 - смещение вправо
	1, 1, 0 - поворот на лево
	0, 1, 1 - поворот на право
	1, 1, 1 - действие
	*/

	Brain brain;

	if (false) {
		brain.init();
		brain.show();
	} else {
		BrainContainer brainContainer;

		brainContainer.layers.resize(3);
		brainContainer.layers[0].neurons.resize(3);
		brainContainer.layers[1].neurons.resize(4);
		brainContainer.layers[2].neurons.resize(4);

		brainContainer.layers[0].neurons[0].setId(0, 0);
		brainContainer.layers[0].neurons[1].setId(0, 1);
		brainContainer.layers[0].neurons[2].setId(0, 2);

		brainContainer.layers[1].neurons[0].setId(1, 0);
		brainContainer.layers[1].neurons[1].setId(1, 1);
		brainContainer.layers[1].neurons[2].setId(1, 2);
		brainContainer.layers[1].neurons[3].setId(1, 3);

		brainContainer.layers[2].neurons[0].setId(2, 0);
		brainContainer.layers[2].neurons[1].setId(2, 1);
		brainContainer.layers[2].neurons[2].setId(2, 2);
		brainContainer.layers[2].neurons[3].setId(2, 3);

		// _neurons[0][0]._valueActivation = 0.75;
		// _neurons[0][1]._valueActivation = 0.5;
		// _neurons[0][2]._valueActivation = 0.7;

		brainContainer.layers[0].neurons[0].valueAtivation = 0.75;
		brainContainer.layers[0].neurons[1].valueAtivation = 0.75;
		brainContainer.layers[0].neurons[2].valueAtivation = 0.75;

		// 101
		//_neurons[0][0].connectNeuron(&_neurons[1][0], 0.75f);
		//_neurons[0][2].connectNeuron(&_neurons[1][0], 0.75f);

		brainContainer.layers[0].neurons[0].addNeuron(1, 0, 0.75);
		brainContainer.layers[0].neurons[2].addNeuron(1, 0, 0.75);

		// 010
		//_neurons[0][1].connectNeuron(&_neurons[1][0], -1.5f);

		brainContainer.layers[0].neurons[1].addNeuron(1, 0, -1.5);

		// 100
		//_neurons[0][0].connectNeuron(&_neurons[1][1], -0.5f);

		brainContainer.layers[0].neurons[0].addNeuron(1, 1, -0.75);

		// 001
		//_neurons[0][2].connectNeuron(&_neurons[1][1], 0.5f);

		brainContainer.layers[0].neurons[2].addNeuron(1, 1, 0.75);

		// 110
		//_neurons[0][0].connectNeuron(&_neurons[1][2], -0.25f);
		//_neurons[0][1].connectNeuron(&_neurons[1][2], 0.25f);

		brainContainer.layers[0].neurons[0].addNeuron(1, 2, -0.75);

		brainContainer.layers[0].neurons[1].addNeuron(1, 2, -0.75);

		// 011
		// _neurons[0][1].connectNeuron(&_neurons[1][2], -0.25);
		// _neurons[0][2].connectNeuron(&_neurons[1][2], 0.25f);

		brainContainer.layers[0].neurons[1].addNeuron(1, 2, 0.75);

		brainContainer.layers[0].neurons[2].addNeuron(1, 2, 0.75);

		// 011
		// _neurons[0][0].connectNeuron(&_neurons[1][3], 0.334f);
		// _neurons[0][1].connectNeuron(&_neurons[1][3], 0.334f);
		// _neurons[0][2].connectNeuron(&_neurons[1][3], 0.334f);

		brainContainer.layers[0].neurons[0].addNeuron(1, 3, 0.334);

		brainContainer.layers[0].neurons[1].addNeuron(1, 3, 0.334);

		brainContainer.layers[0].neurons[2].addNeuron(1, 3, 0.334);


		// _neurons[1][0]._valueActivation = 1.5;
		// _neurons[1][1]._valueActivation = 0.5;
		// _neurons[1][2]._valueActivation = 0.75;
		// _neurons[1][3]._valueActivation = 0.9;

		// _neurons[1][0].connectNeuron(&_neurons[2][0], 1.0f);
		// _neurons[1][1].connectNeuron(&_neurons[2][1], 1.0f);
		// _neurons[1][2].connectNeuron(&_neurons[2][2], 1.0f);
		// _neurons[1][3].connectNeuron(&_neurons[2][3], 1.0f);

		brainContainer.layers[1].neurons[0].valueAtivation = 1.5f;
		brainContainer.layers[1].neurons[0].addNeuron(2, 0, 1.01f);

		brainContainer.layers[1].neurons[1].valueAtivation = 0.5f;
		brainContainer.layers[1].neurons[1].addNeuron(2, 1, 1.02f);

		brainContainer.layers[1].neurons[2].valueAtivation = 0.75f;
		brainContainer.layers[1].neurons[2].addNeuron(2, 2, 1.03f);

		brainContainer.layers[1].neurons[3].valueAtivation = 0.9f;
		brainContainer.layers[1].neurons[3].addNeuron(2, 3, 1.04f);

		std::cout << std::endl << std::endl << "Show container" << std::endl << std::endl;
		brainContainer.show();

		std::cout << std::endl << std::endl << "Show BRAIN" << std::endl << std::endl;
		brain.init(brainContainer);
		brain.show();

		std::cout << std::endl << std::endl << "Show SAVE container" << std::endl << std::endl;
		BrainContainer brainContainerSave = brain.save();
		brainContainerSave.show();
	}

	bool learn = false;

	if (learn) {
		float value = getRes(brain);
		log("RES: " + std::to_string(value));
	}
	else {
		if (false)
		{
			//Brain brain;
			//brain.init();
			brain.reset();

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
		else
		{
			// 0, 0, 0 - стоять
			{
				//Brain brain;
				//brain.init();
				brain.reset();

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
				//Brain brain;
				//brain.init();
				brain.reset();

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
				//Brain brain;
				//brain.init();
				brain.reset();

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
				//Brain brain;
				//brain.init();
				brain.reset();

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
				//Brain brain;
				//brain.init();
				brain.reset();

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
				//Brain brain;
				//brain.init();
				brain.reset();

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
				//Brain brain;
				//brain.init();
				brain.reset();

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
				//Brain brain;
				//brain.init();
				brain.reset();

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
	}

	log("END");

	char valueChar;
	std::cin >> valueChar;
	return 0;
}
