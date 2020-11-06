#include <bits/stdc++.h>
using namespace std;
ifstream fin("input.txt");
ofstream fout("output.txt");

int main() {

  // questa soluzione è il file ../lezione2/ois_negozi/ois_negozi.cpp
  // opportunamente modificato utilizzando la ricerca binaria 

  fin.tie(0);
  fin.sync_with_stdio(0);
  fout.tie(0);
  fout.sync_with_stdio(0);
  
  int n, q;
  fin >> n >> q;

  vector<int> v(n);
  for(int &i : v) {
    fin >> i;
  }

  const int MAXT = 1e5;

  vector<vector<int>> negozi(MAXT);
  for(int i = 0; i < n; i++) {
    negozi[v[i]].push_back(i);
  }

  for(int i = 0; i < q; i++) {
    int a, b;
    fin >> a >> b;
    // i negozi sono già sortati per indice, possiamo fare ricerca binaria
    // e poi guardare i due più vicini

    // cerchiamo l'ultimo minore - come in ois_ruspa
    int l = 0, r = negozi[b].size() - 1;
    while(l != r) {
      int m = (l + r + 1) / 2;
      // se il valore in m è minore, è ok - quindi arrotondiamo per eccesso!
      if (negozi[b][m] < a)
        l = m;
      else
        r = m - 1;
    }

    // il migliore è o il negozio in l, o quello dopo - dato che abbiamo
    // determinato la posizione dell'utente
    int dist = abs(a - negozi[b][l]);
    if(l + 1 < negozi[b].size()) 
      dist = min(dist, abs(a - negozi[b][l+1]));

    fout << dist << '\n';
  }

}