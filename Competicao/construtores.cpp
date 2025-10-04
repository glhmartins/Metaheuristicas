#include <cmath>
#include <ctime>
#include <algorithm>
#include "leitorArquivo.cpp"
#include "sortGuloso.cpp"

using namespace std;

int somaDependencia(int &p, vector<vector<int>> &ma, vector<int> &d){
    int sum = 0;
    for(int i = 0; i<ma.size(); i++){
        if(ma[i][0] == p){
            sum += d[ma[i][1]];
            d[ma[i][1]] = 0;
        }
    }
    return sum;
}

vector<bool> construtorGulosoAleatorio(int &m, int &cap, vector<bool> p, float fator, vector<int> d, vector<int> b, vector<vector<int>> &ma){
    int pa = 0, sumDeps = 0, be = 0, r = (rand()%(m-1))*fator;
    vector<int> pos;
    for(int k = 0; k<m; k++) pos.push_back(k);
    mergesort(b, pos, 0, m-1);
    while(pa<cap){
        sumDeps = somaDependencia(pos[r], ma, d);
        if(pa+sumDeps>cap) break;
        p[pos[r]] = true;
        be += b[r];
        pa += sumDeps;
        b.erase(b.begin()+r);
        pos.erase(pos.begin()+r);
        r = (rand()%pos.size())*fator;
    }
    return p;
}

vector<bool> construtorAleatorio(int &m, int &cap, vector<bool> p, vector<int> d, vector<int> b, vector<vector<int>> &ma){
    int pa = 0, r = rand()%(m-1), sumDeps = 0, be = 0;
    vector<int> pos;
    for(int k = 0; k<m; k++) pos.push_back(k);
    while(pa<cap){
        sumDeps = somaDependencia(pos[r], ma, d);
        if(pa+sumDeps>cap) break;
        p[pos[r]] = true;
        be += b[r];
        pa += sumDeps;
        b.erase(b.begin()+r);
        pos.erase(pos.begin()+r);
        r = rand()%pos.size();
    }
    return p;
}

vector<bool> construtorGuloso(int &m, int &cap, vector<bool> p, vector<int> d, vector<int> b, vector<vector<int>> &ma){
    int i = 0, pa = 0, sumDeps = 0, be = 0;
    vector<int> pos;
    for(int k = 0; k<m; k++) pos.push_back(k);
    mergesort(b, pos, 0, m-1);
    while((i<m)){ 
        sumDeps = somaDependencia(pos[i], ma, d);
        if(pa+sumDeps>cap) break;
        pa += sumDeps;
        p[pos[i]] = true;
        be += b[i];
        i++;
    }
    return p;
}
