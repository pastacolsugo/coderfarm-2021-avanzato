#include <bits/stdc++.h>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

int main() {
    int n;
    fin >> n;
    // dividiamo pari e dispari
    vector<int> pari, dispari;
    for(int i = 0; i < n; i++) {
        int a;
        fin >> a;
        if(a % 2 == 0)
            pari.push_back(a);
        else
            dispari.push_back(a);
    }
    // lo mettiamo a -1, così se non troviamo risposta ha già il valore valido
    int best = -1;

    // troviamo i pari più grandi usando l'ordinamento (si può evitare, ma così è più rapido da scrivere)
    sort(pari.begin(), pari.end());
    
    // ci assicuriamo di averne almeno 2
    if(pari.size() >= 2) {
        // i due più grandi sono ultimo e penultimo
        best = max(best, pari[pari.size() - 1] + pari[pari.size() - 2]);
    }
    // ripetiamo per dispari
    sort(dispari.begin(), dispari.end());
    if(dispari.size() >= 2) {
        best = max(best, dispari[dispari.size() - 1] + dispari[dispari.size() - 2]);
    }

    fout << best;
}