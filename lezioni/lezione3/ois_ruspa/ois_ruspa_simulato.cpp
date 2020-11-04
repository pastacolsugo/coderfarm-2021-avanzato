#include <bits/stdc++.h>

using namespace std;


ifstream fin("input.txt");
ofstream fout("output.txt");

int main() {
    int n, t;
    fin >> n >> t;

    vector<int> m(n);
    for(int &i : m)
        fin >> i;

    for(int q = 0; q < t; q++) {
        // leggiamo la query
        int x, d;
        fin >> x >> d;
        
        // segno per un muro se è abbattuto
        vector<int> abbattuto(n, 0);

        // supponiamo che inizialmente la ruspa sia all'interno
        bool ok = true;

        // ripetiamo finché la ruspa non esce
        while (ok) {
            // per ora, non abbiamo ancora abbattuto nessun muro
            ok = false;

            // verso destra
            if(d == 0) {
                // se ci stiamo spostando verso destra, sbattiamo nel primo muro non abbattuto
                // con coordinata maggiore ad x
                for(int i = 0; i < n && !ok; i++) {
                    if(!abbattuto[i] && m[i] > x) {
                        abbattuto[i] = 1;
                        x = m[i];
                        // inverto la direzione, usando logica booleana :)
                        d = !d;
                        ok = 1;
                    }
                }
            } 
            else {
                // se ci stiamo spostando verso sinistra, cerchiamo partendo dal fondo:
                // sbattiamo nel primo non abbattuto con coordinata minore di x
                for(int i = n-1; i >= 0 && !ok; i--) {
                    if(!abbattuto[i] && m[i] < x) {
                        abbattuto[i] = 1;
                        x = m[i];
                        // inverto la direzione, usando logica booleana :)
                        d = !d;
                        ok = 1;
                    }
                }
            }
        }
        // se terminiamo, significa che non avevamo più muri da abbattere
        fout << d << ' ';
    }   
}