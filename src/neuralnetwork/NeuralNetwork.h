#ifndef ARRAY
#include <array>
#endif
#ifndef RANDOM
#include <random>
#endif // !RANDOM
#ifndef MEMORY
#include <memory>
#endif

#include "neuralnetwork/Neuron.h"


class NeuralNetwork final {
private:
    std::array<std::array<Neuron*, 10>, 4> network;
    std::array<Neuron*, 3> output;
    const unsigned int inputSize;
    unsigned int existingNeurons;
    float uniformRand() {
        return static_cast <float> (std::rand()) / static_cast <float> (RAND_MAX);
    }
    float getOneOutput(int x, int y) {
        return network.at(y).at(x)->getOutput();
    }
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
