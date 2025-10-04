#include "avaliaSolucao.cpp"
#include <ctime>
#include <cmath>

using namespace std;

vector<bool> randomSwapStep(int &m, int &max, int &cap, vector<bool> s, vector<int> &b, vector<int> &d, vector<vector<int>> &ma){
    vector<bool> s1 = s;
    vector<int> fs = funcaoObjetivo(s, ma, d, b), fn;
    int r1, r2, i = 0, aux;
    do {
        s1 = s;
        r1 = rand()%m;
        r2 = rand()%m;
        if ((r1!=r2) && (s1[r1]!=s1[r2])){
            aux = s1[r1];
            s1[r1] = s1[r2];
            s1[r2] = aux;
            fn = funcaoObjetivo(s1, ma, d, b);
            if((fn[0]>fs[0]) && (fn[1]<=cap)) {
                s1[m] = true;
                return s1;
            }
        }
        i++;
    } while (i<max);
    return s;
}

vector<bool> firstSwapStep(int &m, int &cap, vector<bool> s, vector<int> &b, vector<int> &d, vector<vector<int>> &ma){
    vector<bool> s1;
    vector<int> fs = funcaoObjetivo(s, ma, d, b), fn;
    int aux;
    for(int i = 0; i<m-1; i++){
        for(int j = i+1; j<m; j++){
            s1 = s;
            if(s1[i]!=s1[j]){
                aux = s1[i];
                s1[i] = s1[j];
                s1[j] = aux; 
                fn = funcaoObjetivo(s1, ma, d, b);
                if((fn[0]>fs[0]) && (fn[1]<=cap)) {
                    s1[m] = true;
                    return s1;
                }
            }
        }
    }
    return s;
}

vector<bool> bestSwapStep(int &m, int &cap, vector<bool> s, vector<int> &b, vector<int> &d, vector<vector<int>> &ma){
    vector<bool> s1, sf = s;
    vector<int> fs = funcaoObjetivo(sf, ma, d, b), fn;
    int aux;
    for(int i = 0; i<m-1; i++){
        for(int j = i+1; j<m; j++){
            s1 = s;
            if(s1[i]!=s1[j]){
                aux = s1[i];
                s1[i] = s1[j];
                s1[j] = aux; 
                fn = funcaoObjetivo(s1, ma, d, b);
                if((fn[0]>fs[0]) && (fn[1]<=cap)) {
                    fs = fn;
                    sf = s1;
                    sf[m] = true;
                }
            }
        }
    }
    return sf;
}

vector<bool> randomFlipStep(int &m, int &max, int &cap, vector<bool> s, vector<int> &b, vector<int> &d, vector<vector<int>> &ma){
    vector<bool> s1 = s;
    vector<int> fs = funcaoObjetivo(s, ma, d, b), fn;
    int r, i = 0;
    do {
        s1 = s;
        r = rand()%m;
        if(s1[r]==0){
            s1[r] = 1; 
            fn = funcaoObjetivo(s1, ma, d, b);
            if((fn[0]>fs[0]) && (fn[1]<=cap)) {
                s1[m] = true;
                return s1;
            }
        }
        i++;
    } while (i<max);
    return s;
}

vector<bool> firstFlipStep(int &m, int &cap, vector<bool> s, vector<int> &b, vector<int> &d, vector<vector<int>> &ma){
    vector<bool> s1;
    vector<int> fs = funcaoObjetivo(s, ma, d, b), fn;
    for(int i = 0; i<m; i++){
        s1 = s;
        if(s1[i]==0){
            s1[i] = 1; 
            fn = funcaoObjetivo(s1, ma, d, b);
            if((fn[0]>fs[0]) && (fn[1]<=cap)) {
                s1[m] = true;
                return s1;
            }
        }
    }
    return s;
}

vector<bool> bestFlipStep(int &m, int &cap, vector<bool> s, vector<int> &b, vector<int> &d, vector<vector<int>> &ma){
    vector<bool> s1, sf = s;
    vector<int> fs = funcaoObjetivo(sf, ma, d, b), fn;
    for(int i = 0; i<m; i++){
        s1 = s;
        if(s1[i]==0){
            s1[i] = (s1[i] == 1) ? 0:1; 
            fn = funcaoObjetivo(s1, ma, d, b);
            if((fn[0]>fs[0]) && (fn[1]<=cap)) {
                fs = fn;
                sf = s1;
                sf[m] = true;
            }
        }
    }
    return sf;
}

vector<bool> randomImprovementFlip(int &m, int &max, int &cap, vector<bool> s, vector<int> &b, vector<int> &d, vector<vector<int>> &ma){
    //srand(time(NULL));
    vector<bool> sf;
    vector<int> fs = funcaoObjetivo(s, ma, d, b), fn;
    int i = 0, r;
    do {
        i++;
        s[m] = false;
        sf = randomFlipStep(m, max, cap, s, b, d, ma);
        if(s[m]!=sf[m]){
            s = sf;
            i = 0;
        }
    } while(i<=max);
    return s;
}

vector<bool> randomImprovementSwap(int &m, int &max, int &cap, vector<bool> s, vector<int> &b, vector<int> &d, vector<vector<int>> &ma){
    //srand(time(NULL));
    vector<bool> sf;
    vector<int> fs = funcaoObjetivo(s, ma, d, b), fn;
    int i = 0, r;
    do {
        i++;
        s[m] = false;
        sf = randomSwapStep(m, max, cap, s, b, d, ma);
        if(s[m]!=sf[m]){
            s = sf;
            i = 0;
        }
    } while(i<=max);
    return s;
}

vector<bool> firstImprovementFlip(int &m, int &cap, vector<bool> s, vector<int> &b, vector<int> &d, vector<vector<int>> &ma){
    vector<bool> sf = s;
    vector<int> fs = funcaoObjetivo(s, ma, d, b), fn;
    int i = 0;
    do {
        i++;
        s[m] = false;
        sf = firstFlipStep(m, cap, s, b, d, ma);
        if(s[m]!=sf[m]){
            s = sf;
            i = 0;
        }
        else break;
    } while(i<=m);
    return s;
}

vector<bool> firstImprovementSwap(int &m, int &cap, vector<bool> s, vector<int> &b, vector<int> &d, vector<vector<int>> &ma){
    vector<bool> sf = s;
    vector<int> fs = funcaoObjetivo(s, ma, d, b), fn;
    int i = 0;
    do {
        i++;
        s[m] = false;
        sf = firstSwapStep(m, cap, s, b, d, ma);
        if(s[m]!=sf[m]){
            s = sf;
            i = 0;
        }
        else break;
    } while(i<=m);
    return s;
}

vector<bool> bestImprovementFlip(int &m, int &cap, vector<bool> s, vector<int> &b, vector<int> &d, vector<vector<int>> &ma){
    vector<bool> sf;
    vector<int> fs = funcaoObjetivo(s, ma, d, b), fn;
    int i = 0;
    do {
        i++;
        s[m] = false;
        sf = bestFlipStep(m, cap, s, b, d, ma);
        if(s[m]!=sf[m]){
            s = sf;
            i = 0;
        }
        else break;
    } while(i<=m);
    return s;
}

vector<bool> bestImprovementSwap(int &m, int &cap, vector<bool> s, vector<int> &b, vector<int> &d, vector<vector<int>> &ma){
    vector<bool> sf;
    vector<int> fs = funcaoObjetivo(s, ma, d, b), fn;
    int i = 0;
    do {
        i++;
        s[m] = false;
        sf = bestSwapStep(m, cap, s, b, d, ma);
        if(s[m]!=sf[m]){
            s = sf;
            i = 0;
        }
        else break;
    } while(i<=m);
    return s;
}
