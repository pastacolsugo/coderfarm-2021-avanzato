#include <bits/stdc++.h>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

int main (){

    int n, c;
    fin >> n >> c;

    long long swaps = 0;

    map<int, int> pos;
    int colori = 0;

    for(int i = 0; i < n; i++) {
        int tmp;
        fin >> tmp;

        // se il colore manca, lo aggiungo
        if(pos.count(tmp) == 0) {
            pos[tmp] = colori;
            colori++;
        }

        // ora che so la posizione, conto gli swaps
        swaps += pos[tmp];
    }
    fout << swaps << '\n';
}