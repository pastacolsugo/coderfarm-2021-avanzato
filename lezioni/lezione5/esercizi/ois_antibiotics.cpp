#include <bits/stdc++.h>
using namespace std;
ifstream fin("input.txt");
ofstream fout("output.txt");

int main() {
  // ottimizzazione input/output
  fin.tie(0);
  fin.sync_with_stdio(0);

  // la soluzione di questo problema usa un paio di osservazioni chiave:

  // è importante accorgersi che se non è possibile iniziare in un determinato
  // momento X, non sarà possibile iniziare neanche in X-T, così come in nessun
  // X - k*T, dove k è un qualsiasi numero intero positivo - cos'hanno in comune 
  // i numeri X-T e X-k*T ? il loro valore in % T (resto divisione per T).

  // infatti, se aggiungiamo T o multipli di T a un numero, il risultato dell'operazione
  // % T non cambia mai.

  // ad esempio, con T = 30 e H1 = 10, H2 = 40; tra i due tempi l'unico
  // rilevante è il maggiore, H2, siccome basta H2 per rendere impossibile
  // iniziare in H1 (10), così come tutte le eventuali posizioni precedenti.

  // questo ci permette di dire che ci interessano al più T numeri, non N;
  // dato che se due numeri hanno lo stesso modulo, ci basterà considerare
  // il più grande (e aggiungere T ad esso).

  // questo ci permette di risolvere tutti i subtask con T piccolo (90 punti),
  // se consideriamo in modo corretto i moduli "liberi"

  // per ottenere il punteggio pieno però, dobbiamo risolvere anche il caso in cui
  // T <= 10^9. per farlo, ci basta una semplice osservazione:
  // se T > N (10^5), allora sicuramente ci sarà un "modulo" libero W,
  // senza nessun Hi tale che Hi%T = W, per il "pigeon hole principle".

  // di conseguenza, in tal caso ci basterà trovare il più piccolo valore "libero".

  // la soluzione è quindi "il più piccolo modulo libero" se c'è, 
  // oppure il modulo di cui abbiamo salvato il valore minore

  int n, t;
  fin >> n >> t;

  vector<int> v(n);
  for(int & i : v)
    fin >> i;

  // segno il max di ogni modulo
  map<int, int> last;
  for(int i : v)
    last[i % t] = max(last[i%t], i);

  // cerco un modulo libero - il primo può valore al massimo n+1
  // (se non è chiaro cerca su internet video sul pigeon hole principle)
  for(int i = 0; i < min(n+1, t); i++)
    if(last.count(i) == 0) {
      // stampiamo e terminiamo, dato che l'abbiamo trovato
      fout << i << '\n';
      return 0;
    }
  // non abbiamo trovato moduli liberi, quindi cerco il modulo con il valore più piccolo
  int mini = INT_MAX;
  for(auto x : last)
    mini = min(mini, x.second);
  
  // stampo il mini, + T per evitare l'impegno
  fout << mini+t << '\n';

}