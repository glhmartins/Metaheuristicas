#include "avaliaSolucao.cpp"

using namespace std;

void preencher(int &m, const vector<bool>& s, vector<int> &dt, vector<int> &f) {
    dt.clear();
    f.clear();
    for (int i = 0; i < m; i++) {
        if (s[i]) dt.push_back(i);
        else f.push_back(i);
    }
}

vector<bool> randomSwapStep(int &m, int &max, int &cap, const vector<bool> &s, vector<int> &b, vector<int> &d, vector<TP> &ma){
    vector<bool> s1 = s;
    vector<int> fs = funcaoObjetivo(s, ma, d, b), fn(2,0), dt, f;
    preencher(m, s, dt, f);
    int r1, r2, i = 0, in, out;
    do {
        r1 = rand()%(dt.size());
        r2 = rand()%(f.size());
        in = dt[r1];
        out = f[r2];
        swap(s1[in], s1[out]);
        fn[0] = fs[0]-b[in]+b[out];
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
        swap(s1[in], s1[out]);
        i++;
    } while (i<max);
    return s;
}

vector<bool> firstSwapStep(int &m, int &cap, const vector<bool> &s, vector<int> &b, vector<int> &d, vector<TP> &ma){
    vector<bool> s1 = s;
    vector<int> fs = funcaoObjetivo(s,  ma, d, b), fn(2,0), dt, f;
    preencher(m, s, dt, f);
    for(int in: dt){
        for(int out: f){
            swap(s1[in], s1[out]);
            fn[0] = fs[0]-b[in]+b[out];
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
            swap(s1[in], s1[out]);
        }
    }
    return s;
}

vector<bool> randomFlipStep(int &m, int &max, int &cap, const vector<bool> &s, vector<int> &b, vector<int> &d, vector<TP> &ma){
    vector<bool> s1 = s;
    vector<int> fs = funcaoObjetivo(s,  ma, d, b), fn(2,0);
    int r, i = 0;
    do {
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
            s1[r] = 0;
        }
        i++;
    } while (i<max);
    return s;
}

vector<bool> firstFlipStep(int &m, int &cap, const vector<bool> &s, vector<int> &b, vector<int> &d, vector<TP> &ma){
    vector<bool> s1 = s;
    vector<int> fs = funcaoObjetivo(s,  ma, d, b), fn(2,0);
    for(int i = 0; i<m; i++){
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
            s1[i] = 0;
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
