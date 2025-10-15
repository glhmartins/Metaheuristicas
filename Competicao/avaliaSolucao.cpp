#include "TP.cpp"

using namespace std;

int peso(const vector<bool> &p, vector<TP> &ma,  vector<int> d){
    clock_t ti = clock(), tf;
    int sum = 0;
    for(int i = 0; i<ma.size(); i++){
        if(p[ma[i].pacote]==1){
            for(int dp: ma[i].deps){
                sum += d[dp];
                d[dp] = 0;
            }
        }
    }
    tf = clock();
    double t = (double) (tf-ti)/CLOCKS_PER_SEC;
    //cout << "tempo peso: " << t << endl;
    return sum;
}

int beneficio(const vector<bool> &p, vector<int> &b){
    int sum = 0;
    for(int i = 0; i<b.size(); i++) sum += (b[i]*p[i]);
    return sum;
}

vector<int> funcaoObjetivo(const vector<bool> &p, vector<TP> &ma, vector<int> &d, vector<int> &b){
    vector<int> bd;
    bd.push_back(beneficio(p, b));
    bd.push_back(peso(p, ma, d));
    return bd;
}
