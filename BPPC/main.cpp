#include "instance_reader.cpp"
#include "constructors.cpp"

using namespace std;

/*int ils(int &m, int max, int &cap, float alpha, vector<bool> &s, vector<int> &b, vector<int> &d, const vector<TP> &ma){
    vector<int> fs(2,0), fp(2,0);
    vector<bool> sf = s, sp;
    //sf = construtorGulosoAleatorio(m, cap, sf, alpha, d, b, ma);
    sf = rvnd(m, 100, cap, sf, b, d, ma);
    //fs = funcaoObjetivo(sf, ma, d, b);
    int nivel = 1;
    for(int i = 0; i<max; i++){
        sp = perturbacao(m, max, cap, nivel, sf, d, ma);
        sp = rvnd(m, 30, cap, sp, b, d, ma);
        fp = funcaoObjetivo(sp, ma, d, b);
        if(fp[0]>fs[0] && fp[1]<=cap){
            fs[0] = fp[0];
            fs[1] = fp[1];
            sf = sp;
            nivel = (nivel==1)? 1:nivel--;
        } else nivel++;
        //cout << endl << " beneficio[" << i << "]: " << fn[0] << endl;
    }
    cout << endl << "beneficio: " << fs[0] <<  " peso: " << fs[1] << endl;
    s = sf;
    cout << "[";
    for(int i = 0; i<m-1; i++) cout << ((s[i]==false)? "0, ":"1, " );
    cout << ((s[m-1]==false)? '0':'1') << ']' << endl;
    return fs[0];
}


int grasp(int &m, int max, int &cap, float alpha, vector<bool> &s, vector<int> &b, vector<int> &d, const vector<TP> &ma){
    vector<int> fs(2,0), fn(2,0);
    fs[1] = (int) MAXFLOAT;
    vector<bool> sf = s, sn;
    for(int i = 0; i<max; i++){
        sn = s;
        //sn = construtorGulosoAleatorio(m, cap, sn, alpha, d, b, ma);
        sn = rvnd(m, 30, cap, sn, b, d, ma);
        //fn = funcaoObjetivo(sn, ma, d, b);
        if(fn[0]>fs[0] && fn[1]<=cap){
            fs[0] = fn[0];
            fs[1] = fn[1];
            sf = sn;
        }
        //cout << endl << " beneficio[" << i << "]: " << fn[0] << endl;
    }
    cout << endl << "beneficio: " << fs[0] <<  " peso: " << fs[1] << endl;
    s = sf;
    cout << "[";
    for(int i = 0; i<m-1; i++) cout << ((s[i]==false)? "0, ":"1, " );
    cout << ((s[m-1]==false)? '0':'1') << ']' << endl;
    return fs[0];
}*/

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
        cout << "Num of bins: " << bins.size() << endl;
    }
    infile.close();
    return 0;
}