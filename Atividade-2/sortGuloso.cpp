#include <vector>

using namespace std;

/* Fazer sort para que o algoritmo guloso pegue sempre o de maior beneficio */

void merge(vector<int> &b, vector<int> &pos, int inicio, int meio, int fim){
    int i = inicio, j = meio+1, k = 0, auxB[fim-inicio+1], auxP[fim-inicio+1];
    while(i<=meio && j<=fim){
        if(b[i]>b[j]){
            auxB[k] = b[i];
            auxP[k] = pos[i];
            i++;
        } else {
            auxB[k] = b[j];
            auxP[k] = pos[j];
            j++;
        }
        k++;
    }
    while(i<=meio){
        auxB[k] = b[i];
        auxP[k] = pos[i];
        i++;
        k++;
    }
    while(j<=fim){
        auxB[k] = b[j];
        auxP[k] = pos[j];
        j++;
        k++;
    }
    for(k = inicio; k<=fim; k++){
        b[k] = auxB[k-inicio];
        pos[k] = auxP[k-inicio];
    }
}

void mergesort(vector<int> &b, vector<int> &pos, int inicio, int fim){
    if(inicio<fim){
        int meio = (fim+inicio)/2;
        mergesort(b, pos, inicio, meio);
        mergesort(b, pos, meio+1, fim);
        merge(b, pos, inicio, meio, fim);
    }
}