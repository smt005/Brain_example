
#include "Training.h"
#include "Brain.h"
#include "Print.h"
#include "Error.h"

#include <list>
#include <iostream>
#include <algorithm>

namespace NeuralNetwork {
	int countGeneration = 30; // 30;
	int countItem = 300; // 1000;
	int countBest = 30; // 50;
	
	bool compareBrain(BrainPtr first, BrainPtr second) {
		return first->errorInfo > second->errorInfo ? true : false;
	}

	void getBestGeneration(std::list<BrainPtr>& brestBrains, const int generation) {
		std::list<BrainPtr> brains;
		int index = 0;

		for (const BrainPtr& bestBrain : brestBrains) {
			for (size_t i = 0; i < countItem; ++i) {
				BrainPtr newBrain = bestBrain->getCopy(0.5);
				brains.push_back(newBrain);

				double error = 0.0;
				error += getError(*newBrain, { 1.f, 0.f, 1.f }, { 1.0, 1.0, 1.0 , 1.0 });
				/*error += getError(*brain, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f , 0.f });
				error += getError(*newBrain, { 1.f, 0.f, 1.f }, { 1.0, 0.0, 0.0 , 0.0 });
				error += getError(*newBrain, { 0.f, 1.f, 0.f }, { -1.f, 0.f, 0.f , 0.f });
				error += getError(*newBrain, { 0.f, 0.f, 1.f }, { 0.f, 1.f, 0.f , 0.f });
				error += getError(*newBrain, { 0.f, 1.f, 1.f }, { 0.f, 1.f, 1.f , 0.f });
				error += getError(*newBrain, { 1.f, 0.f, 0.f }, { 0.f, -1.f, 0.f , 0.f });
				error += getError(*newBrain, { 1.f, 1.f, 0.f }, { 0.f, -1.f, -1.f , 0.f });
				error += getError(*newBrain, { 1.f, 1.f, 1.f }, { 0.f, 0.f, 0.f , 1.f });*/

				newBrain->errorInfo = error;
				newBrain->generationInfo = generation;
				newBrain->itemIndexInfo = index;
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

	void main_train() {
		if (true) {
			BrainPtr bestBrain;
			std::vector<size_t> layersSet = { 3, 4, 4 };
			std::list<BrainPtr> brestBrains;

			// Создание первых, случайные варианты
			for (int iI = 0; iI < countItem; ++iI) {				
				BrainPtr brain = std::make_shared<Brain>(layersSet, true);
				brain->errorInfo = 0;// DBL_MAX;
				brain->generationInfo = 0;
				brain->itemIndexInfo = iI;
				brestBrains.push_back(brain);
			}

			// Генерация. 0, это случайные, без оценки ошибки
			for (int iG = 1; iG < countGeneration; ++iG)
			{
				getBestGeneration(brestBrains, iG);

				// Отобразить выходные значения
				if (brestBrains.size() > 0) {
					BrainPtr brain = brestBrains.front();
					if (bestBrain.get() != brain.get()) {
						bestBrain = brain;
						printResult({ 1.f, 0.f, 1.f }, *brain.get());
					}
				}
			}

			// Отобразить конфиг
			printConfigPtr(*bestBrain.get());
		}
	}
}
