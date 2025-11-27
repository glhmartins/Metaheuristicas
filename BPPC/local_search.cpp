#include "structures.cpp"

using namespace std;

bool verifySwap(const vector<TI> &items, const TB &bin1_orig, const TB &bin2_orig, int item1_id, int item2_id, const int &capacity){
    TB bin1 = bin1_orig, bin2 = bin2_orig;
    if (bin1.current_weight - items[item1_id].weight + items[item2_id].weight > capacity) return false;
    if (bin2.current_weight - items[item2_id].weight + items[item1_id].weight > capacity) return false;
    auto it1 = find(bin1.items.begin(), bin1.items.end(), item1_id);
    if (it1 == bin1.items.end()) return false; 
    bin1.items.erase(it1); // Remove item 1
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

void cleanEmptyBins(vector<TB> &bins) {
    bins.erase(std::remove_if(bins.begin(), bins.end(), [](const TB &b){ return b.items.empty(); }),bins.end());
}

void perturbacao(const vector<TI> &items, vector<TB> &bins, const int &capacity, const int n_items, int level) {
    cleanEmptyBins(bins);
    if (bins.empty()) return;
    int num_items_to_remove = max(1, (int) ceil(n_items * (level / 100.0))), ri, item_id, rs = 0, min_weight = __INT_MAX__;
    vector<int> removed_items;
    for (int k = 0; k < num_items_to_remove; ++k) {
        if (bins.empty()) break; 
        rs = 0;
        min_weight = __INT_MAX__;
        for (int j = 0; j < (int)bins.size(); ++j) {
            if (bins[j].current_weight < min_weight) {
                min_weight = bins[j].current_weight;
                rs = j;
            }
        }
        if (bins[rs].items.empty()) {
            cleanEmptyBins(bins);
            continue;
        }
        ri = rand() % bins[rs].items.size();
        item_id = bins[rs].items[ri];
        removed_items.push_back(item_id);
        bins[rs].items.erase(bins[rs].items.begin() + ri);
        bins[rs].current_weight -= items[item_id].weight;
        if (bins[rs].current_weight == 0) {
            bins.erase(bins.begin() + rs);
        }
    }
    for (int i = removed_items.size() - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        swap(removed_items[i], removed_items[j]);
    }
    for (int item_id : removed_items) {
        int best_bin_idx = -1, min_remaining_capacity = capacity + 1;
        for (int j = 0; j < (int)bins.size(); ++j) { // Encontra o Best Fit: o bin que minimiza o espaço vazio restante
            TB &bin = bins[j];
            if (items[item_id].weight + bin.current_weight <= capacity && !verifyConflict(bin, items[item_id])) {
                int remaining_capacity = capacity - (items[item_id].weight + bin.current_weight);
                if (remaining_capacity < min_remaining_capacity) {
                    min_remaining_capacity = remaining_capacity;
                    best_bin_idx = j;
                }
            }
        }
        if (best_bin_idx != -1) { // Se encontrou um bin (Best Fit)
            TB &bin = bins[best_bin_idx];
            bin.items.push_back(item_id);
            bin.current_weight += items[item_id].weight;
        }
        else { // Se não coube em nenhum existente, cria um novo bin
            TB new_bin;
            new_bin.current_weight = items[item_id].weight;
            new_bin.items.push_back(item_id);
            bins.push_back(new_bin);
        }
    }
}

bool randomSwapStep(const vector<TI> &items, vector<TB> &bins, const int &n_items, const int &capacity, const int max){
    if (bins.empty()) return false;
    int rs = 0, min_weight = __INT_MAX__, ri1, i = 0, item_id1;
    for(int j = 0; j<(int)bins.size(); j++){
        if(bins[j].current_weight<min_weight) {
            min_weight = bins[j].current_weight;
            rs = j;
        } 
    }
    if (bins[rs].items.empty()) {
        cleanEmptyBins(bins);
        if (bins.empty()) return false;
        return true;
    }
    ri1 = rand() % bins[rs].items.size();
    item_id1 = bins[rs].items[ri1];
    while(i<max){
        int rc = rand()%bins.size();
        if(rc == rs || bins[rc].items.empty()){
            i++;
            continue;
        }        int ri2 = rand() % bins[rc].items.size();
        int item_id2 = bins[rc].items[ri2];
        if(verifySwap(items, bins[rs], bins[rc], item_id1, item_id2, capacity)){
            swapItems(items, bins[rs], bins[rc], item_id1, item_id2);
            cleanEmptyBins(bins);
            return true;
        }
        i++;
    }
    return false;
}

bool firstSwapStep(const vector<TI> &items, vector<TB> &bins, const int &n_items, const int &capacity, const int max){
    if (bins.empty()) return false; 
    int rs = 0, min_weight = __INT_MAX__;
    for(int j = 0; j<(int)bins.size(); j++){
        if(bins[j].current_weight<min_weight) {
            min_weight = bins[j].current_weight;
            rs = j;
        } 
    }
    if (bins[rs].items.empty()) {
        cleanEmptyBins(bins);
        return true;
    }
    for(int i = 0; i < (int)bins.size(); i++){
        if(i == rs || bins[i].items.empty()) continue; 
        for(int ri1 = 0; ri1 < (int)bins[rs].items.size(); ri1++){
            int item_id1 = bins[rs].items[ri1]; 
            for(int ri2 = 0; ri2 < (int)bins[i].items.size(); ri2++){
                int item_id2 = bins[i].items[ri2];
                if(verifySwap(items, bins[rs], bins[i], item_id1, item_id2, capacity)){
                    swapItems(items, bins[rs], bins[i], item_id1, item_id2);
                    cleanEmptyBins(bins);
                    return true;
                }
            }
        }
    }
    return false;
}

bool randomMoveStep(const vector<TI> &items, vector<TB> &bins, const int &n_items, const int &capacity, const int max){
    if (bins.empty()) return false;
    int rs = 0, min_weight = __INT_MAX__, i = 0, ri, item_id;
    for(int j = 0; j<(int)bins.size(); j++){
        if(bins[j].current_weight<min_weight) {
            min_weight = bins[j].current_weight;
            rs = j;
        } 
    }
    if (bins[rs].items.empty()) {
        cleanEmptyBins(bins); 
        return true;
    }
    ri = rand() % bins[rs].items.size();
    item_id = bins[rs].items[ri];
    while(i<max){
        int rc = rand()%bins.size();
        if(rc == rs) {
            i++; 
            continue;
        }
        if(items[item_id].weight + bins[rc].current_weight <= capacity && !verifyConflict(bins[rc], items[item_id])){
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
    if (bins.empty()) return false;
    int rs = 0, min_weight = __INT_MAX__, i = 0;
    for(int j = 0; j<(int)bins.size(); j++){
        if(bins[j].current_weight<min_weight) {
            min_weight = bins[j].current_weight;
            rs = j;
        } 
    }
    if (bins[rs].items.empty()) {
        cleanEmptyBins(bins);
        return true;
    }
    for(i = 0; i < (int)bins.size(); i++){
        if(i == rs) continue;
        for(int ri = 0; ri < (int)bins[rs].items.size(); ri++){
            int item_id = bins[rs].items[ri];
            if(items[item_id].weight + bins[i].current_weight <= capacity && !verifyConflict(bins[i], items[item_id])){
                bins[i].items.push_back(item_id);
                bins[i].current_weight += items[item_id].weight;
                bins[rs].items.erase(bins[rs].items.begin()+ri);
                bins[rs].current_weight -= items[item_id].weight;
                if(bins[rs].current_weight==0) bins.erase(bins.begin()+rs);
                return true;
            }
        }
    }   
    return false;
}

void rvnd(const vector<TI> &items, vector<TB> &bins, const int &n_items, const int &capacity, const int max){
    if (bins.empty()) return;
    vector<TB> sb = bins;
    bool operation_success = false;
    int i = 0, r;
    cleanEmptyBins(sb);
    bins = sb;
    while (i<max) { 
        i++;
        r = rand()%2;
        operation_success = (r==0) ? randomMoveStep(items, sb, n_items, capacity, max):randomSwapStep(items, sb, n_items, capacity, max);
        if(operation_success && sb.size() < bins.size()){
            bins = sb; 
            i = 0; 
        }
        if(i==max-1){
            operation_success = firstMoveStep(items, sb, n_items, capacity, max);
            if(operation_success && sb.size() < bins.size()){
                bins = sb;
                i = 0;
            }
            else { 
                operation_success = firstSwapStep(items, sb, n_items, capacity, max);
                if(operation_success && sb.size() < bins.size()){
                    bins = sb;
                    i = 0;
                }
            }
        }
    }
}
