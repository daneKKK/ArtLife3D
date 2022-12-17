#ifndef CREATURE_H
#define CREATURE_H

#include <memory>
#include <vector>
#include <cmath>

#include "../neuralnetwork/NeuralNetwork.h"
#include "../graphics/models/cube.hpp"

class Creature 
{
private:
    float x, y, z, angleXY, angleYZ; 

    const float fovXY;
    const float fovYZ;
    const float rColor, gColor, bColor;

    const unsigned int numberOfRaysXY;
    const unsigned int numberOfRaysYZ;

    NeuralNetwork brain;
    cube graphicsObject;

    const float MAXENERGY = 500.0f;
    const float MAXVELOCITY = 1;
    const float MAXANGULARVELOCITY = 0.04f;

    float energy = MAXENERGY;
    float birthCounter = 0.0f;
    float lastSpeed = 0.0f;

    const float hungerFactor;

    float timer = 1.0f;

public:
    Creature(const float x, const float y, const float z,
        const float angleXY, const float angleYZ,
        const float fovXY, const float fovYZ,
        const unsigned int numberOfRaysXY, const unsigned int numberOfRaysYZ, const float hungerInput,
        const float rColor, const float gColor, const float bColor);

    Creature(const Creature& base);

    ~Creature();

    Creature& operator=(const Creature& base);

    NeuralNetwork brainCopy() const;

    float getX() const;
    float getY() const;
    float getZ() const;

    float getAngleXY() const;
    float getAngleYZ() const;

    float getFovXY() const;
    float getFovYZ() const;
    float getRColor() const;
    float getGColor() const;
    float getBColor() const;

    unsigned int getNumberOfRaysXY() const;
    unsigned int getNumberOfRaysYZ() const;

    void move(std::vector<float> &brainInput);

    float getEnergy() const;
    void setEnergy(float energyInput);

    float getBirthCounter() const;
    void setBirthCounter(float birthCounterInput);

    float getHungerFactor() const;

    float getTimer() const;
    void setTimer(const float t);

    void render(shader Shader) const;
};

#endif //CREATURE_H