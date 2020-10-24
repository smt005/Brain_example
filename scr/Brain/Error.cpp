#include "Error.h"

namespace NeuralNetwork {

	double getError(Brain& barain, const std::vector<double> in, std::vector<double> outBest)
	{
		double result = 0.0;

		std::vector<double> out;
		barain.action(in, out);

		if (outBest.size() != out.size()) {
			return result;
		}

		for (int i = 0; i < outBest.size(); ++i) {
			double bestValue = outBest[i];
			double value = out[i];

			double resItem = bestValue - value;
			resItem = std::abs(resItem);

			result += resItem;
		}

		return result;
	}

	double getCompliance(Brain& barain, const std::vector<double> in, std::vector<double> outBest)
	{
		double result = 1.0;

		std::vector<double> out;
		barain.action(in, out);

		if (outBest.size() != out.size()) {
			return result;
		}

		for (int i = 0; i < outBest.size(); ++i) {
			double bestValue = outBest[i];
			double value = out[i];

			const double resItem = std::abs(bestValue - value);
			//const double resItemOne = 1.0 / (1.0 + resItem);

			//result = result * resItemOne;

			result += resItem;
		}

		result /= static_cast<double>(outBest.size());
		result = 1.0 / (1.0 + result);;

		return result;
	}
}
 