#include <iostream>

using namespace std;

void bubble(int *o, int *p, int *b, int tam){
    int i, j, to, tp, tb;
    for (i = 0; i<tam-1; i++){
        for(j = i+1; j<tam; j++){
            if ((b[i]/p[i])<=(b[j]/p[j])){
                to = o[i];
                tp = p[i];
                tb = b[i];
                o[i] = o[j];
                p[i] = p[j];
                b[i] = b[j];
                o[j] = to;
                p[j] = tp;
                b[j] = tb;
            }
        }
    }
}

int mochila(int *o, int *p, int *b, int *s, int tam, int peso){
    int pa = 0, i = 0, sum = 0;
    while(pa+p[i]<=peso){
        s[i] = 1;
        sum += b[i];
        pa += p[i];
        i++;
        cout << pa << endl;
    }
    return sum;
}


int main(){
    int o[] = {1,2,3,4,5,6}, p[] = {4,5,7,9,6,15}, b[] = {2,2,3,4,4,10}, s[] = {0,0,0,0,0,0};
    int tam = sizeof(o)/sizeof(int), sum = 0, peso = 30;
    bubble(o, p, b, tam);
    sum = mochila(o, p, b, s, tam, peso);
    for(int i = 0; i<tam; i++) cout << b[i] << " ";
    cout << endl;
    for(int i = 0; i<tam; i++) cout << s[i] << " ";
    cout << endl << "f(s): " << sum << endl;
    return 0;
}