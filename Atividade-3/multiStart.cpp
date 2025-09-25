#include "construtores.cpp"
#include "buscaLocal.cpp"

void multiStartRandom(int m, int max, int parada, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    vector<int> fs(2,0), fn(2,0), sf = s, sn;
    for(int i = 0; i<parada; i++){
        sn = s;
        sn = construtorAleatorio(m, cap, sn, d, b, ma);
        sn = randomImprovementFlip(m, max, cap, sn, b, d, ma);
        fn = funcaoObjetivo(sn, ma, d, b);
        if(fn[0]>fs[0]){
            fs = fn;
            sf = sn;
        }
    }
    cout << endl << "Beneficio: " << fs[0] << endl;
}

void multiStartFirst(int m, int parada, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    vector<int> fs(2,0), fn(2,0), sf = s, sn;
    for(int i = 0; i<parada; i++){
        sn = s;
        sn = construtorAleatorio(m, cap, sn, d, b, ma);
        sn = firstImprovementFlip(m, cap, sn, b, d, ma);
        fn = funcaoObjetivo(sn, ma, d, b);
        if(fn[0]>fs[0]){
            fs = fn;
            sf = sn;
        }
    }
    cout << endl << "Beneficio: " << fs[0] << endl;
}

int main(){
    srand(time(NULL));
    int m, n, ne, cap;
    vector<int> d, b;
    vector<vector<int>> ma;
    leArquivo(d, b, ma, "prob-software.txt",&m, &n, &ne, &cap);
    vector<int> p(m, 0);
    multiStartRandom(m, 25, 10, cap, p, b, d, ma);
    multiStartFirst(m, 10, cap, p, b, d, ma);
    return 0;
}