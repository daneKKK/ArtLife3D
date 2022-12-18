#include "Simulation.h"

Simulation::Simulation(float x, float y, float z, float maxview): 
	simulationSizeX(x), simulationSizeY(y), simulationSizeZ(z) ,MAXVIEW(maxview) 
{
	herbivore.push_back(Creature(0.1f*simulationSizeX, 0.5f * simulationSizeY, 0.5f*simulationSizeZ, 0.0f, 0.0f, 3.0f, 0.0f, 20, 1, 1.0f, 0.0f, 1.0f, 0.0f));
	carnivore.push_back(Creature(0.9f * simulationSizeX, 0.6f*simulationSizeY, 0.5f * simulationSizeZ, 0.0f, 0.0f, 1.0f, 0.0f, 20, 1, 0.3f, 1.0f, 0.0f, 0.0f));
}

Simulation::~Simulation() {
	herbivore.clear();
	carnivore.clear();
}

void Simulation::step(float dt, shader Shader)
{
	std::vector<float> inputs;
	for (int i = 0; i < 21; i++) {
		inputs.push_back(0.0f);
	}
	inputs.push_back(1.0f);
	float xT, yT;
	float lengthSquare;

	auto p = herbivore.begin();
	while (p < herbivore.end()) {
		for (auto d = carnivore.begin(); d < carnivore.end(); d++) {
			if (p->getX() - d->getX() > 0.5f * simulationSizeX) { xT = d->getX() + simulationSizeX; }
			else { xT = d->getX(); }
			if (d->getX() - p->getX() > 0.5f * simulationSizeX) { xT = d->getX() - simulationSizeX; }
			
			if (p->getY() - d->getY() > 0.5f * simulationSizeY) { yT = d->getY() + simulationSizeY; }
			else { yT = d->getY(); }
			if (d->getY() - p->getY() > 0.5f * simulationSizeY) { yT = d->getY() - simulationSizeY; }
			
			
			//std::cout << p->getY() << " " << yT << std::endl;
			
			for (int i = 0; i < 21; i++) {
				lengthSquare = p->intersection(xT, yT, d->getZ(), i, 1.0f);
				if (lengthSquare == -1.0f) { inputs.at(i) = 0.0f; }
				else {
					if (lengthSquare >= MAXVIEW * MAXVIEW) { inputs.at(i) = 0.0f; }
					else {
						inputs.at(i) = std::max(inputs.at(i), 1 - std::sqrt(lengthSquare) / MAXVIEW);
					}
				}
			}
		}


		p->move(inputs, dt);

		if (abs(p->getSpeed()) < 0.001) {
			p->setEnergy(p->getEnergy() + 0.08 * dt);
		}

		p->setTimer(p->getTimer() + 0.1f * dt);
		p->setX(std::fmod(p->getX(), simulationSizeX));
		p->setY(std::fmod(p->getY(), simulationSizeY));
		p->render(Shader);

		if ((p->getEnergy() > 0.9f) && (p->getTimer() > 1.0f)) {
			p = herbivore.insert(p, Creature((*p), true)) + 1;
		}

		p++;
		//std::cout << std::fmod(p->getX(), simulationSizeX) << std::endl;
	}

	p = carnivore.begin();
	while (p < carnivore.end()) {
		auto d = herbivore.begin();
		while (d < herbivore.end()) {
			if (p->getX() - d->getX() > 0.5f * simulationSizeX) { xT = d->getX() + simulationSizeX; }
			else { xT = d->getX(); }
			if (d->getX() - p->getX() > 0.5f * simulationSizeX) { xT = d->getX() - simulationSizeX; }

			if (p->getY() - d->getY() > 0.5f * simulationSizeY) { yT = d->getY() + simulationSizeY; }
			else { yT = d->getY(); }
			if (d->getY() - p->getY() > 0.5f * simulationSizeY) { yT = d->getY() - simulationSizeY; }


			//std::cout << p->getY() << " " << yT << std::endl;

			for (int i = 0; i < 21; i++) {
				lengthSquare = p->intersection(xT, yT, d->getZ(), i, 1.0f);
				if (lengthSquare == -1.0f) { inputs.at(i) = 0.0f; }
				else {
					if (lengthSquare >= MAXVIEW * MAXVIEW) { inputs.at(i) = 0.0f; }
					else {
						inputs.at(i) = std::max(inputs.at(i), 1 - MAXVIEW / std::sqrt(lengthSquare));
					}
				}
			}
			if (((p->getX() - xT) * (p->getX() - xT) + (p->getY() - yT) * (p->getY() - yT) <= 1.0f) && (p->getTimer() > 1.0f)) {
				p->setEnergy(p->getEnergy() + 0.2f);
				p->setBirthCounter(p->getBirthCounter() + 0.4f);
				p->setTimer(0.0f);
				d = herbivore.erase(d);
			}
			else {
				d++;
			}
		}
		p->move(inputs, dt);
		p->setX(std::fmod(p->getX(), simulationSizeX));
		p->setY(std::fmod(p->getY(), simulationSizeY));
		if (p->getEnergy() < 0.0f) {
			p = carnivore.erase(p);
			continue;
		};
		p->setTimer(p->getTimer() + 5.0f * dt);
		if (p->getBirthCounter() >= 0.99f) {
			p->setBirthCounter(p->getBirthCounter() - 0.99f);
			p = carnivore.insert(p, Creature(*p, true)) + 1;
		}
		p->render(Shader);
		p++;
	}
}
