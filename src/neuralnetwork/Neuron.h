#ifndef NEURON_H
#define NEURON_H

#include <random>
#include <vector>
#include <cmath>
#include <memory>

#include "Connection.h"

class Neuron final 
{
private:
	std::vector<Connection> connection;

	float lastOutput = 0.0f;

	float normalRand(float xl, float xh);

	float uniformRand(); 

	float sigmoid();

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

#endif //NEURON_H