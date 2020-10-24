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

void printError(Brain& brain);
void printResult(const std::vector<double>& inData, Brain& brain);
void printResult(const std::vector<double>& inData, const std::vector<double>& outData, const double errorInfo = 0, const int generation = 0, const int index = 0);
void printConfigPtr(Brain& brain);

}
