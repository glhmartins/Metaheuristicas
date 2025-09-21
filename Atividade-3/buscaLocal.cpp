#include "avaliaSolucao.cpp"
#include <ctime>
#include <cmath>

using namespace std;

vector<int> randomStep(int m, int max, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    srand(time(NULL));
    vector<int> s1 = s;
    vector<int> fs = funcaoObjetivo(s, ma, d, b), fn;
    int r, i = 0;
    do {
        r = rand()%s.size();
        s1[r] = (s1[r] == 1) ? 0:1; 
        fn = funcaoObjetivo(s1, ma, d, b);
        if((fn[0]>fs[0]) && (fn[1]<=cap)) return s1;
        i++;
    } while (i<max);
    return s;
}

vector<int> firstStep(int m, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    vector<int> s1;
    vector<int> fs = funcaoObjetivo(s, ma, d, b), fn;
    for(int i = 0; i<m; i++){
        s1 = s;
        s1[i] = (s1[i] == 1) ? 0:1; 
        fn = funcaoObjetivo(s1, ma, d, b);
        if((fn[0]>fs[0]) && (fn[1]<=cap)) return s1;
    }
    return s;
}

vector<int> bestStep(int m, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    vector<int> s1;
    vector<int> fs = funcaoObjetivo(s, ma, d, b), fn;
    for(int i = 0; i<m; i++){
        s1 = s;
        s1[i] = (s1[i] == 1) ? 0:1; 
        fn = funcaoObjetivo(s1, ma, d, b);
        if((fn[0]>fs[0]) && (fn[1]<=cap)) {
            fs = fn;
            s = s1;
        }
    }
    return s;
}

vector<int> randomImprovement(int m, int max, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    srand(time(NULL));
    vector<int> s1 = s;
    vector<int> fs = funcaoObjetivo(s, ma, d, b), fn;
    int i = 0;
    do {
        s1 = randomStep(m, max, cap, s, b, d, ma);
        if(s!=s1){
            s = s1;
            i = 0;
        }
        i++;
    } while(i<=max);
    return s;
}

vector<int> firstImprovement(int m, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    vector<int> s1 = s;
    vector<int> fs = funcaoObjetivo(s, ma, d, b), fn;
    int i = 0;
    do {
        s1 = firstStep(m, cap, s, b, d, ma);
        if(s!=s1){
            s = s1;
            i = 0;
        }
        else break;
        i++;
    } while(i<=m);
    return s;
}

vector<int> bestImprovement(int m, int cap, vector<int> s, vector<int> b, vector<int> d, vector<vector<int>> ma){
    vector<int> s1 = s;
    vector<int> fs = funcaoObjetivo(s, ma, d, b), fn;
    int i = 0;
    do {
        s1 = bestStep(m, cap, s, b, d, ma);
        if(s!=s1){
            s = s1;
            i = 0;
        }
        else break;
        i++;
    } while(i<=m);
    return s;
}
