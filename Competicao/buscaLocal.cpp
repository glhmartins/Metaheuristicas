#include "avaliaSolucao.cpp"

using namespace std;

void preencher(int &m, const vector<bool> &s, vector<int> &dt, vector<int> &f) {
    dt.clear();
    f.clear();
    for (int i = 0; i < m; i++) {
        if (s[i]) dt.push_back(i);
        else f.push_back(i);
    }
}

vector<bool> randomSwapPerturbacao(int &max, int &cap, const vector<bool> &s, vector<int> &dt, vector<int> &f, vector<int> &d, const vector<TP> &ma){
    vector<bool> s1 = s;
    int r1, r2, i = 0, in, out, peso;
    do {
        r1 = rand()%(dt.size());
        r2 = rand()%(f.size());
        in = dt[r1];
        out = f[r2];
        swap(s1[in], s1[out]);
        dt[r1] = out;
        f[r2] = in;
        peso = pesoDtF(ma, d, dt);
        if(peso<=cap) return s1;
        swap(s1[in], s1[out]);
        dt[r1] = in;
        f[r2] = out;
        i++;
    } while (i<max);
    return s;
}

vector<bool> perturbacao(int &m, int &max, int &cap, int nivel, const vector<bool> &s, vector<int> &d, const vector<TP> &ma){
    vector<int> dt, f;
    vector<bool> sp = s;
    preencher(m, sp, dt, f);
    for(int i = 0; i<nivel; i++) sp = randomSwapPerturbacao(max, cap, sp, dt, f, d, ma);
    return sp;
}

vector<bool> randomSwapStep(int &m, int &max, int &cap, const vector<bool> &s, vector<int> &dt, vector<int> &f, vector<int> &b, vector<int> &d, const vector<TP> &ma){
    vector<bool> s1 = s;
    vector<int> fs = funcaoObjetivo(s, ma, d, b), fn(2,0);
    int r1, r2, i = 0, in, out;
    do {
        r1 = rand()%(dt.size());
        r2 = rand()%(f.size());
        in = dt[r1];
        out = f[r2];
        swap(s1[in], s1[out]);
        dt[r1] = out;
        f[r2] = in;
        fn[0] = fs[0]-b[in]+b[out];
        if(fn[0]>fs[0]){
            fn[1] = pesoDtF(ma, d, dt);
            if(fn[1]<=cap){
                s1[m] = true;
                return s1;
            }
        }
        else if(fn[0]==fs[0]){
            fn[1] = pesoDtF(ma, d, dt);
            if(fn[1]<fs[1]){
                s1[m] = true;
                return s1;
            }
        }
        swap(s1[in], s1[out]);
        dt[r1] = in;
        f[r2] = out;
        i++;
    } while (i<max);
    return s;
}

vector<bool> firstSwapStep(int &m, int &cap, const vector<bool> &s, vector<int> &dt, vector<int> &f, vector<int> &b, vector<int> &d, const vector<TP> &ma){
    vector<bool> s1 = s;
    vector<int> fs = funcaoObjetivo(s, ma, d, b), fn(2,0);
    int in, out;
    for(int i = 0; i<dt.size(); i++){
        in = dt[i];
        for(int j = 0; j<f.size(); j++){
            out = f[j];
            swap(s1[in], s1[out]);
            fn[0] = fs[0]-b[in]+b[out];
            dt[i] = out;
            f[j] = in;
            if(fn[0]>fs[0]){
                fn[1] = pesoDtF(ma, d, dt);
                if(fn[1]<=cap){
                    s1[m] = true;
                    return s1;
                }
            }
            else if(fn[0]==fs[0]){
                fn[1] = pesoDtF(ma, d, dt);
                if(fn[1]<fs[1]){
                    s1[m] = true;
                    return s1;
                }
            }
            swap(s1[in], s1[out]);
            dt[i] = in;
            f[j] = out;
        }
    }
    return s;
}

vector<bool> randomFlipStep(int &m, int &max, int &cap, const vector<bool> &s, vector<int> &dt, vector<int> &f, vector<int> &b, vector<int> &d, const vector<TP> &ma){
    vector<bool> s1 = s;
    vector<int> fs = funcaoObjetivo(s,  ma, d, b), fn(2,0);
    int r, i = 0, out;
    do {
        r = rand()%f.size();
        out = f[r];
        s1[out] = 1; 
        fn[0] = fs[0]+b[out];
        dt.push_back(out);
        swap(f[r], f.back());
        f.pop_back();
        if(fn[0]>fs[0]){
            fn[1] = pesoDtF(ma, d, dt);
            if(fn[1]<=cap){
                s1[m] = true;
                return s1;
            }
        }
        dt.pop_back();
        f.push_back(out);
        swap(f[r], f.back());
        s1[out] = 0;
        i++;
    } while (i<max);
    return s;
}

vector<bool> firstFlipStep(int &m, int &cap, const vector<bool> &s, vector<int> &dt, vector<int> &f, vector<int> &b, vector<int> &d, const vector<TP> &ma){
    vector<bool> s1 = s;
    vector<int> fs = funcaoObjetivo(s,  ma, d, b), fn(2,0);
    int out;
    for(int j = 0; j<f.size(); j++){
        out = f[j];
        s1[out] = 1; 
        fn[0] = fs[0]+b[out];
        dt.push_back(out);
        swap(f[j], f.back());
        f.pop_back();
        if(fn[0]>fs[0]){
            fn[1] = pesoDtF(ma, d, dt);
            if(fn[1]<=cap){
                s1[m] = true;
                return s1;
            }
        }
        dt.pop_back();
        f.push_back(out);
        swap(f[j], f.back());
        s1[out] = 0;
    }
    return s;
}

vector<bool> rvnd(int &m, int max, int &cap, vector<bool> &s, vector<int> &b, vector<int> &d, const vector<TP> &ma){
    vector<bool> sf;
    vector<int> dt, f;
    int i = 0, r;
    preencher(m, s, dt, f);
    while (i<max) { 
        i++;
        r = rand()%2;
        s[m] = false;
        sf = (r==0) ? randomFlipStep(m, max, cap, s, dt, f, b, d, ma) : randomSwapStep(m, max, cap, s, dt, f, b, d, ma);
        if(s[m]!=sf[m]){
            s = sf;
            i = 0;
        }
        if(i==max-1){
            sf = firstFlipStep(m, cap, s, dt, f, b, d, ma);
            if(sf[m]!=s[m]){
                s = sf;
                i = 0;
            }
            else{
                sf = firstSwapStep(m, cap, s, dt, f, b, d, ma);
                    if(sf[m]!=s[m]){
                    s = sf;
                    i = 0;
                }
            }
        }
    }
    return s;
}
