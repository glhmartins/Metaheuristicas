#include "construtores.cpp"
#include "buscaLocal.cpp"

using namespace std;

void grasp(int &m, int max, int &cap, float alpha, vector<bool> &s, vector<int> &b, vector<int> &d, vector<TP> &ma){
    vector<int> fs(2,0), fn(2,0);
    vector<bool> sf = s, sn;
    for(int i = 0; i<max; i++){
        sn = s;
        sn = construtorGulosoAleatorio(m, cap, sn, alpha, d, b, ma);
        sn = rvns(m, 30, cap, sn, b, d, ma);
        fn[0] = beneficio(sn, b);
        if(fn[0]>fs[0]){
            fs[0] = fn[0];
            sf = sn;
        }
        cout << endl << " beneficio[" << i << "]: " << fn[0] << endl;
    }
    cout << endl << "beneficio: " << fs[0] << endl;
}

int main(){
    clock_t ti = clock();
    srand(time(NULL));
    int m, n, ne, cap;
    vector<int> d, b;
    vector<TP> ma;
    string a[] = {"i1.txt", "i2.txt", "i3.txt", "i4.txt", "i5.txt", "i6.txt", "i7.txt"};
    leArquivo(d, b, ma, a[6],m, n, ne, cap);
    vector<bool> p(m+1, false);
    grasp(m, 30, cap, 0.8, p, b, d, ma);
    clock_t tf = clock();
    double t = (double) (tf-ti)/CLOCKS_PER_SEC;
    cout << t << endl;
    return 0;
}