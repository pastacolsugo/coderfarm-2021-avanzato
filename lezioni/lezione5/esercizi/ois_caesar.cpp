#include <bits/stdc++.h>
using namespace std;
ifstream fin("input.txt");
ofstream fout("output.txt");

// esistono principalmente due approcci per risolvere il problema,
// ne vedremo nel dettaglio uno solo ma in fondo al codice trovi
// un accenno anche all'altra soluzione.

// per risolvere il problema, occorre trovare un metodo
// per capire quando due stringhe possono coincidere
// se viene applicato un cifrario diverso
// ad esempio, le stringhe AAA e BBB coincidono, se shiftiamo
// di -1 BBB (ricorda che B - 1 = A !)

// essenzialmente, a noi non importa la lettera con cui una 
// stringa inizia (infatti, AAA = BBB nonostante inizino con
// lettere diverse) - ma solamente la differenza tra ciascuna lettera
// e quella successiva nella stringa - di fatto, se facciamo
// iniziare due stringhe con la stessa lettera, le due stringhe
// saranno uguali solo se per ogni due caratteri nello stesso indice
// c'è la stessa "distanza" al carattere nell'indice successivo nella stringa

// ad esempio, le differenze tra caratteri successivi di AAA sono 0 e 0, 
// poiché A - A = 0

// per la stringa ABD invece, le differenze sono 1 e 2
// scriviamo quindi una funzione diff(s) che presa una stringa ci restituisce
// il vector con le differenze tra valori consecutivi
// chiamiamo questo vector "diffarray" per comodità

// se due stringhe hanno lo stesso "diffarray", allora possiamo rincodurre
// l'una all'altra (e viceversa)

// come facciamo a contare quante stringhe hanno lo stesso diffarray? 
// iterare su ogni coppia di stringhe sarebbe troppo lento, ma fortunatamente
// per noi le mappe possono lavorare con qualsiasi tipo di dato confrontabile:
// (si, gli array si possono confrontare in c++)

// possiamo contare quindi la frequenza con cui ciascun diffarray compare,
// come se fosse un qualsiasi tipo "numerico"

// nel file della quarta lezione si fa riferimento a come contare la frequenza
// usando una mappa.

vector<int> diff(string &a) {
  vector<int> d(a.size()-1);
  for(int i = 0; i + 1 < a.size(); i++)
    d[i] = (a[i+1] - a[i] + 26) % 26;
  return d;
}

int main() {
  // ottimizzazione input/output
  fin.tie(0);
  fin.sync_with_stdio(0);

  int n, d;
  fin >> n >> d;

  // leggo le parole in input
  vector<string> parole(n);
  for(string &s : parole)
    fin >> s;
  

  // conto quante volte ottengo ciascun "diff array"
  map<vector<int>, int> freq;
  for(string &s: parole) {
    freq[diff(s)]++;
    // vector<int> d = diff(s);
    // freq[d] += 1;
  }
  int best = 0;
  for(auto &x : freq) {
    if(x.second > best)
      best = x.second;

    // best = max(best, x.second);
  }

  fout << best;
  
}


// un altro modo in cui si poteva risolvere il problema,
// sempre usando le mappe, era quello di ricondurre ciascuna stringa
// ad una stringa "radice" comune, ad esempio shiftandole tutte
// in modo da farle iniziare con la stessa lettera.
// in questo modo, poi si può usare una mappa come sopra per contare
// la stringa più frequente.