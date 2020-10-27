// includo tutte le librerie dello standard
#include <bits/stdc++.h>

using namespace std;

// inizializzo due stream per fare input/output su file
ifstream fin("input.txt");
ofstream fout("output.txt");

int main() {
    int n;
    fin >> n;

    // creo un vettore di n elementi, inizialmente tutti 0
    vector<int> v(n);

    // leggo il vettore
    for(int &i : v) {
        fin >> i;
    }

    // stampo il massimo elemento contenuto all'interno
    fout << *max_element(v.begin(), v.end());
}