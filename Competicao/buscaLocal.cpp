#include "avaliaSolucao.cpp"

using namespace std;

vector<bool> pertubacao(int &m, int nivel, int &cap, vector<bool> s, vector<int> &b, vector<int> &d, vector<TP> &ma){
    vector<bool> s1 = s;
    double a = m*0.05*nivel;
    return s1;
}

vector<bool> randomSwapStep(int &m, int &max, int &cap, const vector<bool> &s, vector<int> &b, vector<int> &d, vector<TP> &ma){
    vector<bool> s1;
    vector<int> fs = funcaoObjetivo(s, ma, d, b), fn(2,0);
    int r1, r2, i = 0;
    do {
        s1 = s;
        r1 = rand()%m;
        r2 = rand()%m;
        if (s1[r1]!=s1[r2]){
            swap(s1[r1], s1[r2]);
            fn[0] = fs[0]-(b[r1]*s[r1])-(b[r2]*s[r2])+(b[r1]*s1[r1])+(b[r2]*s1[r2]);
            if(fn[0]>fs[0]){
                fn[1] = peso(s1, ma, d);
                if(fn[1]<=cap){
                    s1[m] = true;
                    return s1;
                }
            }
            else if(fn[0]==fs[0]){
                fn[1] = peso(s1, ma, d);
                if(fn[1]<fs[1]){
                    s1[m] = true;
                    return s1;
                }
            }
        }
        i++;
    } while (i<max);
    return s;
}

vector<bool> firstSwapStep(int &m, int &cap, const vector<bool> &s, vector<int> &b, vector<int> &d, vector<TP> &ma){
    vector<bool> s1;
    vector<int> fs = funcaoObjetivo(s, ma, d, b), fn(2,0);
    for(int i = 0; i<m-1; i++){
        for(int j = i+1; j<m; j++){
            s1 = s;
            if(s1[i]!=s1[j]){
                swap(s1[i], s1[j]);
                fn[0] = fs[0]-(b[i]*s[i])-(b[j]*s[j])+(b[i]*s1[i])+(b[j]*s1[j]);
                if(fn[0]>fs[0]){
                    fn[1] = peso(s1, ma, d);
                    if(fn[1]<=cap){
                        s1[m] = true;
                        return s1;
                    }
                }
                else if(fn[0]==fs[0]){
                    fn[1] = peso(s1, ma, d);
                    if(fn[1]<fs[1]){
                        s1[m] = true;
                        return s1;
                    }
                }
            }
        }
    }
    return s;
}

vector<bool> randomFlipStep(int &m, int &max, int &cap, const vector<bool> &s, vector<int> &b, vector<int> &d, vector<TP> &ma){
    vector<bool> s1 = s;
    vector<int> fs = funcaoObjetivo(s, ma, d, b), fn(2,0);
    int r, i = 0;
    do {
        s1 = s;
        r = rand()%m;
        if(s1[r]==0){
            s1[r] = 1; 
            fn[0] = fs[0]-(b[r]*s[r])+(b[r]*s1[r]);
            if(fn[0]>fs[0]){
                fn[1] = peso(s1, ma, d);
                if(fn[1]<=cap){
                    s1[m] = true;
                    return s1;
                }
            }
        }
        i++;
    } while (i<max);
    return s;
}

vector<bool> firstFlipStep(int &m, int &cap, const vector<bool> &s, vector<int> &b, vector<int> &d, vector<TP> &ma){
    vector<bool> s1;
    vector<int> fs = funcaoObjetivo(s, ma, d, b), fn(2,0);
    for(int i = 0; i<m; i++){
        s1 = s;
        if(s1[i]==0){
            s1[i] = 1; 
            fn[0] = fs[0]-(b[i]*s[i])+(b[i]*s1[i]);
            if(fn[0]>fs[0]){
                fn[1] = peso(s1, ma, d);
                if(fn[1]<=cap){
                    s1[m] = true;
                    return s1;
                }
            }
        }
    }
    return s;
}

vector<bool> rvns(int &m, int max, int &cap, vector<bool> &s, vector<int> &b, vector<int> &d, vector<TP> &ma){
    vector<bool> sf;
    int i = 0, r;
    while (i<max) {
        i++;
        r = rand()%2;
        s[m] = false;
        sf = (r==0) ? randomFlipStep(m, max, cap, s, b, d, ma) : randomSwapStep(m, max, cap, s, b, d, ma);
        if(s[m]!=sf[m]){
            s = sf;
            i = 0;
        }
        if(i==max-1){
            sf = firstFlipStep(m, cap, s, b, d, ma);
            if(sf[m]!=s[m]){
                s = sf;
                i = 0;
            }
            else{
                sf = firstSwapStep(m, cap, s, b, d, ma);
                    if(sf[m]!=s[m]){
                    s = sf;
                    i = 0;
                }
            }
        }
    }
    return s;
}
