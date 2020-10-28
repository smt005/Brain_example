#include "Error.h"

namespace NeuralNetwork {

	std::vector<Error::Case> Error::_cases;
	std::vector<double> Error::_currentError;

	void Error::test(BrainPtr& brain) {
		if (brain) {
			test(*brain.get());
		}
	}

	void Error::test(Brain& brain) {
		size_t size = _cases.size();

		for (size_t i = 0; i < size; ++i) {
			std::vector<double> &in = _cases[i].in;
			std::vector<double>& out = _cases[i].out;
			brain.action(in, out);
		}

		double errorsValue = getError();
		brain.errorInfo = errorsValue;
	}

	double Error::getError() {
		double errors = 0.0;

		for (size_t i = 0; i < _cases.size(); ++i) {
			errors += getError(i);
		}

		return errors;
	}

	double Error::getError(const size_t index) {
		const std::vector<double>& best = _cases[index].best;
		const std::vector<double>& out = _cases[index].out;
		std::vector<double>& bestError = _cases[index].bestError;

		size_t sizeArray = best.size();
		if (sizeArray != out.size()) {
			return DBL_MAX;
		}

		if (sizeArray != bestError.size()) {
			bestError.reserve(sizeArray);

			for (size_t i = 0; i < sizeArray; ++i) {
				bestError.emplace_back(DBL_MAX);
			}
		}

		if (sizeArray != _currentError.size()) {
			_currentError.resize(sizeArray);
		}

		bool goodError = true;
		double compileError = 0.0;
		double compileBestError = 0.0;

		for (size_t i = 0; i < sizeArray; ++i) {
			double errorValue = best[i] - out[i];
			errorValue = std::abs(errorValue);
			compileError += errorValue;
			compileBestError += bestError[i];

			if (errorValue < bestError[i]) {
				_currentError[i] = errorValue;
			}
			else {
				goodError = false;
			}
		}

		if (goodError) {
			bestError = _currentError;
			return compileError;
		}

		return compileError > compileBestError ? compileError : compileBestError;
	}

	bool Error::parceJson(const Json::Value& data) {
		auto parceArray = [](const Json::Value& arrayJson, std::vector<double>& array) {
			if (!arrayJson.isArray()) {
				return false;
			}

			for (const Json::Value& inValueJson : arrayJson) {
				double inValue = inValueJson.isDouble() ? inValueJson.asDouble() : 0.0;
				array.emplace_back(inValue);
			}
		};

		const Json::Value& casesJson = data["cases"];
		if (!casesJson.isArray()) {
			return false;
		}

		size_t size = casesJson.size();
		_cases.resize(size);

		size_t index = 0;
		for (const Json::Value& caseJson : casesJson) {
			parceArray(caseJson["in"], _cases[index].in);
		}

		return true;
	}

	void Error::getJson(Json::Value& data) {
		for (Case& caseItem : _cases) {
			Json::Value caseJson;

			for (double inValue : caseItem.in) {
				caseJson["in"].append(inValue);

			}
			for (double inValue : caseItem.best) {
				caseJson["best"].append(inValue);

			}
			for (double inValue : caseItem.out) {
				caseJson["out"].append(inValue);

			}

			data["cases"].append(caseJson);
		}
	}

	//---

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

			double resItem = std::abs(bestValue - value);
			//const double resItemOne = 1.0 / (1.0 + resItem);

			//result = result * resItemOne;

			//resItem *= std::abs(bestValue);

			result += resItem;
		}

		result /= static_cast<double>(outBest.size());
		result = 1.0 / (1.0 + result);

		return result;
	}
}
 