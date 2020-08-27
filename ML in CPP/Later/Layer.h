#pragma once
#include "Neuron.h"
#include <stdint.h>
#include <vector>

class Layer {

public:
    int currentLayerSize;
    std::vector<Neuron*> neurons;
    std::vector<double> layerOutputs;
    Layer(int, int);
};