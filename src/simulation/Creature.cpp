#include "Creature.h"

Creature::Creature(const float xInput, const float yInput, const float zInput, 
    const float angleXYInput, const float angleYZInput, 
    const float fovXYInput, const float fovYZInput, 
    const unsigned int numberOfRaysXYInput, const unsigned int numberOfRaysYZInput,
    const float hungerInput):
    fovXY(fovXYInput), fovYZ(fovYZInput), 
    numberOfRaysXY(numberOfRaysXYInput), numberOfRaysYZ(numberOfRaysYZInput),
    hungerFactor(hungerInput) {
    x = xInput;
    y = yInput;
    z = zInput;
    angleXY = angleXYInput;
    angleYZ = angleYZInput;
    energy = MAXENERGY;
}

Creature::Creature(const Creature& base): 
    fovXY(base.getFovXY()), fovYZ(base.getFovYZ()),
    numberOfRaysXY(base.getNumberOfRaysXY()), numberOfRaysYZ(base.getNumberOfRaysYZ()), hungerFactor(base.getHungerFactor()) {
    x = base.getX();
    y = base.getY();
    z = base.getZ();
    angleXY = base.getAngleXY();
    angleYZ = base.getAngleYZ();
    brain = base.brainCopy();

}

Creature::~Creature() {
}


Creature& Creature::operator=(const Creature& base) {
    if (this == &base) {
        return *this;
    }

    brain = base.brainCopy();
    float tmpX = base.getX();
    float tmpY = base.getY();
    float tmpZ = base.getZ();
    float tmpAngleXY = base.getAngleXY();
    float tmpAngleYZ = base.getAngleYZ();
    
    x = tmpX;
    y = tmpY;
    z = tmpZ;
    angleXY = tmpAngleXY;
    angleYZ = tmpAngleYZ;

    brain = std::move(base.brainCopy());

    return *this;
}

NeuralNetwork Creature::brainCopy() const {
    NeuralNetwork a(brain);
    return a;
}

float Creature::getX() const{
    return x;
}

float Creature::getY() const {
    return y;
}

float Creature::getZ() const {
    return z;
}

float Creature::getAngleXY() const {
    return angleXY;
}

float Creature::getAngleYZ() const {
    return angleYZ;
}

float Creature::getFovXY() const {
    return fovXY;
}

float Creature::getFovYZ() const {
    return fovYZ;
}

unsigned int Creature::getNumberOfRaysXY() const {
    return numberOfRaysXY;
}

unsigned int Creature::getNumberOfRaysYZ() const {
    return numberOfRaysYZ;
}

float Creature::getBirthCounter() const
{
    return birthCounter;
}

void Creature::setBirthCounter(float birthCounterInput) {
    birthCounter = birthCounterInput;
}

void Creature::move(std::vector<float> &input) {
    float speed, angularSpeed;
    brain.calculateOutputs(input);
    speed = brain.getOutput(0);
    angularSpeed = brain.getOutput(1);

    x += speed * std::cos(angleXY);
    y += speed * std::sin(angleXY);
    angleXY += angularSpeed;

    lastSpeed = speed;
    energy -= abs(speed) * hungerFactor;
}

float Creature::getEnergy() const
{
    return energy;
}

void Creature::setEnergy(float energyInput) {
    energy = energyInput;
}

float Creature::getHungerFactor() const {
    return hungerFactor;
}
