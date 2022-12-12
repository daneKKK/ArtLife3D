#include "simulation/Creature.h"

#ifndef ARRAY
#include <array>
#endif // !ARRAY

#ifndef VECTOR
#include <vector>
#endif

class Simulation final {
private:
    unsigned int simulationSizeX, simulationSizeY, simulationSizeZ;
    std::vector<Creature> herbivore;
    std::vector<Creature> carnivore;
public:
    Simulation(unsigned int x, unsigned int y, unsigned int z);
    
};
