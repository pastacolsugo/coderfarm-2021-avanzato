#include <bits/stdc++.h>
using namespace std;
ifstream fin("input.txt");
ofstream fout("output.txt");

int main() {

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
    int dist = n;
    for(int x : negozi[b])
      dist = min(dist, abs(x - a));
    fout << dist << '\n';
  }

}