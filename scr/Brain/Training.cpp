
#include "Training.h"
#include "Brain.h"
#include "Print.h"
#include "Error.h"

#include <list>
//#include <vector>
#include <iostream>
#include <algorithm>

#define CONFIG_MINI_00 1
#define CONFIG_MINI_01 0

namespace NeuralNetwork {
	int countGeneration = 100; // 30;
	int countItem = 100; // 1000;
	int countBest = 10; // 50;
	double bestValue = DBL_MAX;

	BrainPtr bestBrain;
	std::vector<size_t> layersSet = { 3, 4, 4 };
	std::list<BrainPtr> brestBrains;
	//std::vector<BrainPtr> brestBrains;

	bool compareBrain(BrainPtr first, BrainPtr second) {
		return first->errorInfo > second->errorInfo ? true : false;
	}

	double compileError(Brain &brain) {
		double error = 0.0;

		error += getError(brain, { 1.0,	0.0,	1.0 }, { 1.0,	0.1,	0.1,	0.1 });
		error += getError(brain, { 0.0,	1.0,	0.0 }, { -1.0,	0.1,	0.1,	0.1 });
		error += getError(brain, { 1.0,	1.0,	0.0 }, { 0.1,	1.0,	0.1,	0.1 });
		error += getError(brain, { 0.0,	1.0,	1.0 }, { 0.1,	0.1,	1.0,	0.1 });
		error += getError(brain, { 1.0,	1.0,	1.0 }, { 1.0,	1.0,	1.0,	1.0 });

		return error;
	}

	double compileCompliance(Brain& brain) {
		double compliance = 1.0;

#if CONFIG_MINI_00
		compliance *= getCompliance(brain, { 0.0,	1.0,	1.0 }, { 0.1,	0.1,	1.0,	0.1 });
		compliance *= getCompliance(brain, { 1.0,	1.0,	0.0 }, { -1.0,	0.1,	1.0,	0.1 });
#endif

#if CONFIG_MINI_01
		compliance *= getCompliance(brain, { 1.0,	0.0,	1.0 }, { 1.0,	0.1,	0.1,	0.1 });
		compliance *= getCompliance(brain, { 0.0,	1.0,	0.0 }, { -1.0,	0.1,	0.1,	0.1 });
		compliance *= getCompliance(brain, { 1.0,	1.0,	0.0 }, { 0.1,	1.0,	0.1,	0.1 });
		compliance *= getCompliance(brain, { 0.0,	1.0,	1.0 }, { 0.1,	0.1,	1.0,	0.1 });
		compliance *= getCompliance(brain, { 1.0,	1.0,	1.0 }, { 1.0,	1.0,	1.0,	1.0 });
#endif

		return compliance;
	}

	void getBestGeneration(std::list<BrainPtr>& brestBrains, const int generation) {
	//void getBestGeneration(std::vector<BrainPtr>& brestBrains, const int generation) {
		std::list<BrainPtr> brains;
		//std::vector<BrainPtr> brains;
		int index = 0;

		for (const BrainPtr& bestBrain : brestBrains) {
			for (size_t i = 1; i < countItem; ++i) {
				double matting = 0.1; // (double)i / (double)countItem;

				BrainPtr newBrain = bestBrain->getCopy(matting);
				brains.push_back(newBrain);

				//double errorInfo = compileError(*newBrain.get());
				double errorInfo = compileCompliance(*newBrain.get());

				newBrain->errorInfo = errorInfo;
				newBrain->generationInfo = generation;
				newBrain->itemIndexInfo = index;
				newBrain->mattingInfo = matting;

				//printResult({ 1.f, 0.f, 1.f }, *newBrain.get());
				//printError(*newBrain.get());

				++index;
			}

			brains.push_back(bestBrain);
		}

		if (brains.size() > 1) {
			brains.sort(compareBrain);
		}

		if (brains.size() > countBest) {
			brains.resize(countBest);
		}

		brestBrains = brains;
	}

	void main_prepare() {
		// Создание первых, случайные варианты
		for (int iI = 0; iI < countBest; ++iI) {
			BrainPtr brain = std::make_shared<Brain>(layersSet, true);
			brain->errorInfo = 0; // DBL_MAX;
			brain->generationInfo = 0;
			brain->itemIndexInfo = iI;
			brain->mattingInfo = 0;
			brestBrains.push_back(brain);
		}
	}

	void main_train() {
		// Генерация. 0, это случайные, без оценки ошибки
		for (int iG = 1; iG < countGeneration; ++iG)
		{
			log("Generation: " + std::to_string(iG));
			getBestGeneration(brestBrains, iG);

			// Отобразить выходные значения
			if (brestBrains.size() > 0) {
				BrainPtr brain = brestBrains.front();
				if (bestBrain.get() != brain.get()) {
					bestBrain = brain;

				#if CONFIG_MINI_00
					printError(*brain.get());
				#endif

					//printResult({ 0.0, 0.0, 1.0 }, *brain.get());

					//printResult({ 1.0, 0.0, 1.0 }, *brain.get());
					//printResult({ 0.0, 1.0, 0.0 }, *brain.get());
					//printResult({ 0.0, 0.0, 1.0 }, *brain.get());

					/*printResult({ 1.0, 0.0, 1.0 }, *brain.get());
					printResult({ 0.0, 1.0, 0.0 }, *brain.get());
					printResult({ 1.0, 1.0, 0.0 }, *brain.get());
					printResult({ 0.0, 1.0, 1.0 }, *brain.get());
					printResult({ 1.0, 0.0, 1.0 }, *brain.get());*/
				}
			}
		}

		// Отобразить
		if (bestBrain) {
			//printConfigPtr(*bestBrain.get());

#if CONFIG_MINI_00
			printResult({ 1.0, 1.0, 0.0 }, *bestBrain.get());
			printResult({ 0.0, 1.0, 1.0 }, *bestBrain.get());
#endif

#if CONFIG_MINI_01
			printResult({ 1.0, 0.0, 1.0 }, *bestBrain.get());
			printResult({ 0.0, 1.0, 0.0 }, *bestBrain.get());
			printResult({ 1.0, 1.0, 0.0 }, *bestBrain.get());
			printResult({ 0.0, 1.0, 1.0 }, *bestBrain.get());
			printResult({ 1.0, 1.0, 1.0 }, *bestBrain.get());
#endif
			//printResult({ 0.0, 1.0, 1.0 }, *bestBrain.get());

			printError(*bestBrain.get());

		}

		/*size_t size = brestBrains.size();
		size = size > 4 ? 5 : size;

		for (int i = 0; i < size; ++i) {			
			BrainPtr brain = brestBrains[i];

			std::cout << std::endl;
			printError();

			printResult({ 0.0, 0.0, 0.0 }, *bestBrain.get());
			printResult({ 1.0, 0.0, 1.0 }, *bestBrain.get());
			printResult({ 0.0, 1.0, 0.0 }, *bestBrain.get());
			printResult({ 1.0, 1.0, 0.0 }, *bestBrain.get());
			printResult({ 0.0, 1.0, 1.0 }, *bestBrain.get());
			printResult({ 1.0, 1.0, 1.0 }, *bestBrain.get());
		}*/
	}
}
