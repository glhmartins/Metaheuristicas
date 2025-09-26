#include "construtores.cpp"
#include "buscaLocal.cpp"

void rvns(int m, int max, int cap, float alpha, vector<bool> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    s = construtorGulosoAleatorio(m, cap, s, alpha, d, b, ma);
    vector<int> fs = funcaoObjetivo(s, ma, d, b), fn;
    vector<bool> sf;
    cout << "Beneficio pos construcao: " << fs[0] << " peso pos construcao: " << fs[1] << endl;
    int i = 0, r;
    do {
        r = rand()%2;
        sf = (r==0) ? randomFlipStep(m, max, cap, s, b, d, ma) : randomSwapStep(m, max, cap, s, b, d, ma);
        if(s!=sf){
            s = sf;
            i = 0;
        }
        else i++;
    } while(i<=max);
    fs = funcaoObjetivo(s, ma, d, b);
    cout << "Beneficio pos busca randomizado: " << fs[0] << " peso pos busca randomizado: " << fs[1] << endl;
}

int main(){
    srand(time(NULL));
    int m, n, ne, cap;
    vector<int> d, b;
    vector<vector<int>> ma;
    leArquivo(d, b, ma, "prob-software.txt",&m, &n, &ne, &cap);
    vector<bool> p(m, false);
    rvns(m, 25, cap, 0.5, p, b, d, ma);
    return 0;
}