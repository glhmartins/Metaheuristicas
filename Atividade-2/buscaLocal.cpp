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
    vector<int> s1, sf = s;
    vector<int> fs = funcaoObjetivo(sf, ma, d, b), fn;
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
                sf = s1;
            }
        }
    }
    return sf;
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
    vector<int> s1, sf = s;
    vector<int> fs = funcaoObjetivo(sf, ma, d, b), fn;
    for(int i = 0; i<m; i++){
        s1 = s;
        s1[i] = (s1[i] == 1) ? 0:1; 
        fn = funcaoObjetivo(s1, ma, d, b);
        if((fn[0]>fs[0]) && (fn[1]<=cap)) {
            fs = fn;
            sf = s1;
        }
    }
    return sf;
}

vector<int> randomImprovementFlip(int m, int max, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    //srand(time(NULL));
    vector<int> sf;
    vector<int> fs = funcaoObjetivo(s, ma, d, b), fn;
    int i = 0, r;
    do {
        sf = randomFlipStep(m, max, cap, s, b, d, ma);
        if(s!=sf){
            s = sf;
            i = 0;
        }
        else i++;
    } while(i<=max);
    return s;
}

vector<int> randomImprovementSwap(int m, int max, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    //srand(time(NULL));
    vector<int> sf;
    vector<int> fs = funcaoObjetivo(s, ma, d, b), fn;
    int i = 0, r;
    do {
        sf = randomSwapStep(m, max, cap, s, b, d, ma);
        if(s!=sf){
            s = sf;
            i = 0;
        }
        else i++;
    } while(i<=max);
    return s;
}

vector<int> firstImprovementFlip(int m, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    vector<int> sf = s;
    vector<int> fs = funcaoObjetivo(s, ma, d, b), fn;
    int i = 0;
    do {
        sf = firstFlipStep(m, cap, s, b, d, ma);
        if(s!=sf){
            s = sf;
            i = 0;
        }
        else break;
        i++;
    } while(i<=m);
    return s;
}

vector<int> firstImprovementSwap(int m, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    vector<int> sf = s;
    vector<int> fs = funcaoObjetivo(s, ma, d, b), fn;
    int i = 0;
    do {
        sf = firstSwapStep(m, cap, s, b, d, ma);
        if(s!=sf){
            s = sf;
            i = 0;
        }
        else break;
        i++;
    } while(i<=m);
    return s;
}

vector<int> bestImprovementFlip(int m, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    vector<int> sf;
    vector<int> fs = funcaoObjetivo(s, ma, d, b), fn;
    int i = 0;
    do {
        sf = bestFlipStep(m, cap, s, b, d, ma);
        if(sf!=s){
            s = sf;
            i = 0;
        }
        else break;
        i++;
    } while(i<=m);
    return s;
}

vector<int> bestImprovementSwap(int m, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    vector<int> sf;
    vector<int> fs = funcaoObjetivo(s, ma, d, b), fn;
    int i = 0;
    do {
        sf = bestSwapStep(m, cap, s, b, d, ma);
        if(sf!=s){
            s = sf;
            i = 0;
        }
        else break;
        i++;
    } while(i<=m);
    return s;
}
