#include "construtores.cpp"
#include "buscaLocal.cpp"

void randomAscentMethod(int m, int max, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    s = construtorAleatorio(m, cap, s, d, b, ma);
    vector<int> fs = funcaoObjetivo(s, ma, d, b);
    cout << "Beneficio pos construcao: " << fs[0] << endl << "peso pos construcao: " << fs[1] << endl;
    s = randomImprovement(m, max, cap, s, b, d, ma);
    fs = funcaoObjetivo(s, ma, d, b);
    cout << "Beneficio pos busca randomizado: " << fs[0] << endl << "peso pos busca randomizado: " << fs[1] << endl;
}

void firstAscentMethod(int m, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    s = construtorAleatorio(m, cap, s, d, b, ma);
    vector<int> fs = funcaoObjetivo(s, ma, d, b);
    cout << "Beneficio pos construcao: " << fs[0] << endl << "peso pos construcao: " << fs[1] << endl;
    s = firstImprovement(m, cap, s, b, d, ma);
    fs = funcaoObjetivo(s, ma, d, b);
    cout << "Beneficio pos busca first: " << fs[0] << endl << "peso pos busca first: " << fs[1] << endl;
}

void bestAscentMethod(int m, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    s = construtorAleatorio(m, cap, s, d, b, ma);
    vector<int> fs = funcaoObjetivo(s, ma, d, b);
    cout << "Beneficio pos construcao: " << fs[0] << endl << "peso pos construcao: " << fs[1] << endl;
    s = bestImprovement(m, cap, s, b, d, ma);
    fs = funcaoObjetivo(s, ma, d, b);
    cout << "Beneficio pos busca best: " << fs[0] << endl << "peso pos busca best: " << fs[1] << endl;
}

int main(){
    int m, n, ne, cap;
    vector<int> d, b;
    vector<vector<int>> ma;
    leArquivo(d, b, ma, "prob-software.txt",&m, &n, &ne, &cap);
    vector<int> p(m, 0);
    //randomAscentMethod(m, 25, cap, p, b, d, ma);
    firstAscentMethod(m, cap, p, b, d, ma);
    //bestAscentMethod(m, cap, p, b, d, ma);
    return 0;
}