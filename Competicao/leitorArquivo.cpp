#include "TP.cpp"

using namespace std;

void converteLinhaTamanhos(ifstream &arq, int &m, int &n, int &ne, int &cap){
    string line;
    getline(arq, line);
    istringstream iss(line);
    vector<string> sizes;
    for (string s; iss >> s; ){
        sizes.push_back(s);
    }
    m = stoi(sizes.at(0));
    n = stoi(sizes.at(1));
    ne = stoi(sizes.at(2));
    cap = stoi(sizes.at(3));
}

void converteLinha(ifstream &arq, vector<int> &x){
    string line;
    getline(arq, line);
    istringstream iss(line);
    for (string s; iss >> s; ){
        x.push_back(stoi(s));
    }
}

void auxDependencia(string &line, vector<int> &aux){
    istringstream iss(line);
    for (string s; iss >> s; ){
        aux.push_back(stoi(s));
    }
}

void converteDependencias(ifstream &arq, vector<TP> &ma){
    string line;
    int i = -1;
    while(getline(arq, line) && line != ""){
        vector<int> aux;
        auxDependencia(line, aux);
        if(ma.size()>0 && i==aux[0]) ma[i].deps.push_back(aux[1]);
        else {
            i++;
            TP p;
            p.pacote = aux[0];
            p.deps.push_back(aux[1]);
            ma.push_back(p);
        }
    }
}

void leArquivo(vector<int> &d, vector<int> &b, vector<TP> &ma, string &nomeArquivo, int &m, int &n, int &ne, int &cap){
    ifstream arq(nomeArquivo);
    converteLinhaTamanhos(arq, m, n, ne, cap);
    converteLinha(arq, b);
    converteLinha(arq, d);
    converteDependencias(arq, ma);
}
