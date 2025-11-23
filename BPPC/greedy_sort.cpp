#include "structures.cpp"

using namespace std;

void merge(vector<TI> &items, int &inicio, int &meio, int &fim){
    int i = inicio, j = meio+1, k = 0;
    TI auxTi[fim-inicio+1];
    while(i<=meio && j<=fim){
        if(items[i].weight>items[j].weight){
            auxTi[k] = items[i];
            i++;
        } else {
            auxTi[k] = items[j];
            j++;
        }
        k++;
    }
    while(i<=meio){
        auxTi[k] = items[i];
        i++;
        k++;
    }
    while(j<=fim){
        auxTi[k] = items[j];
        j++;
        k++;
    }
    for(k = inicio; k<=fim; k++) items[k] = auxTi[k-inicio];
}

void mergesort(vector<TI> &items, int inicio, int fim){
    if(inicio<fim){
        int meio = (fim+inicio)/2;
        mergesort(items, inicio, meio);
        mergesort(items, meio+1, fim);
        merge(items, inicio, meio, fim);
    }
}