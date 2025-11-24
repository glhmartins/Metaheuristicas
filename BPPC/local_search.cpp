#include "structures.cpp"

using namespace std;

bool verifySwap(const vector<TI> &items, const TB &bin1_orig, const TB &bin2_orig, int item1_id, int item2_id, const int &capacity){
    TB bin1 = bin1_orig, bin2 = bin2_orig;
    if (bin1.current_weight - items[item1_id].weight + items[item2_id].weight > capacity) return false;
    if (bin2.current_weight - items[item2_id].weight + items[item1_id].weight > capacity) return false;
    auto it1 = find(bin1.items.begin(), bin1.items.end(), item1_id);
    if (it1 == bin1.items.end()) return false; 
    bin1.items.erase(it1);
    if (verifyConflict(bin1, items[item2_id])) return false;
    auto it2 = find(bin2.items.begin(), bin2.items.end(), item2_id);
    if (it2 == bin2.items.end()) return false; 
    bin2.items.erase(it2);
    if (verifyConflict(bin2, items[item1_id])) return false;
    return true;
}

void swapItems(const vector<TI> &items, TB &bin1, TB &bin2, int item1, int item2){
    auto it1 = find(bin1.items.begin(), bin1.items.end(), item1);
    auto it2 = find(bin2.items.begin(), bin2.items.end(), item2);
    if (it1 == bin1.items.end() || it2 == bin2.items.end()) return; 
    bin1.current_weight = bin1.current_weight - items[item1].weight + items[item2].weight;
    bin2.current_weight = bin2.current_weight - items[item2].weight + items[item1].weight;
    *it1 = item2;
    *it2 = item1;
}

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

bool randomSwapStep(const vector<TI> &items, vector<TB> &bins, const int &n_items, const int &capacity, const int max){
    int ri1, ri2, rs, rc, i = 0, item_id1, item_id2, min_weight = __INT_MAX__;
    for(int j = 0; j<bins.size(); j++){
        if(bins[j].current_weight<min_weight) {
            min_weight = bins[j].current_weight;
            rs = j;
        } 
    }
    ri1 = rand()%(bins[rs].items.size());
    item_id1 = bins[rs].items[ri1];
    while(i<max){
        rc = rand()%bins.size();
        if(rc == rs) continue;
        ri2 = rand()%(bins[rc].items.size());
        item_id2 = bins[rc].items[ri2];
        if(verifySwap(items, bins[rs], bins[rc], item_id1, item_id2, capacity)){
            swapItems(items, bins[rs], bins[rc], item_id1, item_id2);
            return true;
        }
        i++;
    }
    return false;
}

bool firstSwapStep(const vector<TI> &items, vector<TB> &bins, const int &n_items, const int &capacity, const int max){
    int rs, min_weight = __INT_MAX__;
    for(int j = 0; j<bins.size(); j++){
        if(bins[j].current_weight<min_weight) {
            min_weight = bins[j].current_weight;
            rs = j;
        } 
    }
    for(int i = 0; i < bins.size(); i++){
        if(i == rs) continue;
            for(int ri1 = 0; ri1 < bins[rs].items.size(); ri1++){
            int item_id1 = bins[rs].items[ri1]; 
            for(int ri2 = 0; ri2 < bins[i].items.size(); ri2++){
                int item_id2 = bins[i].items[ri2];
                if(verifySwap(items, bins[rs], bins[i], item_id1, item_id2, capacity)){
                    swapItems(items, bins[rs], bins[i], item_id1, item_id2);
                    return true;
                }
            }
        }
    }
    return false;
}

bool randomMoveStep(const vector<TI> &items, vector<TB> &bins, const int &n_items, const int &capacity, const int max){
    int ri, rs, rc, i = 0, item_id, min_weight = __INT_MAX__;
    for(int j = 0; j<bins.size(); j++){
        if(bins[j].current_weight<min_weight) {
            min_weight = bins[j].current_weight;
            rs = j;
        } 
    }
    ri = rand()%(bins[rs].items.size());
    item_id = bins[rs].items[ri];
    while(i<max){
        rc = rand()%bins.size();
        if(rc == rs) continue;
        if(items[item_id].weight+bins[rc].current_weight<=capacity && !verifyConflict(bins[rc], items[item_id])){
            bins[rc].items.push_back(item_id);
            bins[rc].current_weight += items[item_id].weight;
            bins[rs].items.erase(bins[rs].items.begin()+ri);
            bins[rs].current_weight -= items[item_id].weight;
            if(bins[rs].current_weight==0) bins.erase(bins.begin()+rs);
            return true;
        }
        i++;
    }
    return false;
}

bool firstMoveStep(const vector<TI> &items, vector<TB> &bins, const int &n_items, const int &capacity, const int max){
    int ri, rs, i = 0, min_weight = __INT_MAX__;
    for(int j = 0; j<bins.size(); j++){
        if(bins[j].current_weight<min_weight) {
            min_weight = bins[j].current_weight;
            rs = j;
        } 
    }
    for(i = 0; i<bins.size(); i++){
        if(i == rs) continue;
        ri = 0;
        for(int item_id: bins[rs].items){
            if(items[item_id].weight+bins[i].current_weight<=capacity && !verifyConflict(bins[i], items[item_id])){
                bins[i].items.push_back(item_id);
                bins[i].current_weight += items[item_id].weight;
                bins[rs].items.erase(bins[rs].items.begin()+ri);
                bins[rs].current_weight -= items[item_id].weight;
                if(bins[rs].current_weight==0) bins.erase(bins.begin()+rs);
                return true;
            }
            ri++;
        }
    }   
    return false;
}

void rvnd(const vector<TI> &items, vector<TB> &bins, const int &n_items, const int &capacity, const int max){
    vector<TB> sb = bins;
    bool improved = false;
    int i = 0, r;
    while (i<max) { 
        i++;
        r = rand()%2;
        improved = (r==0) ? randomMoveStep(items, sb, n_items, capacity, max):randomSwapStep(items, bins, n_items, capacity, max);
        if(improved){
            bins = sb;
            i = 0;
        }
        if(i==max-1){
            improved = firstMoveStep(items, sb, n_items, capacity, max);
            if(improved){
                bins = sb;
                i = 0;
            }
            /*else {
                improved = firstSwapStep(items, sb, n_items, capacity, max);
                if(improved){
                    bins = sb;
                    i = 0;
                }
            }*/
        }
        improved = false;
    }
}
