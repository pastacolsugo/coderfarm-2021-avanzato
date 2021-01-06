#include <bits/stdc++.h>
using namespace std;
ifstream fin("input.txt");
ofstream fout("output.txt");

// NB: questo codice è leggermento diverso da quello contenuto nel file della lezione,
// è quello che abbiamo scritto insieme durante la lezione "live" - c'è qualche piccolissima
// differenza ma mettendo insieme le parti contenute nella lezione dovreste riuscire
// a ricostruire una versione funzionante anche da lì :)

int main() {
  // ottimizzazione input/output
  fin.tie(0);
  fin.sync_with_stdio(0);

  int n, m, h, s;
  fin >> n >> m >> h >> s;

  // porto in base 0 tutti gli indici
  h--, s--;

  // vector<pair<int,int>> g[n];
  vector<vector<pair<int,int>>> g(n);
  for(int i = 0; i < m; i++) {
    int a, b, l;
    fin >> a >> b >> l;
    // porto in base 0
    a--, b--;
    
    g[a].push_back({b, l});
    g[b].push_back({a, l});
  }

  /*for(int i = 0; i < n; i++) {
    cout << i << ": ";
    for(auto arco : g[i])
      cout << "{" << arco.first << ", " << arco.second << "}, ";
    cout << '\n';
  }*/

  vector<bool> visitato(n, 0);

  int gallerie = 0;
  while(h != s) {
    // segna la visita se non c'è già stata
    if(!visitato[h])
      visitato[h] = 1;
    else {
      gallerie = -1;
      break;
      /*
      fout << -1;
      return 0;
      */
    }

    pair<int, int> sol = {-1, m + 5};
    for(auto arco : g[h]) {
      if(arco.second < sol.second)
        sol = arco;
    }
    // ci spostiamo
    h = sol.first;
    gallerie++;

    /* se abbiamo fatto troppi spostamenti
    if(gallerie > 1e5) {
      gallerie = -1;
      break;
    }*/

  }

  fout << gallerie;
}