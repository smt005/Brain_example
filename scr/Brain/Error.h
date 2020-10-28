#pragma once

#include "Neuron.h"
#include "Brain.h"

#include "json/json.h"
#include <vector>
#include <memory>

namespace NeuralNetwork {
	struct Error {
	public:
		struct Case {
			Case() {}
			Case(const std::vector<double>& _in, const std::vector<double>& _best)
				: in(_in)
				, best(_best)
			{}
			Case(const std::vector<double>& _in, const std::vector<double>& _best, const std::vector<double>& _out)
				: in(_in)
				, best(_best)
				, out(_out)
			{}
			std::vector<double> in;
			std::vector<double> best;
			std::vector<double> out;
			std::vector<double> bestError;
		};

	private:
		static std::vector<Case> _cases;
		static std::vector<double> _currentError;

	public:
		static bool isInited() {
			return _cases.size() > 0 ? true : false;
		}

		static inline void add(const std::vector<double>& _in, const std::vector<double>& _best) {
			_cases.emplace_back(_best, _best);
		}

		static inline void add(const std::vector<double>& _in, const std::vector<double>& _best, const std::vector<double>& _out) {
			_cases.emplace_back(_best, _best, _out);
		}

		static inline Case& getCase(const size_t index) {
			if (index >= _cases.size()) {
				_cases.resize(index + 1);
			}
			return _cases[index];
		}
		static inline std::vector<double>& getIn(const size_t index) {
			return getCase(index).in;
		}
		static inline std::vector<double>& getBest(const size_t index) {
			return getCase(index).best;
		}
		static inline std::vector<double>& getOut(const size_t index) {
			return getCase(index).out;
		}
		static inline std::vector<double>& getBestError(const size_t index) {
			return getCase(index).bestError;
		}

		static void test(BrainPtr& brain);
		static void test(Brain& brain);

		static double getError();
		static double getError(const size_t index);

		static bool parceJson(const Json::Value& data);
		static void getJson(Json::Value& data);
	};

	double getError(Brain& barain, const std::vector<double> in, std::vector<double> outBest);
	double getCompliance(Brain& barain, const std::vector<double> in, std::vector<double> outBest);
}
