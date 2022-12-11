#ifndef MEMORY
#include <memory>
#endif

#include "neuralnetwork/NeuralNetwork.h"

class Creature {
private:
    float x, y, z, angleXY, angleYZ;
    const float fov;
    const unsigned int numberOfRays;
    std::unique_ptr<NeuralNetwork> brain;
public:
    Creature(const float x, const float y, const float z, const float angleXY, const float angleYZ, const float fov, const unsigned int numberOfRays);
    Creature(const Creature& base);
    ~Creature();
    Creature& operator=(const Creature& base);
    std::unique_ptr<NeuralNetwork> brainCopy() const;
    float getX() const;
    float getY() const;
    float getZ() const;
    float getAngleXY() const;
    float getAngleYZ() const;
    float getFov() const;
    float getNumberOfRays() const;
    void move(float* brainInput);
};
