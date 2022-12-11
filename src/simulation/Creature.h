#ifndef MEMORY
#include <memory>
#endif

#include "neuralnetwork/NeuralNetwork.h"

class Creature {
private:
    float x, y, z, angleXY, angleYZ;
    const float fovXY;
    const float fovYZ;
    const unsigned int numberOfRaysXY;
    const unsigned int numberOfRaysYZ;
    std::unique_ptr<NeuralNetwork> brain;
public:
    Creature(const float x, const float y, const float z, 
        const float angleXY, const float angleYZ, 
        const float fovXY, const float fovYZ, 
        const unsigned int numberOfRaysXY, const unsigned int numberOfRaysYZ);
    Creature(const Creature& base);
    ~Creature();
    Creature& operator=(const Creature& base);
    std::unique_ptr<NeuralNetwork> brainCopy() const;
    float getX() const;
    float getY() const;
    float getZ() const;
    float getAngleXY() const;
    float getAngleYZ() const;
    float getFovXY() const;
    float getFovYZ() const;
    unsigned int getNumberOfRaysXY() const;
    unsigned int getNumberOfRaysYZ() const;
    void move(float* brainInput);
};
