#include <bits/stdc++.h>
using namespace std;
ifstream fin("input.txt");
ofstream fout("output.txt");

int main() {
  // ottimizzazione input/output
  fin.tie(0);
  fin.sync_with_stdio(0);

  int n, k;
  fin >> n >> k;

  vector<int> muffin(n);
  for(int &i : muffin)
    fin >> i;

  // calcola le somme prefisse
  vector<int>pref(n);
  pref[0] = muffin[0];
  for(int i = 1; i < n; i++) {
    pref[i] = pref[i-1] + muffin[i];
  }

  // il minimo valore possibile è k x -1000, la bontà minima di un singolo muffin
  int best = k * -1000;

  // proviamo tutti gli intervalli, solo quelli grandi k però - quindi
  // ci assicuriamo che i + k 1 non sfori la fine dell'array
  for(int i = 0; i + k - 1 < n; i++) {
    int sum;
    // qua dobbiamo fare attenzione - non possiamo togliere pref[i-1] se i è 0!
    if(i == 0) {
      sum = pref[i+k-1];
    } else {
      sum = pref[i+k-1] - pref[i-1];
    }
    // metodo alternativo per fare tutto in una riga
    // int sum = pref[i + k - 1] - (i > 0 ? pref[i-1] : 0);

    // salvo il risultato migliore
    best = max(best, sum);
  }

  fout << best;

}