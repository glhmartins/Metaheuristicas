#include <iostream>
#include <cmath>
#include <ctime>
#include "leitorArquivo.cpp"
#include "sortGuloso.cpp"

using namespace std;

int somaDependenciasAleatorio(int i, vector<vector<int>> ma, vector<int> d){
    int j = i, sum = 0;
    while(i == j){
        sum += d[ma[i][1]];
        i++;
    }
    return sum;
}

int somaDependenciasGuloso(int i, vector<vector<int>> ma, vector<int> d){
    int j = i, sum = 0;
    while(i == j){
        sum += d[ma[i][1]];
        i++;
    }
    return sum;
}

/* Incompleto
void aleatorio(int m, int cap, int p[], vector<int> d, vector<int> b, vector<vector<int>> ma){
    srand(time(NULL));
    int pa = 0, r = rand()%m, sum = 0;
    do {
        to do
    } while((pa+p[r]<=cap));
    for (int i = 0; i<m; i++) cout << p[i];
    cout << endl << "Beneficio total dos pacotes escolhidos aleatoriamente: " << sum << endl;
}*/

void guloso(int m, int n, int ne, int cap, int p[], vector<int> d, vector<int> b, vector<vector<int>> ma){
    int i = 0, pa = 0, sumDeps = 0, be = 0, pos[m];
    for(int k = 0; k<m; k++) pos[k] = k;
    mergesort(b, pos, 0, m);
    while((i<m)){ 
        sumDeps = somaDependenciasGuloso(pos[i], ma, d);
        if(pa+sumDeps>cap) break;
        else {
            pa += sumDeps;
            p[i] = 1;
            be += b[i];
        }
        i++;
    }
    for(int k = 0; k<m; k++) cout << p[k];
    cout << endl << "capacidade usada: " << pa << ", capacidade maxima: " << cap << endl;
    cout << "beneficio: " << be << endl;
}

int main(){
    int m, n, ne, cap;
    vector<int> d, b;
    vector<vector<int>> ma;
    leArquivo(d, b, ma, "prob-software.txt",&m, &n, &ne, &cap);
    int p[m];
    for(int i = 0; i<m; i++) p[i] = 0;
    //aleatorio();
    guloso(m, n, ne, cap, p, d, b, ma);
    return 0;
}