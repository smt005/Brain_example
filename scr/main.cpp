
/*
0, 0, 0 - ������
1, 0, 1 - �����
0, 1, 0 - �����
1, 0, 0 - �������� �����
0, 0, 1 - �������� ������
1, 1, 0 - ������� �� ����
0, 1, 1 - ������� �� �����
1, 1, 1 - ��������
*/

#pragma once

#include <iostream>
#include <string>

#include "Brain.h"
#include "Neuron.h"
#include "Print.h"
#include "Test.h"

int main() {

	log("BEGIN");

	test();

	log("END");

	char valueChar;
	std::cin >> valueChar;
	return 0;
}
