#include "structures.cpp"

using namespace std;

/*void randomSwapPerturbacao(int &max, int &cap, const vector<bool> &s, vector<int> &dt, vector<int> &f, vector<int> &d, const vector<TP> &ma){
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

void perturbacao(int &m, int &max, int &cap, int nivel, const vector<bool> &s, vector<int> &d, const vector<TP> &ma){
    vector<int> dt, f;
    vector<bool> sp = s;
    preencher(m, sp, dt, f);
    for(int i = 0; i<nivel; i++) sp = randomSwapPerturbacao(max, cap, sp, dt, f, d, ma);
    return sp;
}*/

/*vector<TB> randomSwapStep(const vector<TI> &items, vector<TB> &bins, const int &n_items, const int &capacity, const int max){
    vector<TB> bf = bins;
    int r1, r2, i = 0;
    do {
        r1 = rand()%(bins.size());
        r2 = rand()%(bins.size());
        swap(s1[in], s1[out]);
        if(fn[0]>fs[0]){
            if(fn[1]<=cap){
                s1[m] = true;
                return s1;
            }
        }
        else if(fn[0]==fs[0]){
            if(fn[1]<fs[1]){
                s1[m] = true;
                return s1;
            }
        }
        swap(s1[in], s1[out]);
        i++;
    } while (i<max);
    return s;
}*/

/*void firstSwapStep(int &m, int &cap, const vector<bool> &s, vector<int> &dt, vector<int> &f, vector<int> &b, vector<int> &d, const vector<TP> &ma){
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
}*/

vector<TB> randomMoveStep(const vector<TI> &items, vector<TB> &bins, const int &n_items, const int &capacity, const int max){
    vector<TB> sb = bins;
    int ri, rs, rc, i = 0, item_id;
    bool moved = false;
    rs = rand()%bins.size();
    ri = rand()%(sb[rs].items.size());
    item_id = sb[rs].items[ri];
    while(!moved && i<max){
        i++;
        rc = rand()%bins.size();
        if(rc == rs) continue;
        if(items[item_id].weight+sb[rc].current_weight<=capacity && !verifyConflict(sb[rc], items[item_id])){
            sb[rc].items.push_back(item_id);
            sb[rs].items.erase(sb[rs].items.begin()+ri);
            moved = true;
        }
    }
    if(sb[rs].items.empty()) sb.erase(sb.begin()+rs);
    return sb;
}

/*void firstFlipStep(int &m, int &cap, const vector<bool> &s, vector<int> &dt, vector<int> &f, vector<int> &b, vector<int> &d, const vector<TP> &ma){
    vector<bool> s1 = s;
    int out;
    for(int j = 0; j<f.size(); j++){
        swap(f[j], f.back());
        f.pop_back();
        if(fn[0]>fs[0]){
            fn[1] = pesoDtF(ma, d, dt);
            if(fn[1]<=cap){
                s1[m] = true;
            }
        }

        swap(f[j], f.back());
        s1[out] = 0;
    }
}*/

void rvnd(const vector<TI> &items, vector<TB> &bins, const int &n_items, const int &capacity, const int max){
    vector<TB> sb = bins;
    int i = 0, r;
    while (i<max) { 
        i++;
        r = rand()%2;
        sb = /*(r==0) ?*/ randomMoveStep(items, bins, n_items, capacity, max); //: randomSwapStep(items, bins, n_items, capacity, max);
        if(sb.size()<bins.size()){
            bins = sb;
            i = 0;
        }
        /*if(i==max-1){
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
        }*/
    }
}
