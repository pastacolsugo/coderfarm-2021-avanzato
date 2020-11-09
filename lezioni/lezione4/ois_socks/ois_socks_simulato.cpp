#include <bits/stdc++.h>

using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

int main (){

    int n, c;
    fin >> n >> c;

    long long swaps = 0;
    vector<int> calzini;

    for(int i = 0; i < n; i++) {
        int c;
        fin >> c;

        // inseriamo il calzino in fondo allo stendino
        calzini.push_back(c);
        // lo spostiamo finché non troviamo un colore uguale a sinistra
        // NB: terminiamo quando i == 1 per evitare di accedere all'indice -1 
        for(int i = calzini.size() - 1; i - 1 >= 0; i--) {
            // se troviamo una coppia uguale
            if(calzini[i-1] == calzini[i]) {
                // mettiamo il calzino in i sopra a quello in i-1, quindi rimuoviamo
                // un valore dal vector
                calzini.erase(calzini.begin() + i);
                // terminiamo
                break;
            } else {
                swap(calzini[i], calzini[i-1]);
                swaps++;
            }
        }
    }
    fout << swaps << '\n';
}