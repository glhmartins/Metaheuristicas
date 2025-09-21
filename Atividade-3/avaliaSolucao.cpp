#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int peso(vector<int> p, vector<vector<int>> ma, vector<int> d){
    int sum = 0;
    vector<int> v;
    for(int i = 0; i<ma.size(); i++){
        auto it = find(v.begin(), v.end(), ma[i][1]);
        if((it == v.end()) && (p[ma[i][0]]==1)){
            sum += d[ma[i][1]];
            v.push_back(ma[i][1]);
        }
    }
    return sum;
}

int beneficio(vector<int> p, vector<int> b){
    int sum = 0;
    for(int i = 0; i<p.size(); i++){
        if (p[i] == 1) sum += b[i];
    }
    return sum;
}

vector<int> funcaoObjetivo(vector<int> p, vector<vector<int>> ma, vector<int> d, vector<int> b){
    vector<int> bd;
    bd.push_back(beneficio(p, b));
    bd.push_back(peso(p, ma, d));
    return bd;
}
