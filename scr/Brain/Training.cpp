
#include "Training.h"
#include "Brain.h"
#include "Print.h"
#include "Test.h"

#include <list>
#include <iostream>
#include <algorithm>

namespace NeuralNetwork {
	int countGeneration = 30;// 5;
	int countItem = 1000;// 50;
	int countBest = 50;// 50;
	double bestGeneration = 0.0;
	BrainPtr bestBrain;

	void setCountGeneration(const int value) {
		countGeneration = value;
	}

	void setCountItem(const int value) {
		countItem = value;
	}

	void setCountBest(const int value) {
		countBest = value;
	}

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

	double testBrain(Brain& barain, const std::vector<double> in, std::vector<double> outBest)
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
				return 0.0;
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

	void testErrorFun() {
		std::cout << "+1 : " << "-------------------------------------" << std::endl;
		for (double i = 0.0; i < 4.0; i = i + 0.1) {
			double value = valuePlus(i);
			std::cout << "i: " << i << "\t -> " << value << std::endl;
		}

		std::cout << "-1 : " << "-------------------------------------" << std::endl;
		for (double i = 0.0; i > -4.0; i = i - 0.1) {
			double value = valuePlus(-i);
			std::cout << "i: " << i << "\t -> " << value << std::endl;
		}

		std::cout << "0 : " << "-------------------------------------" << std::endl;
		for (double i = -3.0; i < 3.0; i = i + 0.1) {
			double value = valueZero(-i, 1000.0);
			std::cout << "i: " << i << "\t -> " << value << std::endl;
		}
	}

	bool compareBrain(BrainPtr first, BrainPtr second) {
		return first->errorInfo > second->errorInfo ? true : false;
	}

	void getBestStartGeneration(std::list<BrainPtr>& brestBrain) {

		for (int iI = 0; iI < countItem; ++iI)
		{
			std::vector<size_t> layersSet = { 3, 4, 4 };
			BrainPtr brain = std::make_shared<Brain>(layersSet, true);

			double result = 0.0;
			//result += testBrain(*brain, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f , 0.f });
			result += testBrain(*brain, { 1.f, 0.f, 1.f }, { 1.0, 1.0, 1.0, 1.0 });
			/*result += testBrain(*brain, { 0.f, 1.f, 0.f }, { -1.f, 0.f, 0.f , 0.f });
			result += testBrain(*brain, { 0.f, 0.f, 1.f }, { 0.f, 1.f, 0.f , 0.f });
			result += testBrain(*brain, { 0.f, 1.f, 1.f }, { 0.f, 1.f, 1.f , 0.f });
			result += testBrain(*brain, { 1.f, 0.f, 0.f }, { 0.f, -1.f, 0.f , 0.f });
			result += testBrain(*brain, { 1.f, 1.f, 0.f }, { 0.f, -1.f, -1.f , 0.f });
			result += testBrain(*brain, { 1.f, 1.f, 1.f }, { 0.f, 0.f, 0.f , 1.f });*/

			//bestGeneration = result;
				
			brain->errorInfo = result;
			brain->generationInfo = 0;
			brain->itemIndexInfo = iI;

			brestBrain.push_front(brain);
		}

		if (brestBrain.size() > 1) {
			brestBrain.sort(compareBrain);
		}

		//------------------------------------------
		/*if (brestBrain.size() > 0)
		{
			for (auto& br : brestBrain) {
				br->resetBrain();
				double result = testBrain(*br, { 1.0, 0.0, 1.0 }, { 1.0, 1.0, 1.0, 1.0 });
				std::cout << "BRAIN: " << result << std::endl;
				test({ 1.f, 0.f, 1.f }, br.get());
			}
		}*/
		//-------------------------------------------

		/*std::cout << "BRAIN ALL" << std::endl;
		for (auto brain : brestBrain) {
			std::cout << "BRAIN: " << brain->errorInfo << "\t [" << brain->itemIndexInfo << ']' << std::endl;
		}
		std::cout << std::endl;*/

		if (brestBrain.size() > countBest) {
			brestBrain.resize(countBest);
		}

		/*std::cout << "BRAIN BEST" << std::endl;
		for (auto brain : brestBrain) {
			std::cout << "BRAIN: " << brain->errorInfo << "\t [" << brain->itemIndexInfo << ']' << std::endl;
		}
		std::cout << std::endl;*/

		/*if (brestBrain.size() > 0)
		{
				bestBrain = brestBrain.front();
				Brain& br = *bestBrain;

				printConfigPtr(&br);

				{
					br.reset();
					double result = testBrain(br, { 1.0, 0.0, 1.0 }, { 1.0, 0.0, 0.0 , 0.0 });
					std::cout << "BRAIN: " << result << "\t [" << br.itemIndexInfo << ']' << std::endl;
				}

				{
					//test({ 0.f, 0.f, 0.f }, &br);
					test({ 1.f, 0.f, 1.f }, &br);
					//test({ 0.f, 1.f, 0.f }, &br);
					//test({ 0.f, 0.f, 1.f }, &br);
					//test({ 0.f, 1.f, 1.f }, &br);
					//test({ 1.f, 0.f, 0.f }, &br);
					//test({ 1.f, 1.f, 0.f }, &br);
					//test({ 1.f, 1.f, 1.f }, &br);
				}
		}*/

		/*{
			int index = 0;
			for (auto& item : brestBrain) {
				//BestBrain = *brestBrain.begin();
				bestBrain = item;
				Brain& br = *bestBrain;

				printConfigPtr(&br);

				{
					br.reset();
					float result = testBrain(br, { 1.f, 0.f, 1.f }, { 1.f, 0.f, 0.f , 0.f });
					std::cout << "BRAIN: " << result << "\t [" << br.itemIndexInfo << ']' << std::endl;
				}

				{
					//test({ 0.f, 0.f, 0.f }, &br);
					test({ 1.f, 0.f, 1.f }, &br);
					//test({ 0.f, 1.f, 0.f }, &br);
					//test({ 0.f, 0.f, 1.f }, &br);
					//test({ 0.f, 1.f, 1.f }, &br);
					//test({ 1.f, 0.f, 0.f }, &br);
					//test({ 1.f, 1.f, 0.f }, &br);
					//test({ 1.f, 1.f, 1.f }, &br);
				}

				++index;
				if (index >= 9) {
					break;
				}
			}
		}*/
	}

	void getBestGeneration(std::list<BrainPtr>& brestBrains) {
		std::list<BrainPtr> brains;
		//brains.resize(brestBrains.size() * countItem + brestBrains.size());

		for (const BrainPtr& bestBrain : brestBrains) {
			for (size_t i = 0; i < countItem; ++i) {
				BrainPtr newBrain = bestBrain->getCopy(0.5);
				brains.push_back(newBrain);

				double result = 0.0;
				//result += testBrain(*brain, { 0.f, 0.f, 0.f }, { 0.f, 0.f, 0.f , 0.f });
				result += testBrain(*newBrain, { 1.f, 0.f, 1.f }, { 1.0, 1.0, 1.0 , 1.0 });
				/*result += testBrain(*newBrain, { 0.f, 1.f, 0.f }, { -1.f, 0.f, 0.f , 0.f });
				result += testBrain(*newBrain, { 0.f, 0.f, 1.f }, { 0.f, 1.f, 0.f , 0.f });
				result += testBrain(*newBrain, { 0.f, 1.f, 1.f }, { 0.f, 1.f, 1.f , 0.f });
				result += testBrain(*newBrain, { 1.f, 0.f, 0.f }, { 0.f, -1.f, 0.f , 0.f });
				result += testBrain(*newBrain, { 1.f, 1.f, 0.f }, { 0.f, -1.f, -1.f , 0.f });
				result += testBrain(*newBrain, { 1.f, 1.f, 1.f }, { 0.f, 0.f, 0.f , 1.f });*/

				newBrain->errorInfo = result;
				newBrain->generationInfo = 0;
				//newBrain->itemIndexInfo = iI;
			}

			brains.push_back(bestBrain);
		}

		if (brains.size() > 1) {
			brains.sort(compareBrain);
		}

		/*std::cout << "BRAIN ALL" << std::endl;
		for (auto brain : brains) {
			std::cout << "BRAIN: " << brain->errorInfo << std::endl;
		}
		std::cout << std::endl;*/

		//------------------------------------------
		/*if (brains.size() > 0)
		{
			for (auto& br : brains) {
				br->resetBrain();
				double result = testBrain(*br, { 1.0, 0.0, 1.0 }, { 1.0, 1.0, 1.0 , 1.0 });
				std::cout << "BRAIN: " << result << std::endl;
				test({ 1.f, 0.f, 1.f }, br.get());
			}
		}*/
		//-------------------------------------------

		if (brains.size() > countBest) {
			brains.resize(countBest);
		}

		brestBrains = brains;
	}

	void main_train() {

		if (true) {
			std::list<BrainPtr> brestBrains;
			getBestStartGeneration(brestBrains);

			//---------------------------------

			/*if (brestBrains.size() > 0)
			{
				bestBrain = brestBrains.front();
				Brain& br = *bestBrain;

				//printConfigPtr(&br);

				{
					br.reset();
					double result = testBrain(br, { 1.0, 0.0, 1.0 }, { 1.0, 0.0, 0.0 , 0.0 });
					std::cout << "BRAIN: " << result << "\t [" << br.itemIndexInfo << ']' << std::endl;
				}

				{
					//test({ 0.f, 0.f, 0.f }, &br);
					test({ 1.f, 0.f, 1.f }, &br);
					//test({ 0.f, 1.f, 0.f }, &br);
					//test({ 0.f, 0.f, 1.f }, &br);
					//test({ 0.f, 1.f, 1.f }, &br);
					//test({ 1.f, 0.f, 0.f }, &br);
					//test({ 1.f, 1.f, 0.f }, &br);
					//test({ 1.f, 1.f, 1.f }, &br);
				}
			}*/

			//---------------------------------------

			for (int iG = 0; iG < countGeneration; ++iG)
			{
				getBestGeneration(brestBrains);

				//---------------------------------

				/*if (brestBrains.size() > 0)
				{
					bestBrain = brestBrains.front();
					Brain& br = *bestBrain;

					//printConfigPtr(&br);

					{
						br.reset();
						double result = testBrain(br, { 1.0, 0.0, 1.0 }, { 1.0, 0.0, 0.0 , 0.0 });
						std::cout << "BRAIN: " << result << "\t [" << br.itemIndexInfo << ']' << std::endl;
					}

					{
						//test({ 0.f, 0.f, 0.f }, &br);
						test({ 1.f, 0.f, 1.f }, &br);
						//test({ 0.f, 1.f, 0.f }, &br);
						//test({ 0.f, 0.f, 1.f }, &br);
						//test({ 0.f, 1.f, 1.f }, &br);
						//test({ 1.f, 0.f, 0.f }, &br);
						//test({ 1.f, 1.f, 0.f }, &br);
						//test({ 1.f, 1.f, 1.f }, &br);
					}
				}*/

				//---------------------------------------

							//------------------------------------------
				if (brestBrains.size() > 0)
				{
					/*for (auto& br : brestBrains) {
						br->resetBrain();
						double result = testBrain(*br, { 1.0, 0.0, 1.0 }, { 1.0, 1.0, 1.0 , 1.0 });
						std::cout << "BRAIN: " << result << std::endl;
						test({ 1.f, 0.f, 1.f }, br.get());
					}*/

					auto& br = brestBrains.front();
					br->resetBrain();
					double result = testBrain(*br, { 1.0, 0.0, 1.0 }, { 1.0, 1.0, 1.0 , 1.0 });
					std::cout << "BRAIN: " << result << std::endl;
					test({ 1.f, 0.f, 1.f }, br.get());
				}
				//-------------------------------------------
			}

			//------------------------------------------
			if (brestBrains.size() > 0)
			{
				/*for (auto& br : brestBrains) {
					br->resetBrain();
					double result = testBrain(*br, { 1.0, 0.0, 1.0 }, { 1.0, 1.0, 1.0 , 1.0 });
					std::cout << "BRAIN: " << result << std::endl;
					test({ 1.f, 0.f, 1.f }, br.get());
				}*/

				auto& br = brestBrains.front();
				br->resetBrain();
				double result = testBrain(*br, { 1.0, 0.0, 1.0 }, { 1.0, 1.0, 1.0 , 1.0 });
				std::cout << "BRAIN: " << result << std::endl;
				test({ 1.f, 0.f, 1.f }, br.get());
				printConfigPtr(br.get());
			}
			//-------------------------------------------
		}
		else {
			BrainPtr brainPtr;

			{
				std::vector<size_t> layersSet = { 3, 4, 4 };
				Brain brain(layersSet, true);
				test({ 1.f, 0.f, 1.f }, &brain);

				brainPtr = brain.getCopy(0.01);
			}

			if (brainPtr) {
				{
					double result = testBrain(*brainPtr, { 1.f, 0.f, 1.f }, { 1.f, 0.f, 0.f , 0.f });
					std::cout << "BRAIN: " << result << "\t" << std::endl;
					test({ 1.f, 0.f, 1.f }, brainPtr.get());
				}

				{
					brainPtr->mutateValue(0.1);
					double result = testBrain(*brainPtr, { 1.f, 0.f, 1.f }, { 1.f, 0.f, 0.f , 0.f });
					std::cout << "BRAIN: " << result << "\t" << std::endl;
					test({ 1.f, 0.f, 1.f }, brainPtr.get());
				}

				{
					brainPtr->mutateValue(0.1);
					double result = testBrain(*brainPtr, { 1.f, 0.f, 1.f }, { 1.f, 0.f, 0.f , 0.f });
					std::cout << "BRAIN: " << result << "\t" << std::endl;
					test({ 1.f, 0.f, 1.f }, brainPtr.get());
				}

				{
					brainPtr->mutateValue(1.0);
					double result = testBrain(*brainPtr, { 1.f, 0.f, 1.f }, { 1.f, 0.f, 0.f , 0.f });
					std::cout << "BRAIN: " << result << "\t" << std::endl;
					test({ 1.f, 0.f, 1.f }, brainPtr.get());
				}
			}
		}
	}
}
