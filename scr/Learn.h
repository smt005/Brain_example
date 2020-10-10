
#pragma once

#include <vector>
#include <iostream>
#include <string>

#include "Brain.h"
#include "Neuron.h"
#include "Synaps.h"
#include "BrainContainer.h"

#include "Print.h"

void initTest(BrainContainer& brainContainer)
{
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
}

float getRes(Brain& brain) {

	float valueAll = 0.0f;

	// 1, 0, 1 - вперёд
	{
		brain.reset();

		std::vector<float> inData;
		inData.push_back(1.0f);
		inData.push_back(0.0f);
		inData.push_back(1.0f);

		brain.enter(inData);
		brain.update();

		std::vector<float> outData;
		brain.result(outData);
		//printResult(inData, outData);

		float valueSum = 0.0f;

		// 0 = 1.0
		{		
			float value = 1.0f;

			float data = outData[0];
			if (data == 1.0f) {
				value = 1.0f;
			}
			else if (data > 1.0f) {
				value = 1.0f; // / data;
			}
			else if (data < 1.0f && data >= 0.0f) {
				value = data;
			}
			else if (data < 0.0f) {
				value = 0.0;
			}
			else { // == 0.0
				value = 0.0f;
			}

			valueSum += value;
		}

		// 1 = 0.0
		{
			float value = 1.0f;

			float data = outData[1];
			if (data == 0.0f) {
				value = 1.0f;
			}
			else if (data > 1.0f) {
				value = 0.0f;
			}
			else if (data < -1.0f) {
				value = 0.0f;
			}
			else
			{
				value = 1.0f - std::abs(data);
			}

			//value = value / 12.0f;
			valueSum += value;
		}

		// 2 = 0.0
		{
			float value = 1.0f;

			float data = outData[2];
			if (data == 0.0f) {
				value = 1.0f;
			}
			else if (data > 1.0f) {
				value = 0.0f;
			}
			else if (data < -1.0f) {
				value = 0.0f;
			}
			else
			{
				value = 1.0f - std::abs(data);
			}

			//value = value / 12.0f;
			valueSum += value;
		}

		// 3 = 0.0
		{
			float value = 1.0f;

			float data = outData[3];
			if (data == 0.0f) {
				value = 1.0f;
			}
			else if (data > 1.0f) {
				value = 0.0f;
			}
			else if (data < -1.0f) {
				value = 0.0f;
			}
			else
			{
				value = 1.0f - std::abs(data);
			}

			//value = value / 12.0f;
			valueSum += value;
		}

		valueAll += (100.0f * (valueSum / 4.0f));
	}

	// 0, 1, 0 - назад
	{
		brain.reset();

		std::vector<float> inData;
		inData.push_back(0.0f);
		inData.push_back(1.0f);
		inData.push_back(0.0f);

		brain.enter(inData);
		brain.update();

		std::vector<float> outData;
		brain.result(outData);
		//printResult(inData, outData);

		float valueSum = 0.0f;

		// 0 = -1.0
		{
			float value = 1.0f;

			float data = outData[0];
			if (data == -1.0f) {
				value = 1.0f;
			}
			else if (data < -1.0f) {
				value = 1.0f; // / std::abs(data);
			}
			else if (data > -1.0f && data <= 0.0f) {
				value = std::abs(data);
			}
			else if (data >= 0.0f) {
				value = 0.0;
			}
			else { // == 0.0
				value = 0.0f;
			}

			valueSum += value;
		}

		// 1 = 0.0
		{
			float value = 1.0f;

			float data = outData[1];
			if (data == 0.0f) {
				value = 1.0f;
			}
			else if (data > 1.0f) {
				value = 0.0f;
			}
			else if (data < -1.0f) {
				value = 0.0f;
			}
			else
			{
				value = 1.0f - std::abs(data);
			}

			//value = value / 12.0f;
			valueSum += value;
		}

		// 2 = 0.0
		{
			float value = 1.0f;

			float data = outData[2];
			if (data == 0.0f) {
				value = 1.0f;
			}
			else if (data > 1.0f) {
				value = 0.0f;
			}
			else if (data < -1.0f) {
				value = 0.0f;
			}
			else
			{
				value = 1.0f - std::abs(data);
			}

			value = value / 12.0f;
			valueSum += value;
		}

		// 3 = 0.0
		{
			float value = 1.0f;

			float data = outData[3];
			if (data == 0.0f) {
				value = 1.0f;
			}
			else if (data > 1.0f) {
				value = 0.0f;
			}
			else if (data < -1.0f) {
				value = 0.0f;
			}
			else
			{
				value = 1.0f - std::abs(data);
			}

			//value = value / 12.0f;
			valueSum += value;
		}

		valueAll += (100.0f * (valueSum / 4.0f));
	}

	// 1, 1, 1 - действие
	{
		brain.reset();

		std::vector<float> inData;
		inData.push_back(1.0f);
		inData.push_back(1.0f);
		inData.push_back(1.0f);

		brain.enter(inData);
		brain.update();

		std::vector<float> outData;
		brain.result(outData);
		//printResult(inData, outData);

		float valueSum = 0.0f;

		// 0 = 0.0
		{
			float value = 1.0f;

			float data = outData[0];
			if (data == 0.0f) {
				value = 1.0f;
			}
			else if (data > 1.0f) {
				value = 0.0f;
			}
			else if (data < -1.0f) {
				value = 0.0f;
			}
			else
			{
				value = 1.0f - std::abs(data);
			}

			//value = value / 12.0f;
			valueSum += value;
		}

		// 1 = 0.0
		{
			float value = 1.0f;

			float data = outData[1];
			if (data == 0.0f) {
				value = 1.0f;
			}
			else if (data > 1.0f) {
				value = 0.0f;
			}
			else if (data < -1.0f) {
				value = 0.0f;
			}
			else
			{
				value = 1.0f - std::abs(data);
			}

			//value = value / 12.0f;
			valueSum += value;
		}

		// 2 = 0.0
		{
			float value = 1.0f;

			float data = outData[2];
			if (data == 0.0f) {
				value = 1.0f;
			}
			else if (data > 1.0f) {
				value = 0.0f;
			}
			else if (data < -1.0f) {
				value = 0.0f;
			}
			else
			{
				value = 1.0f - std::abs(data);
			}

			//value = value / 12.0f;
			valueSum += value;
		}

		// 3 = 1.0
		{
			float value = 1.0f;

			float data = outData[3];
			if (data == 1.0f) {
				value = 1.0f;
			}
			else if (data > 1.0f) {
				value = 1.0f; // / data;
			}
			else if (data < 1.0f && data > 0.0f) {
				value = data;
			}
			else if (data > -1.0f && data < 0.0f) {
				value = std::abs(data);
			}
			else { // == 0.0
				value = 0.0f;
			}

			valueSum += value;
		}

		valueAll += (100.0f * (valueSum / 4.0f));
	}

	valueAll = valueAll / 3.0f;

	return valueAll;
}

float getResAll(Brain& brain) {
	float globalValue = 0.0f;

	// 0, 0, 0 - стоять
	/*{
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
		//printResult(inData, outData);

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
		globalValue += value == 100.0f ? 100.0f : 0.0f;
	}*/

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
		//printResult(inData, outData);

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
		globalValue += value == 100.0f ? 100.0f : 0.0f;
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
		//printResult(inData, outData);

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
		globalValue += value == 100.0f ? 100.0f : 0.0f;
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
		//printResult(inData, outData);

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
		globalValue += value == 100.0f ? 100.0f : 0.0f;
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
		//printResult(inData, outData);

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
		globalValue += value == 100.0f ? 100.0f : 0.0f;
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
		//printResult(inData, outData);

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
		globalValue += value == 100.0f ? 100.0f : 0.0f;
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
		//printResult(inData, outData);

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
		globalValue += value == 100.0f ? 100.0f : 0.0f;
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
		//printResult(inData, outData);

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
		globalValue += value == 100.0f ? 100.0f : 0.0f;
	}

	return (globalValue / 7.0f);
}

void learn(int maxGeneration, int maxIteration) {
	bool stop = false;
	bool newConfig = false;
	int finalGeneration = 0;

	float bestValue = 0.0f;
	BrainContainer bestBrain;
	bestBrain.initDefault();
	bestBrain.generate();

	for (int iGeneration = 0; iGeneration < maxGeneration; ++iGeneration) {

		//log("// " + std::to_string(iGeneration) + ".............................................................................");

		for (int i = 0; i < maxIteration; ++i) {

			BrainContainer testContaindeBrain;
			testContaindeBrain.initDefault();
			testContaindeBrain.generate();
			//initTest(testContaindeBrain);

			cross(bestBrain, testContaindeBrain);

			Brain brainTest;
			brainTest.init(testContaindeBrain);
			float value = getRes(brainTest);

			if (value > bestValue) {
				newConfig = true;
				finalGeneration = iGeneration;
				bestValue = value;
				bestBrain = testContaindeBrain;
			}

			if (bestValue >= 99.0f) {
				break;
			}
		}

		if (newConfig) {
			newConfig = false;
			log("\nBest generation: " + std::to_string(iGeneration) + " value: " + std::to_string(bestValue) + " ------------------------------------------------------------------------------");
			bestBrain.show();
			printConfig(bestBrain);
		}

		if (bestValue >= 99.0f) {
			break;
		}
	}

	log("\nEnd best generation: " + std::to_string(finalGeneration) + " value: " + std::to_string(bestValue) + " ------------------------------------------------------------------------------");
	bestBrain.show();
	printConfig(bestBrain);
}


