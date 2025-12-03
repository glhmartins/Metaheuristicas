#include "structures.cpp"

using namespace std;

void read(vector<TI> &items, ifstream &infile, int &capacity, int &n_itens, int &great){
    infile >> capacity >> n_itens >> great;
    for(int i = 0; i<n_itens; i++){
        TI new_item;
        infile >> new_item.weight;
        new_item.id = i;
        items.push_back(new_item);
    }
}
