#include <bits/stdc++.h>
using namespace std;
ifstream fin("input.txt");
ofstream fout("output.txt");

int main() {
  int n, q;
  fin >> n >> q;

  // Leggo i negozi
  vector<int> v(n);
  for(int &i : v) {
    fin >> i;
  }
  
  // Leggo le query
  for(int i = 0; i < q; i++) {
    int a, b;
    fin >> a >> b;

    // Calcolo la distanza di ogni negozio
    int dist = n;
    for(int j = 0; j < n; j++) {
      // Considero il negozio solo se del tipo giusto
      if(v[j] == b) {
        dist = min(dist, abs(a - j));
      }
    }
    // Stampo il risultato della query
    fout << dist << '\n';
  }
}