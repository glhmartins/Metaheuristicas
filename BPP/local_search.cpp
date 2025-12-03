#include "structures.cpp"

using namespace std;

void cleanEmptyBins(vector<TB> &bins) {
    bins.erase(remove_if(bins.begin(), bins.end(), [](const TB &b){
        return b.items.empty(); }
    ),bins.end());
}

bool verifySwap(const vector<TI> &items, const TB &bin1_orig, const TB &bin2_orig, int item1_id, int item2_id, const int &capacity){
    if (bin1_orig.current_weight - items[item1_id].weight + items[item2_id].weight > capacity) return false;
    if (bin2_orig.current_weight - items[item2_id].weight + items[item1_id].weight > capacity) return false;
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

void perturbation(const vector<TI> &items, vector<TB> &bins, const int &capacity, int level) {
    cleanEmptyBins(bins);
    if (bins.empty()) return;
    int bins_to_remove = level, best_bin; 
    double min_space, space;
    if (bins_to_remove >= bins.size()) bins_to_remove = max(1, (int)bins.size() - 1);
    if (bins_to_remove < 1) bins_to_remove = 1;
    vector<int> removed_items;
    sort(bins.begin(), bins.end(), [](const TB &a, const TB &b) { // Ordena bins por peso (menor peso primeiro) para destruir os piores
        return a.current_weight < b.current_weight;
    });
    for (int k = 0; k < bins_to_remove; ++k) { // Remove the lighter K bins
        if (bins.empty()) break;
        for (int item_id : bins[0].items) {
            removed_items.push_back(item_id);
        }
        bins.erase(bins.begin());
    }
    random_shuffle(removed_items.begin(), removed_items.end()); // shuffle to avoid determinism
    for (int item_id : removed_items){ // Reconstrution using Best Fit
        best_bin = -1;
        min_space = capacity + 1.0;
        for (int i = 0; i < bins.size(); ++i) {
            if (bins[i].current_weight + items[item_id].weight <= capacity) {
                space = capacity - (bins[i].current_weight + items[item_id].weight);
                if (space < min_space) {
                    min_space = space;
                    best_bin = i;
                }
            }
        }
        if (best_bin != -1) {
            bins[best_bin].items.push_back(item_id);
            bins[best_bin].current_weight += items[item_id].weight;
        } else {
            TB new_bin;
            new_bin.current_weight = items[item_id].weight;
            new_bin.items.push_back(item_id);
            bins.push_back(new_bin);
        }
    }
}

// 1. Random Swap: Swap itens between random bins to improve fitness
bool randomSwapStep(const vector<TI> &items, vector<TB> &bins, const int &capacity, const int max_iter){
    if (bins.size() < 2) return false;
    int b1, b2, item1_id, item2_id;
    for(int k=0; k < max_iter; k++) {
        b1 = rand() % bins.size();
        b2 = rand() % bins.size();
        if (b1 == b2 || bins[b1].items.empty() || bins[b2].items.empty()) continue;
        item1_id = bins[b1].items[rand() % bins[b1].items.size()];
        item2_id = bins[b2].items[rand() % bins[b2].items.size()];
        if(verifySwap(items, bins[b1], bins[b2], item1_id, item2_id, capacity)){
            swapItems(items, bins[b1], bins[b2], item1_id, item2_id);
            return true;
        }
    }
    return false;
}

// 2. Random Move: Moves an item from one random bin to another random bin
bool randomMoveStep(const vector<TI> &items, vector<TB> &bins, const int &capacity, const int max_iter){
    if (bins.size() < 2) return false;
    int from, to, item_id, item_idx;
    for(int k=0; k < max_iter; k++) {
        from = rand() % bins.size();
        if (bins[from].items.empty()) continue;
        item_idx = rand() % bins[from].items.size();
        item_id = bins[from].items[item_idx];
        to = rand() % bins.size();
        if (from == to) continue;
        if (bins[to].current_weight + items[item_id].weight <= capacity) {
            bins[to].items.push_back(item_id);
            bins[to].current_weight += items[item_id].weight;
            bins[from].items.erase(bins[from].items.begin() + item_idx);
            bins[from].current_weight -= items[item_id].weight;
            if (bins[from].items.empty()) cleanEmptyBins(bins);
            return true;
        }
    }
    return false;
}

// 3. First Move: Try emptying the lighter bin
bool firstMoveStep(const vector<TI> &items, vector<TB> &bins, const int &capacity){
    if (bins.empty()) return false;
    int rs = 0, item_id;
    double min_weight = __DBL_MAX__;
    bool success = false;
    for(int j = 0; j < bins.size(); j++){
        if(bins[j].current_weight < min_weight) {
            min_weight = bins[j].current_weight;
            rs = j;
        } 
    }
    if (bins[rs].items.empty()) { 
        cleanEmptyBins(bins); 
        return true; 
    }
    for(int ri = bins[rs].items.size() - 1; ri >= 0; ri--){
        item_id = bins[rs].items[ri];
        for(int i = 0; i < bins.size(); i++){
            if(i == rs) continue;
            if(items[item_id].weight + bins[i].current_weight <= capacity){
                bins[i].items.push_back(item_id);
                bins[i].current_weight += items[item_id].weight;
                bins[rs].items.erase(bins[rs].items.begin() + ri);
                bins[rs].current_weight -= items[item_id].weight;
                success = true;
                break;
            }
        }
    }
    if(bins[rs].items.empty()) cleanEmptyBins(bins);
    return success;
}

// 4. binReshuffle: try emptying the five smaller bins
bool binReshuffle(const vector<TI> &items, vector<TB> &bins, const int &capacity, const int attempts_limit){
    if (bins.empty()) return false;
    vector<pair<double, int>> bin_weights;
    for(int i=0; i < bins.size(); ++i) bin_weights.push_back({bins[i].current_weight, i});
    sort(bin_weights.begin(), bin_weights.end()); 
    int tries = min((int)bins.size(), 5), target_idx, best_idx;
    for(int k = 0; k < tries; ++k) {
        target_idx = bin_weights[k].second;
        TB target_bin = bins[target_idx];
        vector<TB> backup = bins;
        bins.erase(bins.begin() + target_idx);
        vector<int> reinsert = target_bin.items;
        sort(reinsert.begin(), reinsert.end(), [&](int a, int b){
            return items[a].weight > items[b].weight;
        });
        bool possible = true;
        for (int item_id : reinsert) {
            best_idx = -1;
            double min_space = capacity + 1.0;
            for (int i = 0; i < bins.size(); ++i) {
                if (bins[i].current_weight + items[item_id].weight <= capacity) {
                    double space = capacity - (bins[i].current_weight + items[item_id].weight);
                    if (space < min_space) {
                        min_space = space;
                        best_idx = i;
                    }
                }
            }
            if (best_idx != -1) {
                bins[best_idx].items.push_back(item_id);
                bins[best_idx].current_weight += items[item_id].weight;
            } else {
                possible = false;
                break;
            }
        }
        if (possible) return true;
        else bins = backup;
    }
    return false;
}

void rvnd(const vector<TI> &items, vector<TB> &bins, const int &capacity, const int max_attempts) {
    if (bins.empty()) return;
    vector<TB> current_solution = bins;
    double current_fitness = calculateFitness(current_solution, capacity), cand_fitness;
    // 0 -> Move, 1 -> Swap, 2 -> FirstMove(Greedy), 3 -> binReshuffle
    vector<int> neighborhoods = {0, 1, 2, 3}; 
    int iter_no_improve = 0;
    bool improved, success;
    while (iter_no_improve < max_attempts) {
        improved = false;
        random_shuffle(neighborhoods.begin(), neighborhoods.end());
        for (int nh : neighborhoods) {
            vector<TB> candidate = current_solution;
            success = false;
            if (nh == 0) success = randomMoveStep(items, candidate, capacity, max_attempts);
            else if (nh == 1) success = randomSwapStep(items, candidate, capacity, max_attempts);
            else if (nh == 2) success = firstMoveStep(items, candidate, capacity); 
            else if (nh == 3) success = binReshuffle(items, candidate, capacity, max(5 ,(int) (bins.size()*0.1)));
            if (success) {
                cand_fitness = calculateFitness(candidate, capacity);
                if (candidate.size() < current_solution.size()) {
                    current_solution = candidate;
                    current_fitness = cand_fitness;
                    bins = current_solution;
                    improved = true;
                    iter_no_improve = 0; 
                    break; 
                }
                else if (candidate.size() == current_solution.size() && cand_fitness > current_fitness + 1e-6) {
                    current_solution = candidate;
                    current_fitness = cand_fitness;
                    bins = current_solution;
                    improved = true;
                    if (iter_no_improve > 0) iter_no_improve--; 
                    break;
                }
            }
        }
        if (!improved) iter_no_improve++;
    }
}
