#include "construtores.cpp"
#include "buscaLocal.cpp"
#include <unistd.h>

int randomFlipAscentMethod(int m, int max, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    s = construtorAleatorio(m, cap, s, d, b, ma);
    vector<int> fs = funcaoObjetivo(s, ma, d, b);
    cout << endl << "Random" << endl;
    cout << "Beneficio pos construcao: " << fs[0] << endl;
    s = randomImprovementFlip(m, max, cap, s, b, d, ma);
    fs = funcaoObjetivo(s, ma, d, b);
    cout << "Beneficio pos busca randomizado: " << fs[0] << endl;
    return fs[0];
}

int randomSwapAscentMethod(int m, int max, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    s = construtorAleatorio(m, cap, s, d, b, ma);
    vector<int> fs = funcaoObjetivo(s, ma, d, b);
    cout << endl << "Random" << endl;
    cout << "Beneficio pos construcao: " << fs[0] << endl;
    s = randomImprovementSwap(m, max, cap, s, b, d, ma);
    fs = funcaoObjetivo(s, ma, d, b);
    cout << "Beneficio pos busca randomizado: " << fs[0] << endl;
    return fs[0];
}

int firstFlipAscentMethod(int m, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    s = construtorAleatorio(m, cap, s, d, b, ma);
    vector<int> fs = funcaoObjetivo(s, ma, d, b);
    cout << endl << "First" << endl;
    cout << "Beneficio pos construcao: " << fs[0] << endl;
    s = firstImprovementFlip(m, cap, s, b, d, ma);
    fs = funcaoObjetivo(s, ma, d, b);
    cout << "Beneficio pos busca first: " << fs[0] << endl;
    return fs[0];
}

int firstSwapAscentMethod(int m, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    s = construtorAleatorio(m, cap, s, d, b, ma);
    vector<int> fs = funcaoObjetivo(s, ma, d, b);
    cout << endl << "First" << endl;
    cout << "Beneficio pos construcao: " << fs[0] << endl;
    s = firstImprovementSwap(m, cap, s, b, d, ma);
    fs = funcaoObjetivo(s, ma, d, b);
    cout << "Beneficio pos busca first: " << fs[0] << endl;
    return fs[0];
}

int bestFlipAscentMethod(int m, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    s = construtorAleatorio(m, cap, s, d, b, ma);
    vector<int> fs = funcaoObjetivo(s, ma, d, b);
    cout << endl << "Best" << endl;
    cout << "Beneficio pos construcao: " << fs[0] << endl;
    s = bestImprovementFlip(m, cap, s, b, d, ma);
    fs = funcaoObjetivo(s, ma, d, b);
    cout << "Beneficio pos busca best: " << fs[0] << endl;
    return fs[0];
}

int bestSwapAscentMethod(int m, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    s = construtorAleatorio(m, cap, s, d, b, ma);
    vector<int> fs = funcaoObjetivo(s, ma, d, b);
    cout << endl << "Best" << endl;
    cout << "Beneficio pos construcao: " << fs[0] << endl;
    s = bestImprovementSwap(m, cap, s, b, d, ma);
    fs = funcaoObjetivo(s, ma, d, b);
    cout << "Beneficio pos busca best: " << fs[0] << endl;
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
    vector<vector<int>> ma;
    leArquivo(d, b, ma, "prob-software.txt",&m, &n, &ne, &cap);
    vector<int> p(m, 0);
    clock_t ti, tf;
    vector<int> sols;
    vector<double> sol, tempo;
    double t, dp;
    //randomFlipAscentMethod(m, 25, cap, p, b, d, ma);
    //randomSwapAscentMethod(m, 25, cap, p, b, d, ma);
    //firstFlipAscentMethod(m, cap, p, b, d, ma);
    //firstSwapAscentMethod(m, cap, p, b, d, ma);
    //bestFlipAscentMethod(m, cap, p, b, d, ma);
    for(int i = 0; i<30; i++){
        ti = clock();
        sols.push_back(bestSwapAscentMethod(m, cap, p, b, d, ma));
        tf = clock();
        t = (double) (tf-ti)/CLOCKS_PER_SEC;
        cout << "tempo de execução: " << t << endl;
        tempo.push_back(t);
        sleep(1);
    }
    sol = valoresFo(sols);
    tempo = tempos(tempo);
    dp = desvio(sols, sol[0]);
    cout << endl << "menor tempo: " << tempo[2] << " maior tempo: " << tempo[1] << " tempo medio: " << tempo[0] << endl;
    cout << "menor fo: " << sol[2] << " maior fo: " << sol[1] << " fo media: " << sol[0] << endl;
    cout << "desvio padrao: " << dp << endl;
    return 0;
}