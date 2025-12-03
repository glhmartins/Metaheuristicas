#include "instance_reader.cpp"
#include "constructors.cpp"
#include "local_search.cpp"

using namespace std;

void ils(vector<TI> &items, vector<TB> &bins, const int &n_items, const int &capacity, const float alpha, const int max_iter){
    vector<TB> aux;
    greedyRandomizedConstructor(items, bins, capacity, n_items, alpha);
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


void grasp(vector<TI> &items, vector<TB> &bins, const int &n_items, const int &capacity, const float alpha, const int max){
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

vector<double> values(vector<int> sols){
    vector<double> p(3,0);
    p[2] = MAXFLOAT;
    for(int i = 0; i<sols.size(); i++){
        p[0] += sols[i];
        if(sols[i]>p[1]) p[1] = sols[i];
        if(sols[i]<p[2]) p[2] = sols[i];
    }
    p[0] = p[0]/sols.size();
    return p;
}

vector<double> times(vector<double> time){
    vector<double> t(3,0);
    t[2] = MAXFLOAT;
    for(int i = 0; i<time.size(); i++){
        t[0] += time[i];
        if(time[i]>t[1]) t[1] = time[i];
        if(time[i]<t[2]) t[2] = time[i];
    }
    t[0] = t[0]/time.size();
    return t;
}

double desvio(vector<int> sol, double media){
    double sum = 0;
    for(int i = 0; i<sol.size(); i++) sum += pow(sol[i]-media, 2);
    sum /= media;
    sum = sqrt(sum);
    return sum;
}

int main(){
    int n_instances, capacity, n_items, great;
    srand(time(0));
    vector<TI> items;
    vector<TB> bins;
    string instance_type;
    string archives[] = {"binpack1.txt", "binpack2.txt", "binpack3.txt", "binpack4.txt", "binpack5.txt", "binpack6.txt", "binpack7.txt", "binpack8.txt"};
    ifstream infile(archives[1]);
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
        //grasp(items, bins, n_items, capacity, 0.5, 100);
        ils(items, bins, n_items, capacity, 0.5, 100);
        cout << " Local Search: " << bins.size() << " Great: " << great << endl;
    }
    infile.close();
    return 0;
}