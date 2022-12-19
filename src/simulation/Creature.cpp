#include "Creature.h"

Creature::Creature(const float xInput, const float yInput, const float zInput, 
    const float angleXYInput, const float angleYZInput, 
    const float fovXYInput, const float fovYZInput, 
    const unsigned int numberOfRaysXYInput, const unsigned int numberOfRaysYZInput,
    const float hungerInput, const float rColor, const float gColor, const float bColor):
    fovXY(fovXYInput), fovYZ(fovYZInput), 
    numberOfRaysXY(numberOfRaysXYInput), numberOfRaysYZ(numberOfRaysYZInput),
    hungerFactor(hungerInput), rColor(rColor), gColor(gColor), bColor(bColor) {
    x = xInput;
    y = yInput;
    z = zInput;
    angleXY = angleXYInput;
    angleYZ = angleYZInput;
    energy = 1.0f;
    graphicsObject.init();
    brain = NeuralNetwork(numberOfRaysXY * numberOfRaysYZ + 1);
    timer = 0.0f;
}

Creature::Creature(const Creature& base): 
    fovXY(base.getFovXY()), fovYZ(base.getFovYZ()),
    numberOfRaysXY(base.getNumberOfRaysXY()), numberOfRaysYZ(base.getNumberOfRaysYZ()), hungerFactor(base.getHungerFactor()), 
    rColor(base.getRColor()), gColor(base.getGColor()), bColor(base.getBColor()) {
    x = base.getX();
    y = base.getY();
    z = base.getZ();
    angleXY = base.getAngleXY();
    angleYZ = base.getAngleYZ();
    brain = std::move(base.brainCopy());
    graphicsObject.init();
    timer = base.getTimer();
    energy = base.getEnergy();
}

Creature::Creature(const Creature& base, bool mutate, int seed) :
    fovXY(base.getFovXY()), fovYZ(base.getFovYZ()),
    numberOfRaysXY(base.getNumberOfRaysXY()), numberOfRaysYZ(base.getNumberOfRaysYZ()), hungerFactor(base.getHungerFactor()),
    rColor(base.getRColor()), gColor(base.getGColor()), bColor(base.getBColor()) {
    srand(time(NULL) + (int)this + seed + randSeed);
    randSeed += 834 + std::rand();
    //std::cout << seed << "   " << std::rand() << std::endl;
    x = base.getX();
    y = base.getY();
    z = base.getZ();
    angleXY = base.getAngleXY();
    if (mutate) {
        angleXY = 3.142f * static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX);
        //std::cout << angleXY << std::endl;
        x = x + std::cos(angleXY) * 1.0f;
        y = y + std::sin(angleXY) * 1.0f;
    };
    angleYZ = base.getAngleYZ();
    energy = 0.0f;
    brain = NeuralNetwork(base.brainCopy(), mutate);
    graphicsObject.init();
    timer = base.getTimer();
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

float Creature::getTimer() const
{
    return timer;
}

void Creature::setTimer(const float t)
{
    if ((abs(t - timer) > 0.1f)&&(timer < 5.0f)) {
        std::cout << "CHANGING TIMER FROM " << timer << " TO " << t << std::endl;
    }
    timer = t;
}

void Creature::setX(float xI)
{
    x = xI;
}

void Creature::setY(float yI)
{
    y = yI;
}

void Creature::setZ(float zI)
{
    z = zI;
}

float Creature::getRColor() const
{
    return rColor;
}

float Creature::getGColor() const
{
    return gColor;
}

float Creature::getBColor() const
{
    return bColor;
}

float Creature::getSpeed() const
{
    return lastSpeed;
}

float Creature::intersection(float xInput, float yInput, float zInput, int rayNumber, float radius)
{
    float currentAngle = angleXY - fovXY + 2 * fovXY * (static_cast<float> (rayNumber) / static_cast<float> (numberOfRaysXY));
    float vX = std::cos(currentAngle);
    float vY = std::sin(currentAngle);
    float xRel = xInput - x;
    float yRel = yInput - y;
    if ((-1 * vY * (xRel)+vX * (yRel)+radius) * (-1 * vY * (xRel)+vX * (yRel)-radius) < 0) {
        return xRel * xRel + yRel * yRel;
    }
    else {
        return -1.0f;
    }
}

unsigned int Creature::getNumberOfRaysYZ() const {
    return numberOfRaysYZ;
}

float Creature::getBirthCounter() const
{
    return birthCounter;
}

void Creature::setBirthCounter(const float birthCounterInput) {
    birthCounter = birthCounterInput;
}

void Creature::move(std::vector<float> &input, float dt) {
    float speed, angularSpeed;
    brain.calculateOutputs(input);
    speed = 2 * (brain.getOutput(0) - 0.5f);
    angularSpeed = 2 * (brain.getOutput(1) - 0.5f);

    x += 5 * dt * speed * std::cos(angleXY);
    y += 5 * dt * speed * std::sin(angleXY);
    angleXY += angularSpeed * static_cast<float>(dt) * 0.3f;

    //std::cout << speed << " " << angularSpeed << std::endl;
    lastSpeed = speed;
    energy -= abs(speed) * hungerFactor * 0.1f * dt;
    //std::cout << energy << std::endl;
}

float Creature::getEnergy() const
{
    return energy;
}

void Creature::setEnergy(const float energyInput) {
    if (energy - energyInput < -0.01f) {
        std::cout << "ADDITION OF " << energyInput - energy << " TO " << energy << std::endl;
    }
    energy = energyInput;
}

float Creature::getHungerFactor() const {
    return hungerFactor;
}

void Creature::render(shader Shader) const {
    float e = energy;
    graphicsObject.render(Shader, { x, z, y }, {rColor * e, gColor * e, bColor * e, 0.0f});
}

int Creature::randSeed = -1;