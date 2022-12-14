#ifndef SIMULATION_H
#define SIMULATION_H

#include "Creature.h"

#include <array>
#include <vector>
#include <algorithm>
//#include <iostream>

class Simulation final 
{
private:
    float simulationSizeX, simulationSizeY, simulationSizeZ;
    float const MAXVIEW;

    std::vector<Creature*> herbivore;
    std::vector<Creature*> carnivore;

    int timerSeed = 0;

public:
    Simulation(float x, float y, float z, float maxview, int herbiCount, int carniCount);
    ~Simulation();

    void step(const float dt, shader Shader);

};

#endif //SIMULATION_H