
#pragma once

#include <vector>
#include <iostream>
#include <string>

#include "Brain.h"
#include "Neuron.h"
#include "Synaps.h"
#include "BrainContainer.h"

#include "Print.h"

float getRes(Brain& brain) {
	float globalValue = 0.0f;

	// 0, 0, 0 - ������
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

	// 1, 0, 1 - �����
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


	// 0, 1, 0 - �����
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

	// 1, 0, 0 - �������� �����
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

	// 1, 1, 0 - ������� �� ����
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

	// 0, 0, 1 - �������� �����
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

	// 0, 1, 1 - ������� �� �����
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

	// 1, 1, 1 - ��������
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
