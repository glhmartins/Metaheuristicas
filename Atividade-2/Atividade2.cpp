#include "construtores.cpp"
#include "buscaLocal.cpp"

void randomAscentMethodSwap(int m, int max, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    s = construtorAleatorio(m, cap, s, d, b, ma);
    vector<int> fs = funcaoObjetivo(s, ma, d, b);
    cout << "Beneficio pos construcao: " << fs[0] << " peso pos construcao: " << fs[1] << endl;
    s = randomSwapImprovement(m, max, cap, s, b, d, ma);
    fs = funcaoObjetivo(s, ma, d, b);
    cout << "Beneficio pos busca randomizado: " << fs[0] << " peso pos busca randomizado: " << fs[1] << endl;
}

void firstAscentMethodSwap(int m, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    s = construtorAleatorio(m, cap, s, d, b, ma);
    vector<int> fs = funcaoObjetivo(s, ma, d, b);
    cout << "Beneficio pos construcao: " << fs[0] << " peso pos construcao: " << fs[1] << endl;
    s = firstSwapImprovement(m, cap, s, b, d, ma);
    fs = funcaoObjetivo(s, ma, d, b);
    cout << "Beneficio pos busca first: " << fs[0] << " peso pos busca first: " << fs[1] << endl;
}

void bestAscentMethodSwap(int m, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    s = construtorAleatorio(m, cap, s, d, b, ma);
    vector<int> fs = funcaoObjetivo(s, ma, d, b);
    cout << "Beneficio pos construcao: " << fs[0] << " peso pos construcao: " << fs[1] << endl;
    s = bestSwapImprovement(m, cap, s, b, d, ma);
    fs = funcaoObjetivo(s, ma, d, b);
    cout << "Beneficio pos busca best: " << fs[0] << " peso pos busca best: " << fs[1] << endl;
}

void randomAscentMethodFlip(int m, int max, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    s = construtorAleatorio(m, cap, s, d, b, ma);
    vector<int> fs = funcaoObjetivo(s, ma, d, b);
    cout << "Beneficio pos construcao: " << fs[0] << " peso pos construcao: " << fs[1] << endl;
    s = randomFlipImprovement(m, max, cap, s, b, d, ma);
    fs = funcaoObjetivo(s, ma, d, b);
    cout << "Beneficio pos busca randomizado: " << fs[0] << " peso pos busca randomizado: " << fs[1] << endl;
}

void firstAscentMethodFlip(int m, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    s = construtorAleatorio(m, cap, s, d, b, ma);
    vector<int> fs = funcaoObjetivo(s, ma, d, b);
    cout << "Beneficio pos construcao: " << fs[0] << " peso pos construcao: " << fs[1] << endl;
    s = firstFlipImprovement(m, cap, s, b, d, ma);
    fs = funcaoObjetivo(s, ma, d, b);
    cout << "Beneficio pos busca first: " << fs[0] << " peso pos busca first: " << fs[1] << endl;
}

void bestAscentMethodFlip(int m, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    s = construtorAleatorio(m, cap, s, d, b, ma);
    vector<int> fs = funcaoObjetivo(s, ma, d, b);
    cout << "Beneficio pos construcao: " << fs[0] << " peso pos construcao: " << fs[1] << endl;
    s = bestFlipImprovement(m, cap, s, b, d, ma);
    fs = funcaoObjetivo(s, ma, d, b);
    cout << "Beneficio pos busca best: " << fs[0] << " peso pos busca best: " << fs[1] << endl;
}

int main(){
    int m, n, ne, cap;
    vector<int> d, b;
    vector<vector<int>> ma;
    leArquivo(d, b, ma, "prob-software.txt",&m, &n, &ne, &cap);
    vector<int> p(m, 0);
    //randomAscentMethodFlip(m, 10, cap, p, b, d, ma);
    //firstAscentMethodFlip(m, cap, p, b, d, ma);
    bestAscentMethodFlip(m, cap, p, b, d, ma);
    //randomAscentMethodSwap(m, 10, cap, p, b, d, ma);
    //firstAscentMethodSwap(m, cap, p, b, d, ma);
    //bestAscentMethodSwap(m, cap, p, b, d, ma);
    return 0;
}