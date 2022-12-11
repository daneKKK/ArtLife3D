#ifndef RANDOM
#include <random>
#endif // !RANDOM

#ifndef VECTOR
#include <vector>
#endif // !RANDOM

#include "neuralnetwork/Connection.h"

class Neuron final {
private:
	std::vector<Connection> connection;
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
public:
	Neuron();
	Neuron(const Neuron& base);
	Neuron& operator=(const Neuron& base);
	unsigned int getConnectionLength();
	void switchConnection(int x, int y, float weight);
	void mutate();
	std::vector<Connection> getConnections() const;
};