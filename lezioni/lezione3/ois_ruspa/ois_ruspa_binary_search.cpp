#include <bits/stdc++.h>

using namespace std;


ifstream fin("input.txt");
ofstream fout("output.txt");

int main() {
  int n, t;
  fin >> n >> t;

  vector<int> v(n);
  for(int &i : v)
    fin >> i;

  for(int i = 0; i < t; i++) {
    int x, d;
    fin >> x >> d;
    
    // ricerca binaria: cerco l'ultimo muro < x
    int l = 0, r = n - 1;
    while(l != r) {
      // arrotondo per eccesso, vedi note lezione3
      int m = (l+r+1) / 2;
      // se il muro è minore, non devo andare più a sinistra di così
      if(v[m] < x)
        l = m;
      // se il muro è maggiore, m supera già il limite,
      // quindi devo fermarmi prima
      else
        r = m - 1;
    }
    // l = r = indice dell'ultimo muro < x
    // di conseguenza, ho l + 1 muri a sinistra, e il restante a destra
    int muri_sx = l + 1;
    int muri_dx = n - muri_sx;
    
    if(muri_sx < muri_dx)
      fout << 1 << ' ';
    else if(muri_dx < muri_sx)
      fout << 0 << ' ';
    else
      fout << d << ' ';
  }
}