#include "structures.cpp"

using namespace std;

void generateConflicts(vector<TI> &items, int &n_itens, float alpha){
    float random;
    for(int i = 0; i<n_itens; i++){
        for(int j = 0; j<n_itens; j++){
            random = (float) rand()/RAND_MAX;
            if(random<=alpha){
                items[i].conflicts.push_back(items[j].id);
                items[j].conflicts.push_back(items[i].id);
            }
        }
    }
}

void read(vector<TI> &items, ifstream &infile, int &capacity, int &n_itens, int &great, float alpha){
    infile >> capacity >> n_itens >> great;
    for(int i = 0; i<n_itens; i++){
        TI new_item;
        infile >> new_item.weight;
        new_item.id = i;
        items.push_back(new_item);
    }
    generateConflicts(items, n_itens, alpha);
}
