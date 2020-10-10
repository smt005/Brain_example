
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

#pragma once

#include <iostream>
#include <string>

#include "Brain.h"
#include "Neuron.h"
#include "Print.h"
#include "Test.h"
#include "Learn.h"

int main() {

	log("BEGIN");

	learn(1000, 1000);
	//test();

	log("END");

	char valueChar;
	std::cin >> valueChar;
	return 0;
}
