
/*
0, 0, 0 - стоять			0, 0, 0, 0
1, 0, 1 - вперёд			+1, 0, 0, 0
0, 1, 0 - назад				-1, 0, 0, 0
1, 0, 0 - смещение влево	0, -1, 0, 0
0, 0, 1 - смещение вправо	0, +1, 0, 0
1, 1, 0 - поворот на лево	0, -1, -1, 0
0, 1, 1 - поворот на право	0, +1, +1, 0
1, 1, 1 - действие			0, 0, 0, +1
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

	NeuralNetwork::main_prepare();
	
	long timeStart = std::clock();

	NeuralNetwork::main_train();

	timeStart = std::clock() - timeStart;
	NeuralNetwork::log("STOP: " + std::to_string(timeStart));

	NeuralNetwork::log("END");
	char valueChar;
	std::cin >> valueChar;
	return 0;
}
