#include <bits/stdc++.h>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

int main() {
    int n, m, k;
    fin >> n >> m >> k;

    // leggo i valori delle lampade
    vector<int> v(n);
    for(int &i : v) {
        fin >> i;
    }

    // contiene la risposta (answer)
    int ans = 0;

    // mantengo il conto dell'ultima finestra vista
    int accese = 0;
    // per ogni "finestra" lunga M, conto le luci accese, poi accendo partendo da destra
    for(int i = 0; i + m - 1 < n; i++) {
        if(i == 0) {
            // conto tutto solo se è la prima finestra
            for(int j = i; j < i + m; j++)
                accese += v[j];
        }
        else {
            // tolgo la posizione precedente e aggiungo l'ultima a destra
            accese += v[i + m - 1];
            accese -= v[i - 1];
        }
        // finché non ne ho accese abbastanza, cerco lanterne spente da accendere
        for(int j = i + m - 1; j >= i && accese < k; j--) {
            if(v[j] == 0) {
                v[j] = 1;
                accese++;
                ans++;
            }
        }
    }
    fout << ans;
}