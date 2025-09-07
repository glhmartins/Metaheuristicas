#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

int mochila(int *o, int *p, int *b, int *s, int tam, int peso){
    srand(time(NULL));
    int pa = 0, r = rand()%tam, sum = 0;
    do {
        if(s[r]!=1){
            s[r] = 1;
            sum += b[r];
            pa += p[r];
            cout << pa << endl;
        }
        r = rand()%tam;
    } while((pa+p[r]<=peso));
    return sum;
}


int main(){
    int o[] = {1,2,3,4,5,6}, p[] = {4,5,7,9,6,15}, b[] = {2,2,3,4,4,10}, s[] = {0,0,0,0,0,0};
    int tam = sizeof(o)/sizeof(int), sum = 0, peso = 30;
    sum = mochila(o, p, b, s, tam, peso);
    for(int i = 0; i<tam; i++) cout << b[i] << " ";
    cout << endl;
    for(int i = 0; i<tam; i++) cout << s[i] << " ";
    cout << endl << "f(s): " << sum << endl;
    return 0;
}