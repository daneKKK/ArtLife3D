#ifndef SIMULATION_H
#define SIMULATION_H

#include "Creature.h"

#include <array>
#include <vector>

class Simulation final 
{
private:
    float simulationSizeX, simulationSizeY, simulationSizeZ;

    std::vector<Creature> herbivore;
    std::vector<Creature> carnivore;

public:
    Simulation(float x, float y, float z);
    void step(float dt, shader Shader);

};

#endif //SIMULATION_H