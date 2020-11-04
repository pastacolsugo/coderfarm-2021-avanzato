#include <bits/stdc++.h>

using namespace std;


ifstream fin("input.txt");
ofstream fout("output.txt");

int main() {
  int n, t;
  fin >> n >> t;

  vector<int> m(n);
  for(int &i : m)
    fin >> i;

  for(int i = 0; i < t; i++) {
    int x, d;
    fin >> x >> d;
    
    // per ogni muro, conto se è minore di x
    int minori = 0;
    for(int muro : m) {
      if(muro < x)
        minori++;
      else
        break;
      // NB: possiamo fare questo break poiché sappiamo
      //     che i muri sono già in ordine crescente,
      //     quindi da lì in poi saranno tutti > a x!
    }

    int maggiori = n - minori;
    // esco a sinistra se ho meno minori
    if (minori < maggiori)
      fout << 1 << ' ';
    // esco a destra se ho meno maggiori
    else if (maggiori < minori)
      fout << 0 << ' ';
    // se sono pari, non cambio la direzione
    else
      fout << d << ' ';
  }
}