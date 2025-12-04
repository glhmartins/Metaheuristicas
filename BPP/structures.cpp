#ifndef STRUCTURES_CPP
#define STRUCTURES_CPP

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cmath>

using namespace std;

typedef struct item {
    int id;
    double weight;
} TI;

typedef struct bin {
    int id;
    double current_weight;
    vector<int> items;
} TB;

double calculateFitness(const vector<TB> &bins, double capacity) {
    double fitness = 0.0, fillRatio;
    for (const auto &bin : bins) {
        if (!bin.items.empty()) {
            fillRatio = (double) (bin.current_weight / capacity);
            fitness += (fillRatio * fillRatio);
        }
    }
    return fitness;
}

#endif