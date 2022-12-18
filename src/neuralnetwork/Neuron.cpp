#include "Neuron.h"

Neuron::Neuron() {
	return;
}

Neuron::Neuron(const Neuron& base) {
	connection = base.getConnections();
}

Neuron& Neuron::operator=(const Neuron& base) {
	connection.clear();
	connection = base.getConnections();
	return *this;
}

unsigned int Neuron::getConnectionLength() {
	return connection.size();
}

void Neuron::switchConnection(int x, int y) {
	auto iterator = connection.begin();
	while (iterator < connection.end()) {
		if ((iterator->x == x) && (iterator->y == y)&&(uniformRand()<0.2)) {
			connection.erase(iterator);
			return;
		}
		++iterator;
	}
	connection.push_back(Connection(x, y, (uniformRand() - 0.5f)*2));
}

void Neuron::mutate() {
	auto iterator = connection.begin();
	while (iterator < connection.end()) {
		if (uniformRand() < 0.3f) {
			iterator->weight = iterator->weight + normalRand(-0.7f, 0.7f);
		}
		++iterator;
	}
}

std::vector<Connection> Neuron::getConnections() const {
	std::vector<Connection> a = connection;
	return a;
}

bool Neuron::checkConnection(int x, int y) {
	auto iterator = connection.begin();
	while (iterator < connection.end()) {
		if ((iterator->x == x) && (iterator->y = y)) {
			return true;
		}
		++iterator;
	}
	return false;
}

void Neuron::giveInput(int x, int y, float w) {
	//std::cout << "aaaaa" << std::endl;
	auto iterator = connection.begin();
	while (iterator < connection.end()) {
		if ((iterator->x == x) && (iterator->y = y)) {
			iterator->lastInput = w;
		}
		iterator++;
	}
	//std::cout << "bbbbb" << std::endl;
}

float Neuron::calculateOutput()
{
	float inputs = 0;
	auto iterator = connection.begin();
	while (iterator < connection.end()) {
		inputs += iterator->lastInput * iterator->weight;
		++iterator;
	}
	lastOutput = 1.0f / (1.0f + std::exp(-1 * inputs));
	return lastOutput;
}

float Neuron::getOutput()
{
	return lastOutput;
}

float Neuron::normalRand(float xl, float xh) {
	float s = 0;
	const int NUMBEROFROLLS = 5;
	for (int i = 0; i < NUMBEROFROLLS; i++) {
		s += static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX);
	}
	return (xl + (xh - xl) * s / NUMBEROFROLLS);
}

float Neuron::uniformRand() {
	return static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX);
}

float Neuron::sigmoid() {
	float inputs = 0;
	auto iterator = connection.begin();
	while (iterator < connection.end()) {
		inputs += iterator->lastInput * iterator->weight;
		++iterator;
	}
	return 1.0f / (1.0f + std::exp(-1 * inputs));
}
	

