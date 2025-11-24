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
    vector<int> conflicts;
} TI;

typedef struct bin {
    int id;
    double current_weight;
    vector<int> items;
} TB;

#endif