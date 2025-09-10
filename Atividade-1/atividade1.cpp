#include <iostream>
#include <cmath>
#include <ctime>
#include <algorithm>
#include "leitorArquivo.cpp"
#include "sortGuloso.cpp"

using namespace std;

// Soma o custo de todas as dependencias do pacote i
int somaDependencias(int p, vector<vector<int>> ma, vector<int> d, vector<int> &v){
    int sum = 0;
    for(int i = 0; i<ma.size(); i++){
        if(ma[i][0] == p){
            auto it = find(v.begin(), v.end(), ma[i][1]);
            if(it == v.end()){
                sum += d[ma[i][1]];
                v.push_back(ma[i][1]);
            }
        }
        cout << ma[i][0] << " " << ma[i][1] << endl;
    }
    return sum;
}

void gulosoAleatorio(int m, int n, int ne, int cap, vector<int> &p, float fator, vector<int> d, vector<int> b, vector<vector<int>> ma){
    srand(time(NULL));
    int i = 0, pa = 0, sumDeps = 0, be = 0, r = (rand()%m)*fator;
    vector<int> pos, v;
    for(int k = 0; k<m; k++) pos.push_back(k);
    mergesort(b, pos, 0, m-1);
    while(pa<cap){
        sumDeps = somaDependencias(pos[r], ma, d, v);
        if(pa+sumDeps>cap) break;
        p[pos[r]] = 1;
        be += b[pos[r]];
        pa += sumDeps;
        pos.erase(pos.begin()+r);
        r = (rand()%pos.size())*fator;
        cout << r << " ";
    }
    cout << endl;
    for(int k = 0; k<m; k++) cout << p[k];
    cout << endl << "capacidade usada: " << pa << ", capacidade maxima: " << cap << endl;
    cout << "beneficio: " << be << endl;
}

/* 
   Utilizo o vetor pos para acessar as posições, toda vez que acesso uma posição
   eu removo ela do vetor, impedindo que fique caindo sempre na mesma posição já acessada
*/
void aleatorio(int m, int n, int ne, int cap, vector<int> &p, vector<int> d, vector<int> b, vector<vector<int>> ma){
    srand(time(NULL));
    // pa = peso atual (custo), "r" recebe o numero aleatorio gerado e 'be' soma os beneficios
    int pa = 0, r = rand()%m, sumDeps = 0, be = 0;
    vector<int> pos, v;
    for(int k = 0; k<m; k++) pos.push_back(k);
    while(pa<cap){
        sumDeps = somaDependencias(pos[r], ma, d, v);
        if(pa+sumDeps>cap) break;
        p[pos[r]] = 1;
        be += b[pos[r]];
        pa += sumDeps;
        pos.erase(pos.begin()+r);
        r = rand()%pos.size();
    }
    for(int k = 0; k<m; k++) cout << p[k];
    cout << endl << "capacidade usada: " << pa << ", capacidade maxima: " << cap << endl;
    cout << "beneficio: " << be << endl;
}

/* 
   No guloso eu utilizo o pos para acessar as posições de forma 
   crescente depois de ter ordenado o vetor
*/
void guloso(int m, int n, int ne, int cap, vector<int> &p, vector<int> d, vector<int> b, vector<vector<int>> ma){
    // i = indice posicao, pa = peso atual (custo), be = beneficio da solução
    int i = 0, pa = 0, sumDeps = 0, be = 0;
    vector<int> pos, v;
    for(int k = 0; k<m; k++) pos.push_back(k);
    mergesort(b, pos, 0, m-1);
    while((i<m)){ 
        sumDeps = somaDependencias(pos[i], ma, d, v);
        if(pa+sumDeps>cap) break;
        pa += sumDeps;
        p[pos[i]] = 1;
        be += b[i];
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
    vector<int> p(m, 0);
    //aleatorio(m, n, ne, cap, p, d, b, ma);
    guloso(m, n, ne, cap, p, d, b, ma);
    //gulosoAleatorio(m, n, ne, cap, p, 0, d, b, ma);
    return 0;
}
