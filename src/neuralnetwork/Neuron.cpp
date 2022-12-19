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

Neuron::~Neuron()
{
	//std::cout << "DELETE" << std::endl;
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
	float t = ((uniformRand() - 0.5f) * 10);
	//std::cout << t << std::endl;
	connection.push_back(Connection(x, y, t));
}

void Neuron::mutate() {
	auto iterator = connection.begin();
	while (iterator < connection.end()) {
		if (uniformRand() < 0.3f) {
			float d = normalRand(-1.5f, 1.5f);
			//std::cout << "Norma; " << d << std::endl;
			iterator->weight = iterator->weight + d;
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
	srand(time(NULL) + (int)this + randSeed);
	randSeed += 1234 + std::rand();
	float s = 0;
	const int NUMBEROFROLLS = 5;
	for (int i = 0; i < NUMBEROFROLLS; i++) {
		s += static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX);
	}
	return (xl + (xh - xl) * s / NUMBEROFROLLS);
}

float Neuron::uniformRand() {
	srand(time(NULL) + (int)this + randSeed);
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
	
int Neuron::randSeed = 13;
