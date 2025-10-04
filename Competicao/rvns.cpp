#include "construtores.cpp"
#include "buscaLocal.cpp"

void rvns(int &m, int max, int &cap, float alpha, vector<bool> s, vector<int> &b, vector<int> &d, vector<vector<int>> &ma){
    s = construtorGuloso(m, cap, s, d, b, ma);
    vector<int> fs = funcaoObjetivo(s, ma, d, b), fn;
    vector<bool> sf;
    cout << "Beneficio pos construcao: " << fs[0] << " peso pos construcao: " << fs[1] << endl;
    int i = 0, r;
    while (i<=max) {
        i++;
        r = rand()%2;
        s[m] = false;
        sf = (r==0) ? randomFlipStep(m, max, cap, s, b, d, ma) : randomSwapStep(m, max, cap, s, b, d, ma);
        if(s[m]!=sf[m]){
            s = sf;
            i = 0;
        }
    }
    fs = funcaoObjetivo(s, ma, d, b);
    cout << "Beneficio pos busca randomizado: " << fs[0] << " peso pos busca randomizado: " << fs[1] << endl;
}

int main(){
    clock_t ti = clock();
    srand(time(NULL));
    int m, n, ne, cap;
    vector<int> d, b;
    vector<vector<int>> ma;
    leArquivo(d, b, ma, "i6.txt",m, n, ne, cap);
    vector<bool> p(m+1, false);
    rvns(m, 25, cap, 0.75, p, b, d, ma);
    clock_t tf = clock();
    double t = (double) (tf-ti)/CLOCKS_PER_SEC;
    cout << t << endl;
    return 0;
}