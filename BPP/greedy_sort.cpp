#include "structures.cpp"

using namespace std;

void merge(vector<TI> &items, int &start, int &mid, int &end){
    int i = start, j = mid+1, k = 0;
    TI auxTi[end-start+1];
    while(i<=mid && j<=end){
        if(items[i].weight>items[j].weight){
            auxTi[k] = items[i];
            i++;
        } else {
            auxTi[k] = items[j];
            j++;
        }
        k++;
    }
    while(i<=mid){
        auxTi[k] = items[i];
        i++;
        k++;
    }
    while(j<=end){
        auxTi[k] = items[j];
        j++;
        k++;
    }
    for(k = start; k<=end; k++) items[k] = auxTi[k-start];
}

void mergesort(vector<TI> &items, int start, int end){
    if(start<end){
        int mid = (end+start)/2;
        mergesort(items, start, mid);
        mergesort(items, mid+1, end);
        merge(items, start, mid, end);
    }
}