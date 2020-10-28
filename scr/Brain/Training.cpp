
#include "Training.h"
#include "Brain.h"
#include "Print.h"
#include "Error.h"
#include "../Common/Help.h"

#include <list>
#include <iostream>
#include <algorithm>
#include <ctime>

#define CONFIG_MINI_00 0
#define CONFIG_MINI_01 1

/*const double min_value = -0.99;
const double valuePLUS = 0.99;
const double valueZero = 0.01;*/

const double min_value = -100000.0;
const double valuePLUS = 100000.0;
const double valueZero = 100.0;

namespace NeuralNetwork {
	int countGeneration = 100; // 30;
	int countItem = 100; // 1000;
	int countBest = 10; // 50;
	double bestValue = DBL_MAX;
	bool loadBest = true;
	bool saveBest = true;

	double currentCompliance[5] = { 0.0, 0.0, 0.0, 0.0, 0.0 };
	double bestCompliance[5] = {0.0, 0.0, 0.0, 0.0, 0.0};

	BrainPtr bestBrain;
	std::vector<size_t> layersSet = { 3, 4, 4 };
	std::list<BrainPtr> brestBrains;
	double muteBest = 10.0;

	bool compareBrainLess(BrainPtr first, BrainPtr second) {
		return first->errorInfo < second->errorInfo ? true : false;
	}

	bool compareBrain(BrainPtr first, BrainPtr second) {
		return first->errorInfo > second->errorInfo ? true : false;
	}

	inline double protectConfig(double compliance, const int index, const double decline) {
		if (currentCompliance[index] < bestCompliance[index]) {
			compliance = compliance * decline;
			return compliance;
		}
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
		currentCompliance[0] = getCompliance(brain, { valuePLUS,	valueZero,	valuePLUS }, { valuePLUS,	valueZero,	valueZero,	valueZero });
		currentCompliance[1] = getCompliance(brain, { valueZero,	valuePLUS,	valueZero }, { min_value,	valueZero,	valueZero,	valueZero });
		currentCompliance[2] = getCompliance(brain, { valuePLUS,	valuePLUS,	valueZero }, { valueZero,	valuePLUS,	valueZero,	valueZero });
		currentCompliance[3] = getCompliance(brain, { valueZero,	valuePLUS,	valuePLUS }, { valueZero,	valueZero,	valuePLUS,	valueZero });
		currentCompliance[4] = getCompliance(brain, { valuePLUS,	valuePLUS,	valuePLUS }, { valuePLUS,	valuePLUS,	valuePLUS,	valuePLUS });

		for (int i = 0; i < 5; ++i) {
			if (currentCompliance[i] > bestCompliance[i])
				bestCompliance[i] = currentCompliance[i];
		}

		for (auto value : currentCompliance) {
			if (value != 0.0) {
				compliance *= value;
			}
		}

		/*const int indexProtect = 4;
		if (currentCompliance[indexProtect] < bestCompliance[indexProtect]) {
			compliance = compliance * 0.75;
			return compliance;
		}*/

		protectConfig(compliance, 0, 0.99);
		protectConfig(compliance, 1, 0.99);
		protectConfig(compliance, 2, 0.99);
		protectConfig(compliance, 3, 0.99);
		protectConfig(compliance, 4, 0.99);
#endif

		return compliance;
	}

	void getBestGeneration(std::list<BrainPtr>& brestBrains, const int generation) {
		std::list<BrainPtr> brains;
		int index = 0;

		for (const BrainPtr& bestBrain : brestBrains) {
			for (size_t i = 1; i < countItem; ++i) {
				double matting = 0.1;

				//double matting = help::random(0.0, (muteBest * 2.0));

				//double matting = (double)i / (double)countItem * 0.1;

				BrainPtr newBrain = bestBrain->getCopy(matting);
				brains.push_back(newBrain);

				//double errorInfo = compileCompliance(*newBrain.get());
				Error::test(newBrain);

				//newBrain->errorInfo = errorInfo;
				newBrain->generationInfo = generation;
				newBrain->itemIndexInfo = index;
				newBrain->mattingInfo = matting;

				++index;
			}

			brains.push_back(bestBrain);
		}

		if (brains.size() > 1) {
			//brains.sort(compareBrain);
			brains.sort(compareBrainLess);
		}

		if (brains.size() > countBest) {
			brains.resize(countBest);
		}

		brestBrains = brains;
	}

	void main_prepare() {
		int startIndex = 0;

		if (loadBest) {
			BrainPtr brain = Brain::loadBrain();

			if (!brain) {
				brain = Brain::loadBrain("brainBack.json");
			}

			if (brain) {

				/*std::stringstream text;
				stringResult(text, { valuePLUS,	valueZero,	valuePLUS }, { valuePLUS,	valueZero,	valueZero,	valueZero }, *brain.get());
				stringResult(text, { valueZero,	valuePLUS,	valueZero }, { min_value,	valueZero,	valueZero,	valueZero }, *brain.get());
				stringResult(text, { valuePLUS,	valuePLUS,	valueZero }, { valueZero,	valuePLUS,	valueZero,	valueZero }, *brain.get());
				stringResult(text, { valueZero,	valuePLUS,	valuePLUS }, { valueZero,	valueZero,	valuePLUS,	valueZero }, *brain.get());
				stringResult(text, { valuePLUS,	valuePLUS,	valuePLUS }, { valuePLUS,	valuePLUS,	valuePLUS,	valuePLUS }, *brain.get());
				std::cout << text.str() << std::endl;*/

				brain->save("brainBack.json");
				brestBrains.push_back(brain);
				startIndex = 1;
			}
		}

		// Создание первых, случайные варианты
		//for (int iI = 0; iI < countBest; ++iI) {
		for (int iI = startIndex; iI < countBest; ++iI) {
			BrainPtr brain = std::make_shared<Brain>(layersSet, true);
			//brain->errorInfo = 0; // DBL_MAX;
			brain->errorInfo = DBL_MAX;
			brain->generationInfo = 0;
			brain->itemIndexInfo = iI;
			brain->mattingInfo = 0;
			brestBrains.push_back(brain);
		}
	}

	void main_train() {
		Error::add({ valuePLUS,	valueZero,	valuePLUS }, { valuePLUS,	valueZero,	valueZero,	valueZero });
		Error::add({ valueZero,	valuePLUS,	valueZero }, { min_value,	valueZero,	valueZero,	valueZero });
		Error::add({ valuePLUS,	valuePLUS,	valueZero }, { valueZero,	valuePLUS,	valueZero,	valueZero });
		Error::add({ valueZero,	valuePLUS,	valuePLUS }, { valueZero,	valueZero,	valuePLUS,	valueZero });
		Error::add({ valuePLUS,	valuePLUS,	valuePLUS }, { valuePLUS,	valuePLUS,	valuePLUS,	valuePLUS });

		long timeStart = std::clock();
		int countSave = 0;

		// Генерация. 0, это случайные, без оценки ошибки
		for (int iG = 1; iG < countGeneration; ++iG)
		{
			//log("Generation: " + std::to_string(iG));
			getBestGeneration(brestBrains, iG);

			// Отобразить выходные значения
			if (brestBrains.size() > 0) {
				BrainPtr brain = brestBrains.front();
				if (bestBrain.get() != brain.get()) {
					bestBrain = brain;

					muteBest = bestBrain->mattingInfo;

				#if CONFIG_MINI_00
					printError(*brain.get());
				#endif

				#if CONFIG_MINI_01
					printError(*brain.get());

					long time = std::clock() - timeStart;
					//if (time > 18000)
					//if (time > 10000)
					{
						std::stringstream text;
						stringResult(text, { valuePLUS,	valueZero,	valuePLUS }, { valuePLUS,	valueZero,	valueZero,	valueZero }, *bestBrain.get());
						stringResult(text, { valueZero,	valuePLUS,	valueZero }, { min_value,	valueZero,	valueZero,	valueZero }, *bestBrain.get());
						stringResult(text, { valuePLUS,	valuePLUS,	valueZero }, { valueZero,	valuePLUS,	valueZero,	valueZero }, *bestBrain.get());
						stringResult(text, { valueZero,	valuePLUS,	valuePLUS }, { valueZero,	valueZero,	valuePLUS,	valueZero }, *bestBrain.get());
						stringResult(text, { valuePLUS,	valuePLUS,	valuePLUS }, { valuePLUS,	valuePLUS,	valuePLUS,	valuePLUS }, *bestBrain.get());
						std::cout << text.str() << " countSave: " << countSave << std::endl;

						/*brain->resultInfo = text.str();
						std::string fileName = "D:\\Projects\\Brain_example\\Brain_example\\Brain\\temp\\brain_" + std::to_string(countSave) + ".json";
						Brain::saveBrain(*bestBrain.get(), fileName);
						++countSave;
						timeStart = std::clock();*/
					}
				#endif
				}
			}

			
		}

		// Отобразить
		if (bestBrain) {

#if CONFIG_MINI_00
			printResult({ 1.0, 1.0, 0.0 }, *bestBrain.get());
			printResult({ 0.0, 1.0, 1.0 }, *bestBrain.get());
#endif

#if CONFIG_MINI_01
			/*printResult({ 1.0, 0.0, 1.0 }, *bestBrain.get());
			printResult({ 0.0, 1.0, 0.0 }, *bestBrain.get());
			printResult({ 1.0, 1.0, 0.0 }, *bestBrain.get());
			printResult({ 0.0, 1.0, 1.0 }, *bestBrain.get());
			printResult({ 1.0, 1.0, 1.0 }, *bestBrain.get());*/

			/*std::stringstream text;

			stringResult(text, { valuePLUS,	valueZero,	valuePLUS }, { valuePLUS,	valueZero,	valueZero,	valueZero }, *bestBrain.get());
			stringResult(text, { valueZero,	valuePLUS,	valueZero }, { min_value,	valueZero,	valueZero,	valueZero }, *bestBrain.get());
			stringResult(text, { valuePLUS,	valuePLUS,	valueZero }, { valueZero,	valuePLUS,	valueZero,	valueZero }, *bestBrain.get());
			stringResult(text, { valueZero,	valuePLUS,	valuePLUS }, { valueZero,	valueZero,	valuePLUS,	valueZero }, *bestBrain.get());
			stringResult(text, { valuePLUS,	valuePLUS,	valuePLUS }, { valuePLUS,	valuePLUS,	valuePLUS,	valuePLUS }, *bestBrain.get());

			std::cout << text.str() << std::endl;*/
#endif

			printError(*bestBrain.get());

			if (saveBest) {
				Brain::saveBrain(*bestBrain.get());
				Brain::saveBrain(*bestBrain.get(), "brainBack.json");
			}

		}
	}
}
