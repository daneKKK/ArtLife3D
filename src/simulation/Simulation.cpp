#include "Simulation.h"

Simulation::Simulation(float x, float y, float z, float maxview, int herbiCount, int carniCount): 
	simulationSizeX(x), simulationSizeY(y), simulationSizeZ(z) ,MAXVIEW(maxview) 
{
	srand(time(NULL) + timerSeed);
	std::cout << std::rand() << std::endl;
	for (int i = 0; i < herbiCount; i++) {
		herbivore.push_back(new Creature(static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX) * simulationSizeX, 
			static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX) * simulationSizeY,
			0.5f * simulationSizeZ, static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX) * 3.14f, 
			0.0f, 3.0f, 0.0f, 20, 1, 1.0f, 0.0f, 1.0f, 0.0f));
	}
	for (int i = 0; i < carniCount; i++) {
		carnivore.push_back(new Creature(static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX) * simulationSizeX, 
			static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX) * simulationSizeY, 
			0.5f * simulationSizeZ, 
			3.14f * static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX), 
			0.0f, 1.0f, 0.0f, 20, 1, 0.3f, 1.0f, 0.0f, 0.0f));
		//carnivore.at(i) = std::move(Creature(carnivore.at(i), true));
	}
	for (auto p = herbivore.begin(); p < herbivore.end(); p++) {
		(*p)->setTimer(-0.5f + 1.0f * static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX));
	}
	//herbivore.push_back(Creature(0.1f*simulationSizeX, 0.5f * simulationSizeY, 0.5f*simulationSizeZ, 0.0f, 0.0f, 3.0f, 0.0f, 20, 1, 1.0f, 0.0f, 1.0f, 0.0f));
	//carnivore.push_back(Creature(0.4f * simulationSizeX, 0.5f*simulationSizeY, 0.5f * simulationSizeZ, 0.0f, 0.0f, 1.0f, 0.0f, 20, 1, 0.3f, 1.0f, 0.0f, 0.0f));
}

Simulation::~Simulation() {
	herbivore.clear();
	carnivore.clear();
}

void Simulation::step(const float dt, shader Shader)
{
	srand(time(NULL) + timerSeed + 17);
	std::vector<float> inputs;
	for (int i = 0; i < 21; i++) {
		inputs.push_back(0.0f);
	}
	inputs.push_back(1.0f);
	float xT, yT;
	float lengthSquare;

	//std::cout << "------------------" << std::endl;
	//for (int i = 0; i < herbivore.size(); i++) {
	//	std::cout << herbivore.at(i).getTimer() << std::endl;
	//}

	//std::cout << "===============" << std::endl;
	//std::cout << dt << std::endl;
	//std::cout << dt << "---------------" << std::endl;
	auto p = herbivore.begin();
	while (p < herbivore.end()) {
		//std::cout << (*p)->getTimer() << std::endl;
		for (auto d = carnivore.begin(); d < carnivore.end(); d++) {
			if ((*p)->getX() - (*d)->getX() >= 0.5f * simulationSizeX) { xT = (*d)->getX() + simulationSizeX; }
			else { xT = (*d)->getX(); }
			if ((*d)->getX() - (*p)->getX() >= 0.5f * simulationSizeX) { xT = (*d)->getX() - simulationSizeX; }
			else { xT = (*d)->getX(); }
			
			if ((*p)->getY() - (*d)->getY() > 0.5f * simulationSizeY) { yT = (*d)->getY() + simulationSizeY; }
			else { yT = (*d)->getY(); }
			if ((*d)->getY() - (*p)->getY() > 0.5f * simulationSizeY) { yT = (*d)->getY() - simulationSizeY; }
			else { xT = (*d)->getX(); }
			
			
			//std::cout << (*p)->getY() << " " << yT << std::endl;
			
			for (int i = 0; i < 21; i++) {
				lengthSquare = (*p)->intersection(xT, yT, (*d)->getZ(), i, 1.0f);
				if (lengthSquare == -1.0f) { inputs.at(i) = 0.0f; }
				else {
					if (lengthSquare >= MAXVIEW * MAXVIEW) { inputs.at(i) = 0.0f; }
					else {
						inputs.at(i) = std::max(inputs.at(i), 1 - std::sqrt(lengthSquare) / MAXVIEW);
					}
				}
			}
		}
		for (auto d = herbivore.begin(); d < p; d++) {
			if ((*p)->getX() - (*d)->getX() > 0.5f * simulationSizeX) { xT = (*d)->getX() + simulationSizeX; }
			else { xT = (*d)->getX(); }
			if ((*d)->getX() - (*p)->getX() > 0.5f * simulationSizeX) { xT = (*d)->getX() - simulationSizeX; }

			if ((*p)->getY() - (*d)->getY() > 0.5f * simulationSizeY) { yT = (*d)->getY() + simulationSizeY; }
			else { yT = (*d)->getY(); }
			if ((*d)->getY() - (*p)->getY() > 0.5f * simulationSizeY) { yT = (*d)->getY() - simulationSizeY; }

			if (((*p)->getX() - xT) * ((*p)->getX() - xT) + ((*p)->getY() - yT) * ((*p)->getY() - yT) <= 1.44f) {
				float dist = ((*p)->getX() - xT) * ((*p)->getX() - xT) + ((*p)->getY() - yT) * ((*p)->getY() - yT);
				float dx = (*p)->getX() - xT;
				float dy = (*p)->getY() - yT;
				//std::cout << dx << std::endl;
				(*p)->setX((*p)->getX() + 1.2f * dx / 2.0f * (1.0f / std::sqrtf(dist) - 1.0f));
				(*p)->setY((*p)->getY() + 1.2f * dy / 2.0f * (1.0f / std::sqrtf(dist) - 1.0f));
				(*d)->setX((*d)->getX() - 1.2f * dx / 2.0f * (1.0f / std::sqrtf(dist) - 1.0f));
				(*d)->setY((*d)->getY() - 1.2f * dy / 2.0f * (1.0f / std::sqrtf(dist) - 1.0f));
			}
		}
		

		(*p)->move(inputs, dt);

		if (abs((*p)->getSpeed()) < 0.001) {
			(*p)->setEnergy(std::min((*p)->getEnergy() + static_cast<float>(0.08 * dt), 1.0f));
		}

		(*p)->setTimer((*p)->getTimer() + 0.1f * dt);
		(*p)->setX(std::fmod((*p)->getX(), simulationSizeX));
		(*p)->setY(std::fmod((*p)->getY(), simulationSizeY));
		(*p)->render(Shader);

		
		if (((*p)->getEnergy() > 0.9f) && ((*p)->getTimer() > 1.0f)) {
			//std::cout << (*p)->getTimer() << " timer " << std::endl;
			srand(time(NULL) + timerSeed);
			timerSeed += 4127;
			p = herbivore.insert(p, new Creature((**p), true, std::rand()));
			(*p)->setTimer(-0.5f + 1.0f * static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX));
			//std::cout << (*p)->getTimer() << " newwwwwwwww" << std::endl;
			timerSeed += 1338;
			p++;
			(*p)->setTimer(-0.5f + 1.0f * static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX));
			//std::cout << (*p)->getTimer() << " ooooold" << std::endl;
			//p++;
		}
		(*p)->setX(std::fmod((*p)->getX(), simulationSizeX));
		if ((*p)->getX() < 0) {
			(*p)->setX((*p)->getX() + simulationSizeX);
		}
		(*p)->setY(std::fmod((*p)->getY(), simulationSizeY));
		if ((*p)->getY() < 0) {
			(*p)->setY((*p)->getY() + simulationSizeY);
		}
		//std::cout << (*p)->getTimer() << std::endl;
		p++;
		//std::cout << std::fmod((*p)->getX(), simulationSizeX) << std::endl;
	}

	p = carnivore.begin();
	while (p < carnivore.end()) {
		if ((*p)->getEnergy() < 0.0f) {
			delete (*p);
			p = carnivore.erase(p);
			continue;
		};
		auto d = herbivore.begin();
		while (d < herbivore.end()) {
			if ((*p)->getX() - (*d)->getX() > 0.5f * simulationSizeX) { xT = (*d)->getX() + simulationSizeX; }
			else { xT = (*d)->getX(); }
			if ((*d)->getX() - (*p)->getX() > 0.5f * simulationSizeX) { xT = (*d)->getX() - simulationSizeX; }

			if ((*p)->getY() - (*d)->getY() > 0.5f * simulationSizeY) { yT = (*d)->getY() + simulationSizeY; }
			else { yT = (*d)->getY(); }
			if ((*d)->getY() - (*p)->getY() > 0.5f * simulationSizeY) { yT = (*d)->getY() - simulationSizeY; }


			//std::cout << (*p)->getY() << " " << yT << std::endl;

			for (int i = 0; i < 21; i++) {
				lengthSquare = (*p)->intersection(xT, yT, (*d)->getZ(), i, 1.0f);
				if (lengthSquare == -1.0f) { inputs.at(i) = 0.0f; }
				else {
					if (lengthSquare >= MAXVIEW * MAXVIEW) { inputs.at(i) = 0.0f; }
					else {
						inputs.at(i) = std::max(inputs.at(i), 1 -  std::sqrt(lengthSquare)/ MAXVIEW);
					}
				}
			}
			if ((((*p)->getX() - xT) * ((*p)->getX() - xT) + ((*p)->getY() - yT) * ((*p)->getY() - yT) <= 1.0f) && ((*p)->getTimer() > 1.0f)) {
				//std::cout << "======================" << std::endl;
				//std::cout << (*p)->getX() << " " <<  (*d)->getX() << std::endl;
				//std::cout << (*p)->getY() << " " << (*d)->getY() << std::endl;
				//std::cout << ((*p)->getX() - xT) * ((*p)->getX() - xT) + ((*p)->getY() - yT) * ((*p)->getY() - yT) << std::endl;
				(*p)->setEnergy(std::min((*p)->getEnergy() + 0.2f, 1.0f));
				(*p)->setBirthCounter((*p)->getBirthCounter() + 0.4f);
				(*p)->setTimer(0.0f);
				//std::cout << (*p)->getTimer() << std::endl;
				d = herbivore.erase(d);
			}
			else {
				d++;
			}
		}

		for (auto d = carnivore.begin(); d < p; d++) {
			//if (((*p)->getX() == (*d)->getX())&&((*p)->getY() == (*d)->getY())) { continue; };
			if ((*p)->getX() - (*d)->getX() > 0.5f * simulationSizeX) { xT = (*d)->getX() + simulationSizeX; }
			else { xT = (*d)->getX(); }
			if ((*d)->getX() - (*p)->getX() > 0.5f * simulationSizeX) { xT = (*d)->getX() - simulationSizeX; }

			if ((*p)->getY() - (*d)->getY() > 0.5f * simulationSizeY) { yT = (*d)->getY() + simulationSizeY; }
			else { yT = (*d)->getY(); }
			if ((*d)->getY() - (*p)->getY() > 0.5f * simulationSizeY) { yT = (*d)->getY() - simulationSizeY; }

			if (((*p)->getX() - xT) * ((*p)->getX() - xT) + ((*p)->getY() - yT) * ((*p)->getY() - yT) <= 1.44f) {
				float dist = ((*p)->getX() - xT) * ((*p)->getX() - xT) + ((*p)->getY() - yT) * ((*p)->getY() - yT);
				float dx = (*p)->getX() - xT;
				float dy = (*p)->getY() - yT;
				//std::cout << dx << std::endl;
				(*p)->setX((*p)->getX() + 1.2f * dx / 2.0f * (1.0f / std::sqrtf(dist) - 1.0f));
				(*p)->setY((*p)->getY() + 1.2f * dy / 2.0f * (1.0f / std::sqrtf(dist) - 1.0f));
				(*d)->setX((*d)->getX() - 1.2f * dx / 2.0f * (1.0f / std::sqrtf(dist) - 1.0f));
				(*d)->setY((*d)->getY() - 1.2f * dy / 2.0f * (1.0f / std::sqrtf(dist) - 1.0f));
			}
		}

		(*p)->move(inputs, dt);
		(*p)->setX(std::fmod((*p)->getX(), simulationSizeX));
		if ((*p)->getX() < 0) {
			(*p)->setX((*p)->getX() + simulationSizeX);
		}
		(*p)->setY(std::fmod((*p)->getY(), simulationSizeY));
		if ((*p)->getY() < 0) {
			(*p)->setY((*p)->getY() + simulationSizeY);
		}
		if ((*p)->getEnergy() < 0.0f) {
			delete[] (*p);
			p = carnivore.erase(p);
			continue;
		};
		(*p)->setEnergy((*p)->getEnergy() - static_cast<float>(0.03 * dt));
		(*p)->setTimer((*p)->getTimer() + 5.0f * dt);
		if ((*p)->getBirthCounter() >= 0.99f) {
			(*p)->setBirthCounter((*p)->getBirthCounter() - 0.99f);
			p = carnivore.insert(p, new Creature((**p), true, std::rand()));
			p++;
		}
		//std::cout << (*p)->getEnergy() << std::endl;
		(*p)->render(Shader);
		p++;
	}
}
