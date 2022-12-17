#include "Simulation.h"

Simulation::Simulation(float x, float y, float z): simulationSizeX(x), simulationSizeY(y), simulationSizeZ(z) {
	herbivore.push_back(Creature(0.1f*simulationSizeX, 0.5f * simulationSizeY, 0.5f*simulationSizeZ, 0.0f, 0.0f, 3.0f, 0.0f, 20, 1, 1.0f, 0.0f, 1.0f, 0.0f));
	carnivore.push_back(Creature(0.9f * simulationSizeX, 0.5f*simulationSizeY, 0.5f * simulationSizeZ, 0.0f, 0.0f, 1.0f, 0.0f, 20, 1, 0.3f, 1.0f, 0.0f, 0.0f));
}

void Simulation::step(float dt, shader Shader)
{


	for (auto p = herbivore.begin(); p < herbivore.end(); p++) {
		p->render(Shader);
	}
	for (auto p = carnivore.begin(); p < carnivore.end(); p++) {
		p->render(Shader);
	}
}
