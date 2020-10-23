#include "Error.h"

namespace NeuralNetwork {


	double valuePlus(const double value) {
		double valueAbs = std::abs(value);
		double result = 0.0;

		if (valueAbs < 1.0 && valueAbs > 0.0) {
			result = 1.0 * valueAbs;
		}
		else if (valueAbs > 1.0) {
			result = 1.0 / valueAbs;
		}
		else if (valueAbs <= 0.0) {
			result = 0.0;
		}

		//result = std::pow(result, 5);
		return result;
	}

	double valueZero(const double value, const double decline) {
		if (value == 0.0f) {
			return 1.0f;
		}

		double valueAbs = std::abs(value);
		valueAbs = valueAbs > 1.0 ? 1.0 : valueAbs;
		double result = 1.0 - valueAbs;

		//result = std::pow(result, 5);
		result /= decline;

		return result;
	}

	double getError(Brain& barain, const std::vector<double> in, std::vector<double> outBest)
	{
		double result = 0.0f;

		std::vector<double> out;
		barain.action(in, out);

		if (outBest.size() != out.size()) {
			return result;
		}

		for (int i = 0; i < outBest.size(); ++i) {
			double bestValue = outBest[i];
			double value = out[i];

			if (value <= 0.0) {
				result += 0.0;
			}
			if (bestValue > 0.0f) {
				result += valuePlus(value);
			}

			/*if (bestValue > 0.0f) {
				result += valuePlus(value);
			}
			else if (bestValue < 0.0) {
				result += valuePlus(-value);
			}
			else {
				//result += std::pow(valueZero(value, 1000000.0), 5);
				result += std::pow(valueZero(value, 1000.0), 5);
			}*/
		}

		return result;
	}

}
