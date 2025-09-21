#include "construtores.cpp"
#include "buscaLocal.cpp"

// Grasp com busca local randomImprovement
void graspRandom(int m, int max, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    s = construtorGulosoAleatorio(m, cap, s, 0.2 ,d, b, ma);
    vector<int> fs = funcaoObjetivo(s, ma, d, b);
    cout << "Beneficio pos construcao: " << fs[0] << " peso pos construcao: " << fs[1] << endl;
    s = randomImprovement(m, max, cap, s, b, d, ma);
    fs = funcaoObjetivo(s, ma, d, b);
    cout << "Beneficio pos busca randomizado: " << fs[0] << " peso pos busca randomizado: " << fs[1] << endl;
}

// Grasp com busca local firstImprovement
void graspFirst(int m, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    s = construtorGulosoAleatorio(m, cap, s, 0.2 ,d, b, ma);
    vector<int> fs = funcaoObjetivo(s, ma, d, b);
    cout << "Beneficio pos construcao: " << fs[0] << " peso pos construcao: " << fs[1] << endl;
    s = firstImprovement(m, cap, s, b, d, ma);
    fs = funcaoObjetivo(s, ma, d, b);
    cout << "Beneficio pos busca first: " << fs[0] << " peso pos busca first: " << fs[1] << endl;
}

// Grasp com busca local bestImprovement
void graspBest(int m, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    s = construtorGulosoAleatorio(m, cap, s, 0.2 ,d, b, ma);
    vector<int> fs = funcaoObjetivo(s, ma, d, b);
    cout << "Beneficio pos construcao: " << fs[0] << " peso pos construcao: " << fs[1] << endl;
    s = bestImprovement(m, cap, s, b, d, ma);
    fs = funcaoObjetivo(s, ma, d, b);
    cout << "Beneficio pos busca best: " << fs[0] << " peso pos busca best: " << fs[1] << endl;
}

int main(){
    int m, n, ne, cap;
    vector<int> d, b;
    vector<vector<int>> ma;
    leArquivo(d, b, ma, "prob-software.txt",&m, &n, &ne, &cap);
    vector<int> p(m, 0);
    graspRandom(m, 10, cap, p, b, d, ma);
    //graspFirst(m, cap, p, b, d, ma);
    //graspBest(m, cap, p, b, d, ma);
    return 0;
}