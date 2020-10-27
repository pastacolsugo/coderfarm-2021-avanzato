#include <bits/stdc++.h>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

int main() {
  int n;
  fin >> n;

  // numero più grande letto fin'ora
  int maxi = -1000;
  for(int i = 0; i < n; i++) {
    int tmp;
    fin >> tmp;
    if(tmp > maxi) {
      maxi = tmp;
    }
  }
  fout << maxi;
}