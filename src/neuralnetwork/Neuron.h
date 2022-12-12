#ifndef RANDOM
#include <random>
#endif // !RANDOM

#ifndef VECTOR
#include <vector>
#endif // !RANDOM

#ifndef MATH
#include <cmath>
#endif // !RANDOM

#ifndef MEMORY
#include <memory>
#endif

#include "neuralnetwork/Connection.h"

class Neuron final {
private:
	std::vector<Connection> connection;
	float lastOutput = 0.0f;
	float normalRand(float xl, float xh) {
		float s = 0;
		const int NUMBEROFROLLS = 5;
		for (int i = 0; i < NUMBEROFROLLS; i++) {
			s += static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX);
		}
		return (xl + (xh - xl) * s / NUMBEROFROLLS);
	}
	float uniformRand() {
		return static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX);
	}
	float sigmoid() {
		float inputs = 0;
		auto iterator = connection.begin();
		while (iterator < connection.end()) {
			inputs += iterator->lastInput * iterator->weight;
		}
		return 1.0f / (1.0f + std::exp(-1 * inputs));
	}
public:
	Neuron();
	Neuron(const Neuron& base);
	Neuron& operator=(const Neuron& base);
	unsigned int getConnectionLength();
	void switchConnection(int x, int y);
	void mutate();
	std::vector<Connection> getConnections() const;
	bool checkConnection(int x, int y);
	void giveInput(int x, int y, float w);
	float calculateOutput();
	float getOutput();
};