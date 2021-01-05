#include <bits/stdc++.h>
using namespace std;

#ifdef EVAL
#include <fstream>
#define cin fin
#define cout fout
ifstream fin("input.txt");
ofstream fout("output.txt");
#endif

using ll = long long;

// per risolvere questo problema combiniamo l'utilizzo delle mappe con
// quello delle somme prefisse: ci accorgiamo infatti che esiste un segmento
// di somma S solo se abbiamo un prefisso di somma K a cui possiamo togliere
// un altro prefisso più corto di somma X tale che K-X = S

// come possiamo fare a contare quante coppie di prefissi soddisfano questa proprietà?

// il modo più semplice è quello di iterare sui prefissi dal più corto al più lungo
// man mano che iteriamo, manteniamo la frequenza dei prefissi già visti fin'ora,
// per ciascuna possibile dimensione: avremo quindi una map<int, int> freq
// in cui appunto freq[x] indicherà quanti prefissi abbiamo già visto
// di somma x. 

// come usiamo questa informazione? se il prefisso attuale è di somma K,
// andiamo a identificare il valore X necessario: X = K-S (basta risolvere l'equazione sopra)

// quindi, andiamo a vedere quanti prefissi di valore X abbiamo a disposizione,
// informazione che abbiamo nella mappa freq.

// ciascuno di questi prefissi rappresenta una soluzione valida, quindi
// avremo qualcosa del tipo "ans += freq[K - S]"

// a seconda del tipo di mappa usato (map, unordered_map),
// con questo metodo è possibile ottenere un punteggio tra 60 e 85.

// con qualche trucco per velocizzare l'input, è anche possibile fare
// 100 punti.


// per fare 100 punti però, sarebbe consigliato un altro metodo,
// leggermente più "macchinoso" e che richiede qualche osservazione
// in più. se ci sarà tempo, vedremo quella tecnica in futuro!

int main() {
  // ottimizzazione input/output
  cin.tie(0);
  cin.sync_with_stdio(0);

  int m, n;
  cin >> m >> n;
  map<int, int> freq;
  int ans = 0, sum = 0;
  // posso sempre togliere un prefisso di lunghezza zero (non togliere niente)
  freq[0] = 1;
  for(int i = 0; i < n; i++) {
  	int tmp;
  	cin >> tmp;
  	sum += tmp;
    // conto i prefissi che vanno bene e li aggiungo alla soluzione
  	auto x = freq.find(sum - m);
  	if(x != freq.end())
  		ans += x->second;
    // aggiungo questo prefisso a quelli che sto contando
  	freq[sum]++;
  }
  cout << ans;

}