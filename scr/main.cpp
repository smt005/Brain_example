
/*
0, 0, 0 - ������			0, 0, 0, 0
1, 0, 1 - �����			+1, 0, 0, 0
0, 1, 0 - �����				-1, 0, 0, 0
1, 0, 0 - �������� �����	0, -1, 0, 0
0, 0, 1 - �������� ������	0, +1, 0, 0
1, 1, 0 - ������� �� ����	0, -1, -1, 0
0, 1, 1 - ������� �� �����	0, +1, +1, 0
1, 1, 1 - ��������			0, 0, 0, +1
*/

#include <Windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>

#include "Brain/Brain.h"
#include "Brain/Print.h"
#include  "Brain/Example.h"
#include "Brain/Training.h"

int main() {
	NeuralNetwork::log("BEGIN");

	/*NeuralNetwork::main_prepare();
	
	long timeStart = std::clock();

	NeuralNetwork::main_train();

	timeStart = std::clock() - timeStart;
	NeuralNetwork::log("STOP: " + std::to_string(timeStart));*/

	{
		std::vector<size_t> layersSet = { 3, 4, 4 };
		NeuralNetwork::Brain brain(layersSet, true);

		printConfigPtr(brain);

		printResult({ 1.0, 0.0, 1.0 }, brain);
		printResult({ 0.0, 1.0, 0.0 }, brain);
		printResult({ 1.0, 1.0, 0.0 }, brain);
		printResult({ 0.0, 1.0, 1.0 }, brain);
		printResult({ 1.0, 1.0, 1.0 }, brain);

		NeuralNetwork::Brain::saveBrain(brain);
	}

	{
		NeuralNetwork::BrainPtr brainPtr = NeuralNetwork::Brain::loadBrain();

		if (brainPtr) {
			NeuralNetwork::Brain& brain = *brainPtr.get();

			printConfigPtr(brain);

			printResult({ 1.0, 0.0, 1.0 }, brain);
			printResult({ 0.0, 1.0, 0.0 }, brain);
			printResult({ 1.0, 1.0, 0.0 }, brain);
			printResult({ 0.0, 1.0, 1.0 }, brain);
			printResult({ 1.0, 1.0, 1.0 }, brain);
		}
	}

	NeuralNetwork::log("END");
	char valueChar;
	std::cin >> valueChar;
	return 0;
}
