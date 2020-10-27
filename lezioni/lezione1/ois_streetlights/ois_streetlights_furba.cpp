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
    
    int ans = 0;
    
    // controllo i primi M, come nella soluzione normale
    int window = accumulate(v.begin(), v.begin() + m, 0);
    if(window < k) {
        for(int i = m - 1; i >= 0 && window < k; i--)
            if(v[i] == 0) {
                v[i] = 1;
                window++;
                ans++;
            }
    }

    // da ora in poi, SE accendiamo una lampada, è sempre l'ultima
    for(int i = m; i < n; i++) {
        window += v[i];
        window -= v[i - m];
        if(window < k) {
            v[i] = 1;
            window++;
            ans++;
        }
    }

    cout << ans;
}