#include <bits/stdc++.h>
using namespace std;
ifstream fin("input.txt");
ofstream fout("output.txt");

int main() {

  int n, q;
  fin >> n >> q;

  vector<int> v(n);
  for(int &i : v) {
    fin >> i;
  }
  
  for(int i = 0; i < q; i++) {
    int a, b;
    fin >> a >> b;

    // Cerco a destra di a
    int dx = n;
    for(int j = a; j < n; j++) {
      if(v[j] == b) {
        dx = j - a;
        break;
      }
    }

    // Cerco a sinistra di a
    int sx = n;
    for(int j = a; j >= 0; j--) {
      if(v[j] == b) {
        sx = a - j;
        break;
      }
    }

    // Stampo il più vicino dei due 
    fout << min(sx, dx) << '\n';
  }
}