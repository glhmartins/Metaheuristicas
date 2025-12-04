#include "instance_reader.cpp"
#include "constructors.cpp"
#include "local_search.cpp"

using namespace std;

void ils(vector<TI> &items, vector<TB> &bins, const int &n_items, const double &capacity, const int max_iter){
    vector<TB> aux;
    RandomConstructor(items, bins, capacity, n_items);
    cout << "constructor: " << bins.size();
    rvnd(items, bins, capacity, max_iter);
    int level = 1;
    double current_fitness = calculateFitness(bins, capacity), aux_fitness;
    for(int i = 0; i < max_iter; i++){
        aux = bins;
        perturbation(items, aux, capacity, level);
        rvnd(items, aux, capacity, max_iter);
        aux_fitness = calculateFitness(aux, capacity);
        if(aux.size() < bins.size()){
            bins = aux;
            current_fitness = aux_fitness;
            level = 1;
        } 
        else if (aux.size() == bins.size() && aux_fitness > current_fitness + 1e-6) {   
            bins = aux;
            current_fitness = aux_fitness;
            level = 1;
        }
        else if (level < (int) (n_items*0.1)) level++;
    }
}

void grasp(vector<TI> &items, vector<TB> &bins, const int &n_items, const double &capacity, const float alpha, const int max){
    vector<TB> bins_copy = bins, aux;
    int best_constructor = __INT_MAX__;
    for(int i = 0; i<max; i++){
        aux = bins;
        greedyRandomizedConstructor(items, aux, capacity, n_items, alpha);
        if(aux.size()<best_constructor) best_constructor = aux.size();
        rvnd(items, aux, capacity, max);
        if(aux.size()<bins_copy.size() || i==0) bins_copy = aux;
    }
    cout << "constructor: " << best_constructor;
    bins = bins_copy;
}

int main(){
    int n_instances, n_items, great, greats = 0, best = 0;
    double times = 0, capacity, gap;
    bool first_exec = true;
    clock_t ti, tf;
    srand(time(0));
    vector<double> best_solution, current_solution;
    vector<TI> items;
    vector<TB> bins;
    string instance_type;
    string archives[] = {"binpack1.txt", "binpack2.txt", "binpack3.txt", "binpack4.txt", "binpack5.txt", "binpack6.txt", "binpack7.txt", "binpack8.txt"};
    for(int j = 0; j<10; j++){
        current_solution.clear();
        greats = 0;
        ti = clock();
        ifstream infile(archives[2]);
        if(!infile.is_open()){
            cout << "Error" << endl;
            exit(1);
        }
        infile >> n_instances;
        for(int i = 0; i<n_instances; i++){
            items.clear();
            bins.clear();
            infile >> instance_type;
            cout << "Instance type: " << instance_type << endl;
            read(items, infile, capacity, n_items, great);
            grasp(items, bins, n_items, capacity, 0.5 , 100);
            //ils(items, bins, n_items, capacity, 100);
            cout << " Local Search: " << bins.size() << " Great: " << great << endl;
            if(bins.size()<=great) greats++;
            gap = (double) (bins.size()-great)/great;
            if (gap<0) gap = 0;
            current_solution.push_back(gap);
        }
        if (first_exec || greats > best) {
            best = greats;
            best_solution = current_solution;
            first_exec = false;
        }
        tf = clock();
        times += (double) (tf-ti)/CLOCKS_PER_SEC;;
        infile.close();
    }
    double media_gap = 0;
    for(int i = 0; i<n_instances; i++) media_gap += best_solution[i];
    media_gap /= n_instances;
    cout << "Melhor OR: " << best << "/" << n_instances << endl;
    cout << "Gap médio: " << media_gap << endl;
    cout << "tempo médio de execução do arquivo: " << (double) times/10 << endl;
    return 0;
}
