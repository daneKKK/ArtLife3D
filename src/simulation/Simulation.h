#ifndef SIMULATION_H
#define SIMULATION_H

#include "Creature.h"

#include <array>
#include <vector>

class Simulation final 
{
private:
    unsigned int simulationSizeX, simulationSizeY, simulationSizeZ;

    std::vector<Creature> herbivore;
    std::vector<Creature> carnivore;

public:
    Simulation(unsigned int x, unsigned int y, unsigned int z);
    
};

#endif //SIMULATION_H