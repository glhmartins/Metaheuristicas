#include "avaliaSolucao.cpp"
#include <ctime>
#include <cmath>

using namespace std;

vector<int> randomSwapStep(int m, int max, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    vector<int> s1;
    vector<int> fs = funcaoObjetivo(s, ma, d, b), fn;
    int r1, r2, i = 0, aux;
    do {
        s1 = s;
        r1 = rand()%s.size();
        r2 = rand()%s.size();
        if (r1!=r2){
            aux = s1[r1];
            s1[r1] = s1[r2];
            s1[r2] = aux;
            fn = funcaoObjetivo(s1, ma, d, b);
            if((fn[0]>fs[0]) && (fn[1]<=cap)) return s1;
        }
        i++;
    } while (i<max);
    return s;
}

vector<int> firstSwapStep(int m, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    vector<int> s1;
    vector<int> fs = funcaoObjetivo(s, ma, d, b), fn;
    int aux;
    for(int i = 0; i<m-1; i++){
        for(int j = i+1; j<m; j++){
            s1 = s;
            aux = s1[i];
            s1[i] = s1[j];
            s1[j] = aux; 
            fn = funcaoObjetivo(s1, ma, d, b);
            if((fn[0]>fs[0]) && (fn[1]<=cap)) return s1;
        }
    }
    return s;
}

vector<int> bestSwapStep(int m, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    vector<int> s1;
    vector<int> fs = funcaoObjetivo(s, ma, d, b), fn;
    int aux;
    for(int i = 0; i<m-1; i++){
        for(int j = i+1; j<m; j++){
            s1 = s;
            aux = s1[i];
            s1[i] = s1[j];
            s1[j] = aux; 
            fn = funcaoObjetivo(s1, ma, d, b);
            if((fn[0]>fs[0]) && (fn[1]<=cap)) {
                fs = fn;
                s = s1;
            }
        }
    }
    return s;
}

vector<int> randomFlipStep(int m, int max, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    vector<int> s1 = s;
    vector<int> fs = funcaoObjetivo(s, ma, d, b), fn;
    int r, i = 0;
    do {
        s1 = s;
        r = rand()%s.size();
        s1[r] = (s1[r] == 1) ? 0:1; 
        fn = funcaoObjetivo(s1, ma, d, b);
        if((fn[0]>fs[0]) && (fn[1]<=cap)) return s1;
        i++;
    } while (i<max);
    return s;
}

vector<int> firstFlipStep(int m, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    vector<int> s1;
    vector<int> fs = funcaoObjetivo(s, ma, d, b), fn;
    for(int i = 0; i<m; i++){
        s1 = s;
        s1[i] = (s1[i] == 1) ? 0:1; 
        fn = funcaoObjetivo(s1, ma, d, b);
        if((fn[0]>fs[0]) && (fn[1]<=cap)) return s1;
    }
    return s;
}

vector<int> bestFlipStep(int m, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    vector<int> s1;
    vector<int> fs = funcaoObjetivo(s, ma, d, b), fn;
    for(int i = 0; i<m; i++){
        s1 = s;
        s1[i] = (s1[i] == 1) ? 0:1; 
        fn = funcaoObjetivo(s1, ma, d, b);
        if((fn[0]>fs[0]) && (fn[1]<=cap)) {
            fs = fn;
            s = s1;
        }
    }
    return s;
}

vector<int> randomImprovement(int m, int max, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    srand(time(NULL));
    vector<int> s1 = s, s2 = s, sf;
    vector<int> fs = funcaoObjetivo(s, ma, d, b), fn;
    int i = 0, r;
    do {
        r = rand()%2;
        s1 = randomSwapStep(m, max, cap, s, b, d, ma);
        s2 = randomFlipStep(m, max, cap, s, b, d, ma);
        sf = (r == 0) ? s1:s2;
        if(s!=sf){
            s = sf;
            i = 0;
        }
        i++;
    } while(i<=max);
    return s;
}

vector<int> firstImprovement(int m, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    vector<int> s1 = s, s2 = s, sf;
    vector<int> fs = funcaoObjetivo(s, ma, d, b), fn;
    int i = 0;
    do {
        s1 = firstSwapStep(m, cap, s, b, d, ma);
        s2 = firstFlipStep(m, cap, s, b, d, ma);
        sf = (funcaoObjetivo(s1, ma, d, b)>funcaoObjetivo(s2, ma, d, b)) ? s1:s2;
        if(s!=sf){
            s = sf;
            i = 0;
        }
        else break;
        i++;
    } while(i<=m);
    return s;
}

vector<int> bestImprovement(int m, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    vector<int> s1 = s, s2 = s, sf;
    vector<int> fs = funcaoObjetivo(s, ma, d, b), fn;
    int i = 0;
    do {
        s1 = bestSwapStep(m, cap, s, b, d, ma);
        s2 = bestFlipStep(m, cap, s, b, d, ma);
        sf = (funcaoObjetivo(s1, ma, d, b)>funcaoObjetivo(s2, ma, d, b)) ? s1:s2;
        if(sf!=s){
            s = sf;
            i = 0;
        }
        else break;
        i++;
    } while(i<=m);
    return s;
}
