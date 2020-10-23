#pragma once

#include "Neuron.h"
#include "Brain.h"
#include <vector>
#include <memory>

namespace NeuralNetwork {

	double getError(Brain& barain, const std::vector<double> in, std::vector<double> outBest);
}
