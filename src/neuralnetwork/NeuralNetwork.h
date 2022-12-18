#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include <array>
#include <random>
#include <memory>
#include <iostream>

#include "Neuron.h"


class NeuralNetwork final 
{
private:
    std::array<std::array<Neuron*, 10>, 4> network;
    std::array<Neuron*, 3> output;

    const unsigned int inputSize;

    unsigned int existingNeurons;

    float uniformRand();

    float getOneOutput(int x, int y);

public:
    NeuralNetwork();
    NeuralNetwork(unsigned int inputSize);
    NeuralNetwork(const NeuralNetwork& base);
    NeuralNetwork(const NeuralNetwork& base, bool mutate);

    NeuralNetwork& operator=(const NeuralNetwork& base);

    unsigned int getInputSize() const;

    unsigned int getExistingNeurons() const;

    std::array<std::array<Neuron*, 10>, 4> copyNetwork() const;
    std::array<Neuron*, 3> copyOutput() const;

    void calculateOutputs(std::vector<float> &input);

    float getOutput(int i) const;
};

#endif //NEURALNETWORK_H