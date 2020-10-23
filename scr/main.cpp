
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

#include "Brain/Brain.h"
#include "Brain/Print.h"
#include  "Brain/Example.h"
#include "Brain/Training.h"

int main() {
	NeuralNetwork::log("BEGIN");

	NeuralNetwork::main_train();
	//NeuralNetwork::main_test();

	NeuralNetwork::log("END");

	char valueChar;
	std::cin >> valueChar;
	return 0;
}
