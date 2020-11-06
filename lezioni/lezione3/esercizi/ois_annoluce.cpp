// L'esercizio ci chiede di rispondere a query
// in cui ci è chesto di contare quanti punti
// si trovino ad una distanza < D

// per risparmiarci di calcolare la distanza con la radice quadrata [sqrt()]
// possiamo usare direttamente il quadrato della distanza come valore

// Per contare gli elementi < D, calcoliamo prima di tutte le distanza di ogni punto

// Dopodiché, ci basterà effettuare una ricerca binaria per D, riconducendo così
// effettivamente il problema a quello che facevamo in ois_ruspa

#include <bits/stdc++.h>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

int main() {
    int n;
    fin >> n;

    vector<long long> d(n);
    for(auto &x : d) {
        // usiamo i long long per non uscire dai limiti
        // degli interi
        long long a, b, c;
        fin >> a >> b >> c;
        // calcoliamo il quadrato della distanza
        x = a * a + b * b + c * c;
    }

    // ordiniamo in ordine crescente di distanza
    sort(d.begin(), d.end());

    // rispondiamo alle query usando la ricerca binaria
    int q;
    fin >> q;

    while(q--) {
        long long x;
        fin >> x;

        // calcoliamo il quadrato della distanza
        x *= x;

        // binary search - troviamo il primo valore maggiore di x
        int l = 0, r = n - 1;
        while(l != r) {
            int m = (l + r) / 2;
            if(d[m] <= x) {
                l = m + 1;
            } else {
                r = m;
            }
        }
        // tutti i valori a sinistra di l ora sono <= di x,
        // però dobbiamo ancora verificare se l lo è o meno
        // (solo quando l == n-1)
        if(d[r] <= x)
            r++;
        fout << r << '\n';
    }

}