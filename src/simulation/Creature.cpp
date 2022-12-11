#include "Creature.h"
#include "neuralnetwork/NeuralNetwork.h"

Creature::Creature(const float xInput, const float yInput, const float zInput, const float angleXYInput, const float angleYZInput) {
    x = xInput;
    y = yInput;
    z = zInput;
    angleXY = angleXYInput;
    angleYZ = angleYZInput;
}

Creature::Creature(Creature& base) {
    x = base.getX();
    y = base.getY();
    z = base.getZ();
    angleXY = base.getAngleXY();
    angleYZ = base.getAngleYZ();
    brain = base.brainCopy();
}

Creature::~Creature() {
        delete[] brain;
}


Creature& Creature::operator=(const Creature& base) {
    if (this == &base) {
        return *this;
    }

    brain = base.brainCopy();
    float tmpX = base.getX();
    float tmpY = base.getY();
    float tmpAngle = base.getAngle();
    x = tmpX;
    y = tmpY;
    angle = tmpAngle;

    return *this;
}

NeuralNetwork* Creature::brainCopy() {
    NeuralNetwork* newBrain = new NeuralNetwork(brain);
    return newBrain;
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

float Creature::getFov() const {
    return fov;
}

float Creature::getNumberOfRays() const {
    return numberOfRays;
}
