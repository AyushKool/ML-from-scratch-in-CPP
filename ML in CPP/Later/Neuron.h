#pragma once 
#include <stdio.h>
#include <vector>
#include <cmath>

class Neuron {
public:
    double output;
    double delta;
    std::vector<double> weights;
    Neuron(int, int);
    void initializeWeights(int);
};