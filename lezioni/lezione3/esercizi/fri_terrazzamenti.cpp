// la prima particolarità di questo problema sta nella
// implementazione - questa volta, non dobbiamo preoccuparci
// di gestire input e output, ci basta implementare la funzione
// descritta

// using e namespace restano
#include <bits/stdc++.h>

using namespace std;

// questa funzione conta serve per contare il costo della soluzione
// utilizzando un certo valore come primo scalino.
// trovi più info dentro la funzione stima
long long conta(int n, int h[], int start) {
  long long ans = 0;
  for(int i = 0; i < n; i++) {
    ans += abs((start + i) - h[i]);
  }
  return ans;
}

long long stima(int n, int h[]) {
  /* questo problema è piuttosto complicato.
    esistono principalmente due soluzioni diverse:
      - la prima richiede un paio di osservazioni matematiche,
        e l'utilizzo furbo della mediana
      - la seconda è più tecnica, ed è quella che cercheremo
        di utilizzare qui - sfruttando la ricerca binaria
      
    L'idea è quella di trasformare questo problema in un problema di 
    ricerca lineare, per poi trasformarlo in ricerca binaria.

    Dobbiamo quindi identificare su cosa fare la ricerca -
    in questo caso la nostra unica opzione è effettuare questa
    ricerca sulla "soluzione", ovvero sulla sequenza a scala
    da utilizzare.

    Ci immaginiamo di avere un'array che contiene le possibili soluzioni:
    la prima, è la sequenza:
      0 1 2 3 4 5 6 7 ... N-1
    seguita da
      1 2 3 4 5 6 ... N
    e, a seguire
      2 3 4 5 6 7 ... N+1
      3 4 5 6 7 8 ... N+2

    Continuando in questo modo, ci accorgiamo che possiamo effettivamente
    elencare tutte le possibili soluzioni.

    In totale, esistono H soluzioni, dove H è il massimo valore dell'altezza
    di un blocco (non avrà mai senso superare questo valore come valore di inizio).

    H vale fino a 10^9, tuttavia in un subtask arriva solo fino a 10^4 -
    calcolando in O(n) il valore effettivo di una soluzione, possiamo
    trovare la migliore in O(nh), e ottenere  20/100


    Come possiamo migliorare questa cosa?

    Ci accorgiamo che i costi di queste soluzioni seguono un certo "pattern":
      fino ad arrivare alla soluzione ottimale, diminuiscono - poi iniziano a crescere

    Vi invito a fare un po' di prove, se siete arrivati fino a questo punto.

    Rappresentando questi valori in un grafico (dove la x è l'altezza del primo scalino,
    e la y il costo della soluzione), ci accorgiamo che forma una parabola.

    In particolare, puntiamo la nostra attenzione su quello che succede analizzando
    l'intorno di una coordinata x :
      osserviamo che se muovendosi in x+1 la soluzione peggiora, vuol dire che siamo a dx della soluzione
      se invece la soluzione migliora, vuol dire che siamo a sx dell'obbiettivo
    
    possiamo quindi simulare questo processo, utilizzando la ricerca
    binaria per scegliere il punto di partenza dei nostri scalini
  */
  long long best = LLONG_MAX;n
  int ans = -1; // valore fittizio per iniziare la ricerca

  int l = 0;
  int r = 1e9; // valore di inizio massimo
  while(l != r) {
    int m = (l+r) / 2;
    // proviamo con m e m+1
    long long val_m = conta(n, h, m);
    long long val_m1 = conta(n, h, m+1);
  }
}
