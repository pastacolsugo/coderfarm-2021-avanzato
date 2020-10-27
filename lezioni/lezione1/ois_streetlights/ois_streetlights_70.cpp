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

    // per ogni "finestra" lunga M, conto le luci accese, poi accendo partendo da destra
    for(int i = 0; i + m - 1 < n; i++) {
        int accese = 0;
        for(int j = i; j < i + m; j++)
            accese += v[j];
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