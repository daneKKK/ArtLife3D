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
	}
	return false;
}

void Neuron::giveInput(int x, int y, float w) {
	auto iterator = connection.begin();
	while (iterator < connection.end()) {
		if ((iterator->x == x) && (iterator->y = y)) {
			iterator->lastInput = w;
		}
	}
}

float Neuron::calculateOutput()
{
	float inputs = 0;
	auto iterator = connection.begin();
	while (iterator < connection.end()) {
		inputs += iterator->lastInput * iterator->weight;
	}
	lastOutput = 1.0f / (1.0f + std::exp(-1 * inputs));
	return lastOutput;
}

float Neuron::getOutput()
{
	return lastOutput;
}
