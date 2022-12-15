#include "NeuralNetwork.h"

float NeuralNetwork::uniformRand() {
	return static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX);
}

float NeuralNetwork::getOneOutput(int x, int y) {
	return network.at(y).at(x)->getOutput();
}

NeuralNetwork::NeuralNetwork(): NeuralNetwork(1) {}

NeuralNetwork::NeuralNetwork(unsigned int inputSize): inputSize(inputSize) {
	existingNeurons = 0;
	auto iterA = network.begin();
	while (iterA < network.end()) {
		auto iterB = iterA->begin();
		while (iterB < iterA->end()) {
			(*iterB) = nullptr;
			++iterB;
		}
		++iterA;
	}
	auto iterC = output.begin();
	while (iterC < output.end()) {
		(*iterC) = new Neuron;
		++iterC;
		++existingNeurons;
	}

}

NeuralNetwork::NeuralNetwork(const NeuralNetwork& base): inputSize(base.getInputSize()) {
	network = base.copyNetwork();
	output = base.copyOutput();
	existingNeurons = base.getExistingNeurons();
}

NeuralNetwork::NeuralNetwork(const NeuralNetwork& base, bool mutate): inputSize(base.getInputSize()) {
	network = base.copyNetwork();
	output = base.copyOutput();
	existingNeurons = base.getExistingNeurons();
	if (mutate == 0) { return; };
	float a = uniformRand();
	if (a < 0.33f) { return; }
	else if (a < 0.66f) {
		//connectionA
		int x0, x1, y0, y1;
		int newConnectionIndex = std::rand() % existingNeurons;
		if (newConnectionIndex < output.size()) {
			y1 = 4;
			x1 = newConnectionIndex;
		}
		else {
			auto iterA = network.end();
			--iterA;
			y1 = 3;
			while (iterA >= network.begin()) {
				float connectionFound = false;
				auto iterB = iterA->end();
				--iterB;
				x1 = 9;
				while (iterB >= iterA->begin()) {
					if ((*iterB) != nullptr) {
						--newConnectionIndex;
						if (newConnectionIndex == 0) {
							break;
						}
					}
					--x1;
					--iterB;
				}
				--y1;
				--iterA;
				if (connectionFound) { break; }
			}
		}
		newConnectionIndex = std::rand() % (inputSize + std::min(static_cast<int>(existingNeurons - 1 - newConnectionIndex), static_cast<int>(existingNeurons - output.size())));
		if (newConnectionIndex < inputSize + 1) {
			y0 = -1;
			x0 = newConnectionIndex;
		}
		else {
			auto iterA = network.begin();
			y0 = 0;
			while (iterA < network.end()) {
				float connectionFound = false;
				auto iterB = iterA->begin();
				x0 = 0;
				while (iterB < iterA->end()) {
					if ((*iterB) != nullptr) {
						--newConnectionIndex;
						if (newConnectionIndex == 0) {
							break;
						}
					}
					++x0;
					++iterB;
				}
				++y0;
				++iterA;
				if (connectionFound) { break; }
			}
		}
		if (y0 >= y1) { return; };
		if (y1 == 4) {
			output.at(x1)->switchConnection(x0, y0);
		}
		else {
			network.at(y1).at(x1)->switchConnection(x0, y0);
		}
	}
	else {
		int x = std::rand() % 10;
		int y = std::rand() % 4;
		if (network.at(y).at(x) != nullptr) { return; };
		network.at(y).at(x) = new Neuron();
		++existingNeurons;
	}

}

NeuralNetwork& NeuralNetwork::operator=(const NeuralNetwork& base)
{
	network = base.copyNetwork();
	output = base.copyOutput();
	existingNeurons = base.getExistingNeurons();
	return *this;
}

unsigned int NeuralNetwork::getInputSize() const
{
	return inputSize;
}

unsigned int NeuralNetwork::getExistingNeurons() const
{
	return existingNeurons;
}


std::array<std::array<Neuron*, 10>, 4> NeuralNetwork::copyNetwork() const
{
	std::array<std::array<Neuron*, 10>, 4> a;
	auto iterA = a.begin();
	auto iterABase = network.cbegin();
	while (iterABase < network.cend()) {
		auto iterB = iterA->begin();
		auto iterBBase = iterABase->cbegin();
		while (iterBBase < iterABase->cend()) {
			if ((*iterBBase) != nullptr) { (*iterB) = new Neuron(*(*iterBBase)); }
			else { (*iterB) = nullptr; };
			++iterB;
			++iterBBase;
		}
		++iterA;
		++iterABase;
	}

	return a;
}

std::array<Neuron*, 3> NeuralNetwork::copyOutput() const
{
	std::array<Neuron*, 3> a;
	auto iterA = a.begin();
	auto iterABase = output.cbegin();
	while (iterABase < output.cend()) {
		if (*iterABase != nullptr) {
			(*iterA) = new Neuron(*(*iterABase));
		}
		else {
			*iterA = nullptr;
		}
		++iterA;
		++iterABase;
	}
	return a;
}

void NeuralNetwork::calculateOutputs(std::vector<float> &input) {
	//CAN BE GREATLY REMADE BY CHANGING THE DIRECTION OF CONNECTIONS!!!!!!!!
	auto i = network.begin();
	int y0 = 0;
	while (i < network.end()) {
		auto j = i->begin();
		int x0 = 0;
		while (j < i->end()) {
			for (int k = 0; k < input.size(); k++) {
				(*j)->giveInput(k, -1, input.at(k));
			}
			int y = 0;
			for (auto l = network.begin(); l < i; ++l) {
				int x = 0;
				for (auto m = l->begin(); m < l->end(); m++) {
					if ((*m) != nullptr) {
						(*j)->giveInput(x, y, (*m)->getOutput());
					}
					++x;
				}
				++y;
			}
			(*j)->calculateOutput();
			++x0;
			for (auto n = output.begin(); n < output.end(); ++n) {
				(*n)->giveInput(x0, y0, (*j)->getOutput());
			}
		}
		++y0;
		++i;
	}
	for (int j = 0; j < input.size(); ++j) {
		for (auto n = output.begin(); n < output.end(); ++n) {
			(*n)->giveInput(j, -1, input.at(j));
		}
	}
	for (auto n = output.begin(); n < output.end(); ++n) {
		(*n)->calculateOutput();
	}
}

float NeuralNetwork::getOutput(int i) const
{
	return output.at(i)->getOutput();
}
