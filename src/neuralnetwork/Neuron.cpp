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

void Neuron::switchConnection(int x, int y, float weight) {
	auto iterator = connection.begin();
	while (iterator < connection.end()) {
		if ((iterator->x == x) && (iterator->y == y)&&(uniformRand()<0.2)) {
			connection.erase(iterator);
			return;
		}
		++iterator;
	}
	connection.push_back(Connection(x, y, weight));
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
