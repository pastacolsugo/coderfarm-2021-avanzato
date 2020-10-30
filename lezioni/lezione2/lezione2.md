# Lezione 2
## Indice
* [Esercizi assegnati](#esercizi-assegnati)
  * [ois_streetlights](#ois_streetlights)
  * [easy3](#easy3)
* [Range based for](#range-based-for)
* [Task: ois_negozi](#introduzione-al-corso)
  * [Soluzione *"naive"* - 50/100](#soluzione-naive)
    * [Velocizzare input/output: 80/100](#velocizzare-io)
    * [Migliorare la ricerca: 80/100](#migliorare-la-ricerca)
  * [Soluzione furba: 100/100](#soluzione-furba)

## Esercizi assegnati

### ois_streetlights

Nella prima lezione, era stato assegnato di completare a **100** punti il problema ***ois_streetlights***.

Sebbena l'idea era stata accennata nella [prima lezione](../lezione1/lezione1.md) ed è disponibile [un'implementazione](../lezione1/ois_streetlights/ois_streetlights.cpp) corretta, cerchiamo di completare il discorso.

Nella [soluzione da 70 punti](../lezione1/ois_streetlights/ois_streetlights_70.cpp), il numero di lampioni accesi veniva calcolato in modo indipendente per ciascun *"blocco"*. Abbiamo però detto che conoscendo il valore di un blocco, è semplice calcolare il valore del blocco successivo:
<img src="https://i.imgur.com/Wi0kTow.png" alt="spiegazione blocchi" width="450"/>

Come illustrato nel disegno, conoscendo il valore del blocco blu (**4**), per calcolare il blocco rosso ci basterà togliere l'**1** iniziale, e aggiungere l'**1** finale (**4 - 1 + 1 = 4**).

Nel nostro codice, ci basterà quindi modificare il ciclo dei *blocchi*: se ci troviamo nel primo blocco, allora dobbiamo contare manualmente il numero di lanterne accesi, altrimenti utilizziamo la logica vista ora per velocizzare il conteggio:

```cpp
for(int i = 0; i + m - 1 < n; i++) {
    if(i == 0) {
        // conto tutto solo se è la prima finestra (o primo blocco)
        for(int j = i; j < i + m; j++)
            accese += v[j];
    }
    else {
        // tolgo la posizione precedente e aggiungo l'ultima a destra
        accese += v[i + m - 1];
        accese -= v[i - 1];
    }
    
    [...]
}
```
Ci servirà anche aggiungere una variabile esterna al ciclo, in questo caso chiamata `accese`, in modo da mantenere il conteggio dei lampioni (o lanterne) accese.

Il resto del codice può rimanere invariato, anche se può essere fatta qualche considerazione: quante volte viene ripetuto il secondo ciclo nel peggiore dei casi?
Nel primo segmento, è possibile che sia necessario accendere più di un lampioni, ma in tutti gli altri no - infatti, se un blocco ha almeno **K** lanterne successive, il blocco successivo ne ha comunque almeno **K - 1**, siccome al più una lanterna viene tolta. In particolare, la lanterna da accendere non va neanche cercata, sarà infatti sempre l'ultima aggiunta.

Un codice che usa questo accorgimento è presente nei [file della prima lezione](../lezione1/ois_streetlights/ois_streetlights_furba.cpp).

## easy3

Insieme a **easy2**, che però non sarà commentato perché ritenuto semplice quasi quanto **easy1**, vale la pena spendere due parole su **easy3** - infatti, la [soluzione più semplice](../lezione1/esercizi/easy3/easy3_70.cpp), che prova manualmente a calcolare il valore di ciascuna possibile coppia, ottiene un punteggio di **70/100**, poiché con **N = 10^5** non possiamo annidare due cicli di lunghezza **N** ciasciuno (complessità **O(N^2)**).

L'idea è quindi quella di cercare solo **4** numeri:
- i due pari più grandi
- i due dispari più grandi

Infatti, se la soluzione esiste è necessariamente la somma di una di queste due coppie.
Esistono diversi metodi per cercare questi numeri, ad esempio:
- iterare sui numeri, mantenendo come per la ricerca del massimo i valori migliori incontrati fin'ora, estendendo però la soluzione in modo da poter gestire **2** massimi per *categoria*
- dividere i numeri in pari e dispari, e ordinare poi i due array ([codice proposto](../lezione1/esercizi/easy3/easy3.cpp))

## Range based for

In alcuni delle soluzioni della scorsa lezione, ma soprattutto in quelle di questa lezione, potrebbe comparire questo tipo di cicli `for`:
```cpp
for(tipo variabile : vettore) {
  ...
}
```

Questo tipo di cicli viene chiamato `range-based for` e possiamo considerarlo una feature del c++ comparabile al `foreach` di altri linguaggi.

Quando vogliamo eseguire lo stesso codice per ciascun elemento di una collezione, possiamo quindi usare questo tipo di ciclo, che possiamo quindi leggere come se fosse un *"per ogni"*:

```cpp
vector<int> v(10);

// Per ogni elemento i di v, stampa i
for(int i : v) {
  cout << i << '\n';
}

vector<int> u;
// Per ogni elemento i di v, aggiungi i*2 al vettore u
for(int i : v)
  u.push_back(i * 2);
```

Durante l'esecuzione di questo ciclo, verrà quindi creata una variabile (negli esempi, di nome `i`) del tipo specificato (`int`) a cui verranno assegnati in ordine tutti i valori contenuti nel vettore (`v`), uno per ciascuna iterazione.

**NB:** la variabile `i` che stiamo creando negli esempi, è a tutti gli effetti una nuova variabile. Di fatto, il primo ciclo potrebbe essere riscritto in questo modo:

```cpp
for(int index = 0; index < v.size(); index++) {
  int i = v[index];
  // Contenuto del ciclo d'esempio
  cout << i << '\n';
}
```

Siccome iteriamo creando appunto una nuova variabile, in questo modo non sarà possibile modificare il contenuto del vettore modificando direttamente il contenuto della variabile usata per l'iterazione (`i`).

Per fare ciò, e poter quindi usare questi cicli cose come la lettura dell'input, dovremmo dichiarare la variabile usata per l'iterazione come riferimento (`*`):
```cpp
for(int &i : v) {
  cin >> i;
}
```

In questo modo, ogni modifica sulla variabile `i` verrà riflessa negli elementi del vettore `v`.

## Task: ois_negozi

Il problema *Shopping Stress* ci da una lista di **N** negozi, ciascuno di un determinato tipo **t<sub>i</sub>**, seguita da una lista di **Q** query (richieste): nella **i**-esima richiesta, dobbiamo indicare quanto spotarsi al minimo dalla posizione **a<sub>i</sub>** per raggiungere un negozio di tipo **b<sub>i</sub>**.

<h3 id="soluzione-naive"> Soluzione "naive" - 50/100 </h3>

La prima soluzione che ci può venire in mente è la seguente: per ciascuna query, calcoliamo la distanza dalla posizione **a<sub>i</sub>** a quella di ciascun negozio, considerando validi solo i risultati relativi ai negozi dello stesso tipo:

```cpp
// Leggo le query
for(int i = 0; i < q; i++) {
  int a, b;
  fin >> a >> b;

  // Calcolo la distanza di ogni negozio
  int dist = n;
  for(int j = 0; j < n; j++) {
    // Considero il negozio solo se del tipo giusto
    if(v[j] == b) {
      dist = min(dist, abs(a - j));
    }
  }
  // Stampo il risultato della query
  fout << dist << '\n';
}
```

Sebbene questa soluzione sia corretta, otteniamo un punteggio di soli **50** punti, siccome la complessità dell'algoritmo sarà di **O(n * q)** (*n* operazioni per ciascuna delle *q* richieste).

Codice della soluzione : [ois_negozi_50.cpp](ois_negozi/ois_negozi_50.cpp)

<h4 id="velocizzare-io"> Velocizzare input/output: 80/100 </h4>

Un trucchetto che ogni tanto può portare le nostre soluzioni ad ottenere qualche punto in più, superando qualche testcase a bruciapelo, consiste nel velocizzare la lettura dell'input, utilizzando due metodi della classe `fstream` (e non solo):

```cpp
fin.tie(0);
fin.sync_with_stdio(0);
```

Questi due metodi disabilitano alcune impostazioni che potremmo definire di "sicurezza", e rendono l'input effettivamente più veloce. La stessa cosa può anche essere applicata all'output, anche se tipicamente il vantaggio ottenuto sarà minore:

```cpp
fout.tie(0);
fout.sync_with_stdio(0);
```

Anche se non sempre basterà applicare questa ottimizzazione per velocizzare l'input, il mio consiglio è di includere queste due semplici righe al vostro codice - soprattutto in gara!

Codice con ottimizzazione input/output: [ois_negozi_fast_input.cpp](ois_negozi/ois_negozi_fast_input.cpp)

**NB**: utilizzare questi metodi può diventare inutile se poi viene utilizzato `endl` al posto di `"\n"` per andare a capo nell'output - ricordatevi che usare `endl` svuota il buffer ogni volta, e rende le operazioni di output molto più lente!

**NB2**: a seconda del traffico su [training.olinfo.it](training.olinfo.it), potrebbe capitare che il codice sopra non ottenga **80** punti per qualche millisecondo - l'importante per assicurarsi che l'input sia stato effettivamente velocizzato è confrontare i tempi di questa soluzione con quelli ottenuti senza aver utilizzato i metodi `tie` e `sync_with_stdio`.

<h4 id="migliorare-la-ricerca"> Migliorare la ricerca: 80/100 </h4>

Un altro trucchetto per velocizzare di quel poco che basta per ottenere i punti del terzo subtask e arrivare comunque ad **80/100**, è quello di migliorare il metodo con cui cerchiamo il negozio più vicino: se anziché iniziare a guardare dall'inizio della lista, partissimo direttamente dalla posizione **a** specificata dalla query, potremmo fermarci al primo negozio di tipo **b** incontrato a destra o a sinistra:

```cpp
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
```

In questo modo, la complessità rimarrà sempre di **O(n * q)** nel caso pessimo, ma possiamo aspettarci che l'esecuzione di una query sarà molto più veloce nel caso medio (se i negozi sono disposti in modo casuale).

Codice con ricerca migliorata: [ois_negozi_ricerca_migliorata.cpp](ois_negozi/ois_negozi_ricerca_migliorata.cpp)

<h3 id="soluzione-furba"> Soluzione furba - 100/100 </h3>

Per capire come velocizzare la nostra soluzione, ci poniamo la seguente domanda: possiamo guardare meno negozi di quelli che stiamo guardando? 

Già inizialmente avevamo risposto di sì a questa domanda, evitando quindi di guardare i negozi più lontani del più vicino, sia a destra che sinistra.
Ora però cerchiamo di fare una scrematura ancora più grande: non ci sono solo i negozi "più lontani" a rallentare la ricerca, ma anche quelli "più vicini", ovvero più in generale tutti i negozi che non sono del tipo **b** che noi stiamo cercando.

Come facciamo a filtrarli? L'idea è quella di dividere i negozi (le loro posizioni) in contenitori, in modo da poter gestire direttamente solo quelli del tipo che interessa a noi.

<img src="https://i.imgur.com/TD0oEcD.png" alt="spiegazione contenitore" width="550"/>

L'immagine sopra cerca di spiegare questa idea: per ciascun negozio, andiamo a inserire il suo indice nella lista corrispondente al suo tipo:
- per il primo negozio, di tipo `3`, viene inserito l'indice `0` nella lista dei negozi di tipo `3`
- per il secondo negozio, di tipo `2`, viene inserito l'indice `1` nella lista dei negozi di tipo `2`
- per il terzo negozio, di tipo `3`, viene inserito il suo indice `2` nella lista dei negozi di tipo `3`

Una volta che abbiamo a disposizione le liste di ciascun tipo, diventa semplice cercare il negozio più vicino: ci basterà infatti iterare direttamente sulla lista dei negozi del tipo richiesto, limitando notevolmente lo spazio di ricerca.

Rimane da definire una cosa: come facciamo a realizzare queste "liste"?

La scelta più ovvia per la rappresentazione delle liste di negozi è un vettore di vettori, per l'esattezza un `vector<vector<int>>` - utilizzare i vector ci semplifica notevolmente la vita poiché possiamo averli inizialmente tutti vuoti, espandendo le liste solo man mano che i negozi vengono inseriti.

Dobbiamo fare attenzione a una solo cosa ora - quanti tipo di negozi potrebbero esserci? Il testo lo dice chiaramente: il tipo di ogni negozio (**t<sub>i</sub>**) è compreso tra **1** e **10^5**, ci basterà quindi inizializzare **100 000** di queste liste:

```cpp
// dichiariamo il limite come costante
const int MAXT = 1e5;
vector<vector<int>> negozi(MAXT);
```

Ora, non ci resta che riempire le liste, inserendo gli indici nelle liste:

```cpp
for(int i = 0; i < n; i++) {
  int indice = i;
  int tipo = v[i];
  // inseriamo l'indice nella lista del tipo
  negozi[tipo].push_back(indice);
}
```

Adesso, possiamo rispondere alle query iterando solo nella lista corrispondente:

```cpp
for(int i = 0; i < q; i++) {
  int a, b;
  fin >> a >> b;
  int dist = n;
  // itero sugli indici dei negozi di tipo b
  for(int x : negozi[b])
    dist = min(dist, abs(x - a));
  fout << dist << '\n';
}
```

Effettuate queste modifiche, la nostra soluzione otterrà finalmente **100** punti.

Trovate il codice sia [qui](ois_negozi/ois_negozi.cpp) che su [repl](https://repl.it/@FilippoSoldati/negozi2) :) 