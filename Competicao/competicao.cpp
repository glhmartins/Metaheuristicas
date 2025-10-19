#include "construtores.cpp"
#include "buscaLocal.cpp"

using namespace std;

int grasp(int &m, int max, int &cap, float alpha, vector<bool> &s, vector<int> &b, vector<int> &d, vector<TP> &ma){
    vector<int> fs(2,0), fn(2,0);
    fs[1] = (int) MAXFLOAT;
    vector<bool> sf = s, sn;
    for(int i = 0; i<max; i++){
        sn = s;
        sn = construtorGulosoAleatorio(m, cap, sn, alpha, d, b, ma);
        sn = rvns(m, 100, cap, sn, b, d, ma);
        fn = funcaoObjetivo(sn, ma, d, b);
        if(fn[0]>fs[0] && fn[1]<=cap){
            fs[0] = fn[0];
            fs[1] = fn[1];
            sf = sn;
        }
        //cout << endl << " beneficio[" << i << "]: " << fn[0] << endl;
    }
    cout << endl << "beneficio: " << fs[0] <<  " peso: " << fs[1] << endl;
    s = sf;
    cout << "[";
    for(int i = 0; i<m-1; i++) cout << ((s[i]==false)? "0, ":"1, " );
    cout << ((s[m-1]==false)? '0':'1') << ']' << endl;
    return fs[0];
}

vector<double> valoresFo(vector<int> sols){
    vector<double> p(3,0);
    p[2] = MAXFLOAT;
    for(int i = 0; i<sols.size(); i++){
        p[0] += sols[i];
        if(sols[i]>p[1]) p[1] = sols[i];
        if(sols[i]<p[2]) p[2] = sols[i];
    }
    p[0] = p[0]/sols.size();
    return p;
}

vector<double> tempos(vector<double> tempo){
    vector<double> t(3,0);
    t[2] = MAXFLOAT;
    for(int i = 0; i<tempo.size(); i++){
        t[0] += tempo[i];
        if(tempo[i]>t[1]) t[1] = tempo[i];
        if(tempo[i]<t[2]) t[2] = tempo[i];
    }
    t[0] = t[0]/tempo.size();
    return t;
}

double desvio(vector<int> sol, double media){
    double sum = 0;
    for(int i = 0; i<sol.size(); i++) sum += pow(sol[i]-media, 2);
    sum /= media;
    sum = sqrt(sum);
    return sum;
}

int main(){
    srand(time(NULL));
    int m, n, ne, cap;
    vector<int> d, b;
    vector<TP> ma;
    clock_t ti, tf;
    vector<int> sols;
    vector<double> sol, tempo;
    double t, dp;
    string a[] = {"i1.txt", "i2.txt", "i3.txt", "i4.txt", "i5.txt", "i6.txt", "i7.txt", "sukp02.txt", "sukp07.txt", "sukp28.txt"};
    for(int j = 0; j<1; j++){
        d.clear();
        b.clear();
        ma.clear();
        leArquivo(d, b, ma, a[7],m, n, ne, cap);
        sols.clear();
        sol.clear();
        tempo.clear();
        for(int i = 0; i<30; i++){
            vector<bool> p(m+1, false);
            ti = clock();
            sols.push_back(grasp(m, 100, cap, 0.8, p, b, d, ma));
            tf = clock();
            t = (double) (tf-ti)/CLOCKS_PER_SEC;
            cout << t << endl;
            tempo.push_back(t);
        }
        sol = valoresFo(sols);
        tempo = tempos(tempo);
        dp = desvio(sols, sol[0]);
        cout << endl << "menor tempo: " << tempo[2] << " maior tempo: " << tempo[1] << " tempo medio: " << tempo[0] << endl;
        cout << "menor fo: " << sol[2] << " maior fo: " << sol[1] << " fo media: " << sol[0] << endl;
        cout << "desvio padrao: " << dp << endl;
    }
    return 0;
}