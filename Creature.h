#include "NeuralNetwork.h"

class Creature {
private:
    float x, y, z, angleXY, angleYZ;
    NeuralNetwork brain;
public:
    Creature(float x, float y, float angle);
    Creature(&Creature base);
    ~Creature() {
        delete[] brain;
    }
    Creature& operator=(const &Creature base) {
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
    NeuralNetwork* brainCopy() {
        NeuralNetwork* newBrain = new NeuralNetwork(brain);
        return newBrain;
    }
    float getX() {
        return x;
    }
    float getY() {
        return y;
    }
    float getAngle() {
        return angle;
    }
}
