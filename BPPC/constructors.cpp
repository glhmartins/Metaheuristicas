#include "greedy_sort.cpp"

using namespace std;

bool verifyConflict(const TB &bin, const TI &item){
    for(int item_bin: bin.items){
        for(int item_to_pack: item.conflicts){
            if(item_bin==item_to_pack) return true;
        }
    }
    return false;
}

void greedyConstructor(vector<TI> items, vector<TB> &bins, const int &capacity, const int &n_items){
    TB bin;
    bin.current_weight = 0;
    bin.id = 0;
    bins.push_back(bin);
    mergesort(items, 0, n_items-1);
    for(int i = 0; i<n_items; i++){
        int j = 0;
        bool packed = false;
        while(j<bins.size() && !packed){
            if((items[i].weight+bins[j].current_weight<=capacity) && !verifyConflict(bins[j], items[i])){
                bins[j].current_weight += items[i].weight;
                bins[j].items.push_back(items[i].id);
                packed = true;
            }
            j++;
        }
        if(j==bins.size() && !packed){
            bin.current_weight = items[i].weight;
            bin.id = bins.size();
            bin.items.push_back(items[i].id);
            bins.push_back(bin);
        }
    }
}

void greedyRandomizedConstructor(vector<TI> items, vector<TB> &bins, const int &capacity, const int &n_items, float alpha){
    TB bin;
    bin.current_weight = 0;
    bin.id = 0;
    bins.push_back(bin);
    mergesort(items, 0, n_items-1);
    while(items.size()>=1){
        int j = 0, r = (rand()%(items.size()))*alpha;;
        bool packed = false;
        while(j<bins.size() && !packed){
            if((items[r].weight+bins[j].current_weight<=capacity) && !verifyConflict(bins[j], items[r])){
                bins[j].current_weight += items[r].weight;
                bins[j].items.push_back(items[r].id);
                packed = true;
            }
            j++;
        }
        if(j==bins.size() && !packed){
            bin.current_weight = items[r].weight;
            bin.id = bins.size();
            bin.items.push_back(items[r].id);
            bins.push_back(bin);
        }
        items.erase(items.begin()+r);
    }
}

void RandomConstructor(vector<TI> items, vector<TB> &bins, const int &capacity, const int &n_items){
    TB bin;
    bin.current_weight = 0;
    bin.id = 0;
    bins.push_back(bin);
    mergesort(items, 0, n_items-1);
    while(items.size()>=1){
        int j = 0, r = rand()%items.size();;
        bool packed = false;
        while(j<bins.size() && !packed){
            if((items[r].weight+bins[j].current_weight<=capacity) && !verifyConflict(bins[j], items[r])){
                bins[j].current_weight += items[r].weight;
                bins[j].items.push_back(items[r].id);
                packed = true;
            }
            j++;
        }
        if(j==bins.size() && !packed){
            bin.current_weight = items[r].weight;
            bin.id = bins.size();
            bin.items.push_back(items[r].id);
            bins.push_back(bin);
        }
        items.erase(items.begin()+r);
    }
}
