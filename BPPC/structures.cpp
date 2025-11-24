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

bool verifyConflict(const TB &bin, const TI &item){
    for(int item_bin: bin.items){
        for(int item_to_pack: item.conflicts){
            if(item_bin==item_to_pack) return true;
        }
    }
    return false;
}

#endif