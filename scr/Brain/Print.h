#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace NeuralNetwork {
	class Brain;

template <class Text>
void log(const Text& text) {
	std::cout << text << std::endl;
}

void printResult(const std::vector<double>& inData, const std::vector<double>& outData);
void printConfigPtr(Brain* brain);

}
