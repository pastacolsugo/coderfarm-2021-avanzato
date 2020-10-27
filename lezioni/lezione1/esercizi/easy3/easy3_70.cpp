#include <bits/stdc++.h>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

int main() {
    int n;
    fin >> n;

    vector<int> v(n);
    for(int i = 0; i < n; i++)
        fin >> i;

    // proviamo tutte le coppie: questa soluzione ottiene solo 70 punti, essendo lenta
    int best = -1;
    for(int i = 0; i < n; i++)
        for(int j = i + 1; j < n; j++) {
            int somma = v[i] + v[j];
            if(somma % 2 == 0 && somma > best)
                best = somma;
        }

    fout << best; 

}