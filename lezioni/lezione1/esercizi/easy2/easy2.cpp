#include <bits/stdc++.h>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

int main() {
    int n;
    fin >> n;

    int best = -1;
    for(int i = 0; i < n; i++) {
        int a, b;
        fin >> a >> b;
        int sum = a + b;
        // cerco la somma massima, che sia pari!
        if(sum % 2 == 0 && sum > best)
            best = sum;
    }
    fout << best;
}