
#include "Test.h"
#include "Brain.h"
#include "Print.h"

namespace NeuralNetwork {

	void test(const std::vector<double> in, Brain* barain)
	{
		static Brain* runBarain = nullptr;

		if (!barain) {
			std::vector<size_t> layersSet = { 3, 4, 4 };
			runBarain = new NeuralNetwork::Brain(layersSet, true);
		}
		else {
			runBarain = barain;
		}

		std::vector<double> out;
		runBarain->action(in, out);

		if (!barain && runBarain) {
			NeuralNetwork::printConfigPtr(runBarain);
		}

		if (!barain) {
			delete runBarain;
			runBarain = nullptr;
		}

		NeuralNetwork::printResult(in, out);
	}

	void main_test() {
		/*{
			std::vector<size_t> layersSet = { 3, 4, 4 };
			NeuralNetwork::Brain brain = layersSet;

			NeuralNetwork::printConfigPrr(&brain);

			test({ 0.f, 0.f, 0.f }, &brain);
			test({ 1.f, 0.f, 1.f }, &brain);
			test({ 0.f, 1.f, 0.f }, &brain);
			test({ 0.f, 0.f, 1.f }, &brain);
			test({ 0.f, 1.f, 1.f }, &brain);
			test({ 1.f, 0.f, 0.f }, &brain);
			test({ 1.f, 1.f, 0.f }, &brain);
			test({ 1.f, 1.f, 1.f }, &brain);
		}*/

		{
			test({ 0.f, 0.f, 0.f });
			test({ 1.f, 0.f, 1.f });
			test({ 0.f, 1.f, 0.f });
			test({ 0.f, 0.f, 1.f });
			test({ 0.f, 1.f, 1.f });
			test({ 1.f, 0.f, 0.f });
			test({ 1.f, 1.f, 0.f });
			test({ 1.f, 1.f, 1.f });
		}
	}

}
