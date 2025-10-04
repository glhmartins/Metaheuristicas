#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int peso(vector<bool> &p, vector<vector<int>> &ma, vector<int> d){
    int sum = 0;
    for(int i = 0; i<ma.size(); i++){
        if(p[ma[i][0]]==1){
            sum += d[ma[i][1]];
            d[ma[i][1]] = 0;
        }
    }
    return sum;
}

int beneficio(vector<bool> &p, vector<int> &b){
    int sum = 0;
    for(int i = 0; i<b.size(); i++) sum += (b[i]*p[i]);
    return sum;
}

vector<int> funcaoObjetivo(vector<bool> &p, vector<vector<int>> &ma, vector<int> &d, vector<int> &b){
    vector<int> bd;
    bd.push_back(beneficio(p, b));
    bd.push_back(peso(p, ma, d));
    return bd;
}
