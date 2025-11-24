#include "instance_reader.cpp"
#include "constructors.cpp"
#include "local_search.cpp"

using namespace std;

void ils(vector<TI> &items, vector<TB> &bins, const int &n_items, const int &capacity, const float alpha, const int max){
    vector<TB> aux = bins;
    greedyRandomizedConstructor(items, aux, capacity, n_items, alpha);
    rvnd(items, aux, n_items, capacity, max);
    int nivel = 1;
    for(int i = 0; i<max; i++){
        //aux = perturbacao(m, max, cap, nivel, sf, d, ma);
        rvnd(items, aux, n_items, capacity, max);
        if(aux.size()<bins.size()){
            bins = aux;
            nivel = (nivel==1)? 1:nivel--;
        } else nivel++;
    }
    bins = aux;
}


void grasp(vector<TI> &items, vector<TB> &bins, const int &n_items, const int &capacity, const float alpha, const int max){
    vector<TB> bins_copy = bins, aux;
    for(int i = 0; i<max; i++){
        aux = bins;
        greedyRandomizedConstructor(items, aux, capacity, n_items, alpha);
        rvnd(items, aux, n_items, capacity, max);
        if(aux.size()<bins_copy.size() || i==0) bins_copy = aux;
        cout << "Num of bins: " << bins_copy.size() << endl;
    }
    bins = bins_copy;
}

vector<double> valoresFo(vector<int> sols){
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

vector<double> tempos(vector<double> tempo){
    vector<double> t(3,0);
    t[2] = MAXFLOAT;
    for(int i = 0; i<tempo.size(); i++){
        t[0] += tempo[i];
        if(tempo[i]>t[1]) t[1] = tempo[i];
        if(tempo[i]<t[2]) t[2] = tempo[i];
    }
    t[0] = t[0]/tempo.size();
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
    int n_instances, capacity, n_items;
    srand(time(NULL));
    vector<TI> items;
    vector<TB> bins;
    string instance_type;
    string archives[] = {"binpack1.txt", "binpack2.txt", "binpack3.txt", "binpack4.txt", "binpack5.txt", "binpack6.txt", "binpack7.txt", "binpack8.txt"};
    ifstream infile(archives[0]);
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
        read(items, infile, capacity, n_items, 0);
        //for(int j = 0; j<bins.size(); j++) cout << "bin " << j << " weight: " << bins[j].current_weight << endl;
        //greedyConstructor(items, bins, capacity, n_items);
        grasp(items, bins, n_items, capacity, 0.2, 10);
        //cout << "Num of bins: " << bins.size() << endl;
    }
    infile.close();
    return 0;
}