# Lezione 7
## Indice
* [Teoria dei grafi](#teoria-dei-grafi)
  * [Liste di adiacenza](#liste-di-adiacenza)
* [Task: sunnydale](#task-sunnydale)
* [Matrici di adiacenza](#matrici-di-adiacenza)

## Teoria dei grafi

Vi capiterà spesso, nell'affrontare problemi di competitive programming e non solo, di trovarvi di fronte a problemi facilmente rappresentabili dai cosiddetti "**grafi**" - potete immaginarveli come reti, come diagrammi o come schemi, ma per essere più precisi stiamo parlando di un insieme di entità (*nodi*) collegate tra loro da qualche tipo di relazione (*archi*).

Alcuni esempi banali possono essere:
* una rete di amicizie su Facebook:
<img src="https://i.imgur.com/8K7V3rD.png" alt="amicizie facebook" width="350"/>
* le strade di una città, ciascuna con la sua lunghezza:
<img src="https://i.imgur.com/7KY4Z7Q.png" alt="rete stradale" width="350"/>
* l'insieme degli account di Instagram collegati con i rispettivi "
"follow":
<img src="https://i.imgur.com/HZscGuN.png" alt="follow instagram" width="350"/>

Nonostante ciascuno di questi esempi sia abbastanza self-explanatory, osservandoli riusciamo già a ricavarci un sacco di informazioni sulle caratteristiche che può avere un grafo.

Partiamo dal primo esempio, il grafo delle amicizie su Facebook.
Innanzitutto, andiamo ad individuare quali "entità" sono rappresentate dai nodi e quali invece dagli archi: gli utenti, rappresentati dal proprio nome, sono i **nodi** del grafo, mentre invece i rapporti di amicizia, reciproci, sono gli **archi**. Notiamo come la presenza di un arco tra i nodi **A** e **B** indichi un rapporto da entrambi i lati, senza una particolare direzione: parliamo quindi di grafo **non orientato**.

Nel secondo esempio, quello della rete stradale, i **nodi** rappresentatano gli incroci tra le strade (nell'esempio non sono stati denominati in nessun modo), mentre invece gli **archi** rappresentano le strade. Notiamo che, come prima, non è specificato alcun verso di percorrenza per gli archi, di conseguenza abbiamo ancora un grafo **non orientato**.
Questa volta però, c'è un particolare ulteriore - a ciascun arco, è associata anche un'ulteriore informazione, in questo caso la lunghezza della strada: parliamo quindi di grafo **pesato**.

Nel terzo esempio, i **nodi** rappresentano gli utenti mentre gli archi ... gli archi sono diversi! Ci accorgiamo infatti che questa volta abbiamo delle vere e proprie **frecce**, che hanno un verso di percorrenza - possiamo già dire che questa volta il nostro è un grafo **orientato**, dove gli **archi** in uscita da un utente rappresentano gli utenti followati da esso. Talvolta, questi rapporti sono reciproci: in tal caso, possiamo rappresentarlo sia con due archi (*luca - emma*) che con un singola arco ma con una doppia freccia (*filippo - nico*). Osservando meglio, ci accorgiamo anche di un'altra cosa: questo grafo **non** è **completamente connesso**!
Torneremo sulla connettività dei grafi in un secondo momento, però dovrebbe già essere intuitivo dal grafo in figura come la "rete" rappresentata sia suddivisa in più parti tra loro non raggiungibili.

*D'accordo, abbiamo capito che possiamo rappresentare diversi scenari "reali" utilizzando questi grafi, ma come possiamo gestirli "in codice"?*

## Liste di adiacenza

Esistono diversi metodi per rappresentare i grafi, ciascuno con i suoi vantaggi e svantaggi. Indubbiamente però, il metodo più semplice e versatile da cui iniziare è la **lista di adiacenza**.

È facile pensare che sia difficile scrivere un programma in grado di gestire un grafo, quello che per noi è "un disegno", fatto da righe e figure. Per capire come rappresentarlo però, ci basta rispondere a una semplice domanda: quando guardi il grafo, qual è l'informazione che vai a leggere per comprenderlo?

Senza dubbio, l'informazione principale durante la lettura di un grafo sono gli archi, e più nel dettaglio sono gli archi collegati al nodo che stai guardando - e la cosa che rende così comoda la lettura è proprio l'avere tutti i collegamenti lì a portata di mano, vederli partire direttamente dal nodo.

Di conseguenza, ci basta replicare questa informazione: per ciascun nodo del grafo, ci memorizziamo la lista dei suoi archi, quindi essenzialmente la lista dei nodi a cui lui è collegato. Vediamo come applicare la cosa al grafo di Instagram, prima però assegniamo dei numeri ai nodi, in modo da rendere il tutto più comodo da rappresentare:

<img src="https://i.imgur.com/YEBxGbI.png" alt="follow instagram 2" width="350"/>

Osserviamo quindi i nodi:
* **0** followa **1** e **2**
* **1** followa **0**
* **2** followa **1** e **3**
* **3** followa **2**
* **4** non followa nessuno
* **5** e **6** followano solo **4**

Per ciascuno dei nostri **N** nodi, abbiamo quindi individuato la lista dei suoi "vicini".
E siccome in C++ possiamo usare `vector` per rappresentare le liste (con l'aiuto del metodo `push_back()`), abbiamo di fatto appena scritto un vettore di `vector`, o un `vector<vector<>>` che dir si voglia :)

Inizialmente, il nostro `vector` sarà vuoto - conterrà quindi **N = 6** liste di **0** elementi:

<img src="https://i.imgur.com/YHbt72X.png" alt="lista vuota" width="55"/>

Man mano che inseriamo gli archi, la nostra "lista di liste" inizierà a prendere forma:

<img src="https://i.imgur.com/2Bv5BpZ.png" alt="inserimento lista" width="500"/>

*(nell'ordine, sono stati inseriti gli archi **{0, 1}**, **{1, 0}**, **{1, 2}**, **{2, 3}**)*

Fino ad arrivare alla lista completa:
<img src="https://i.imgur.com/mAZ3dQl.png" alt="lista completa" width="125"/>

Sicuramente per noi è meno intuitivo leggere questa lista rispetto al grafo di partenza, però dovrebbe essere semplice accorgersi dell'equivalenza tra le due rappresentazioni, ed è semplice ricostruire il disegno del grafo partendo dalla lista di adiacenza.

*Ok, capito, ma il codice?*

Per capire come scrivere il codice, guardiamo prima come i grafi ci vengono dati in input tipicamente nei problemi:
dopo averci dato **N** ed **M**, il numero di nodi e di archi rispettivamente, abbiamo tipicamente **M** coppie di interi **A<sub>i</sub>** e **B<sub>i</sub>**, rispettivamente il nodo di partenza e quello di arrivo dell'**i**-esimo arco.

Ci basterà quindi leggere gli archi e inserirli uno alla volta nella nostra lista di adiacenza :)

```cpp
// leggiamo numero di nodi e archi
int n, m;
cin >> n >> m;

// g di grafo: la nostra lista di adiacenza :)
vector<vector<int>> g(n);

// leggiamo gli m archi
for(int i = 0; i < m; i++) {
  int a, b;
  cin >> a >> b;
  // aggiungiamo l'arco alla lista
  g[a].push_back(b);
}

```

*Ok, e questo funziona anche con gli altri esempi?*

Un passo alla volta - l'idea ovviamente è la stessa, però potrebbe essere necessario avere qualche qualche accorgimento in più.

Nell'esempio di Facebook, i legami di amicizia erano "bidirezionali" (o "non orientati") - nel grafo disegnato la cosa va da sè, ma nella nostra lista questo non viene automaticamente esplicato - infatti se aggiungiamo l'arco **{A, B}** solamente come in uscita da **A**, sarà difficile individuarlo quando cercheremo gli archi relativi al nodo **B**.
Questo problema però è facilmente risolvibile: ci basterà inserire l'arco due volte, sia in uscita da **A** diretto verso **B**, che in uscita da **B** diretto verso **A**.

Modificare il codice è molto semplice:

```cpp
// leggiamo gli m archi
for(int i = 0; i < m; i++) {
  int a, b;
  cin >> a >> b;
  // aggiungiamo l'arco alla lista
  g[a].push_back(b);
  // anche nell'altra direzione
  g[b].push_back(a);
}
```

*E nei grafi pesati?*

Beh nei grafi pesati, come l'esempio delle strade, quello che cambia è l'informazione associata all'arco: non c'è più  solamente un nodo di destinazione (un intero), ma anche una lunghezza associata (un secondo intero).
La nostra lista di adiacenza dovrà quindi contenere non liste di interi, ma liste di `pair<int, int>`.

```cpp
// lista di adiacenza per archi pesati
vector<vector<pair<int, int>>> g(n);
```

O in alternativa, una nostra `struct arco`:
```cpp
struct arco {
  int to, weight;
};

vector<vector<arco>> g(n);
```

Anche l'input subisce qualche modifica, questa volta infatti gli interi per ciascuna riga sono 3, in quanto un arco sarà rappresentato da **A**, **B** e **C**, rispettivamente nodo di partenza, nodo di arrivo e peso dell'arco (lunghezza).

```cpp
// leggiamo gli m archi
for(int i = 0; i < m; i++) {
  int a, b, c;
  cin >> a >> b >> c;
  // aggiungiamo l'arco da A a B
  g[a].push_back({b, c});
  // e quello da B ad A
  g[b].push_back({a, c});
}
```

È importante ricordarsi che i nostri pair hanno il nodo di arrivo nel campo `.first` e il loro peso nel campo `.second`.

## Task: sunnydale

Ora che sappiamo come funzionano le liste di adiacenza, siamo pronti per risolvere il nostro primo problema di grafi: [Sunnydale](https://training.olinfo.it/#/task/sunny).

Leggendo il problema, dovrebbe venirci spontaneo pensare ai grafi, non appena iniziamo a sentir parlare di gallerie da attraversare per spostarsi tra uno svincolo e l'altro. 

Le domande chiave che ci poniamo sono:
1. questo grafo è orientato?
    - no, non è orientato: dovremo quindi memorizzare gli archi in entrambe le direzioni
2. questo grafo è pesato?
    - si, ciascuna galleria ha associata una sua luminosità: dovremo quindi usare dei `pair` per gestire gli archi

Leggiamo quindi l'input e ci costruiamo la lista di adiacenza - volendo, possiamo addirittura farlo prima di avere completamente in mente la soluzione, dato che tutti (o quasi) i problemi sui grafi partono proprio dalla rappresentazione del grafo in memoria.

```cpp
// leggiamo n, m
int n, m;
fin >> n >> m;
// leggiamo h, s - di cui per ora ignoriamo il significato
int h, s;
fin >> h >> s;

// dichiariamo la lista di adiacenza
vector<vector<pair<int, int>>> g(n);

// leggiamo gli m archi
for(int i = 0; i < m; i++) {
  int a, b, c;
  cin >> a >> b >> c;
  // aggiungiamo l'arco da A a B
  g[a].push_back({b, c});
  // e quello da B ad A
  g[b].push_back({a, c});
}
```
Leggendo un po' meglio però, ci accorgiamo di una peculiarità - che d'ora in avanti sarà la terza domanda da porsi sempre quando incontriamo un grafo: gli indici dei nodi dati in input partono da **1**, non da **0** come negli array.

Qui abbiamo due scelte:
1. Anziché dichiarare la lista di adiacenza di **N** elementi, la facciamo di **N+1** elementi, così da poter usare tutti gli indici in **[1, N]** - l'indice **0** resterà vuoto, ma noi lo ignoreremo del tutto, evitando ogni possibile problema.
2. Gli indici in base **1** non ci piacciono :( prendiamo tutti i valori in input che rappresentano indici di nodi e li decrementiamo di **1**, così da renderli "0-based" (farli partire da zero). Dovremo solo fare attenzione a diminuire TUTTI gli indici, e ad incrementarli nuovamente qualora il problema ce li chiedesse come output.

Entrambe le soluzioni sono valide, e sarebbe sbagliato dirvi che una delle due è decisamente meglio dell'altra.
Tuttavia, io ho una forte preferenza per la seconda soluzioni, nonostante spesso possa risultare un pochino più brigosa da adottare (più indici da diminuire / incrementare, rispetto ad un semplice +1). Il motivo principale per questa preferenza è che so che tutto il codice che scrivo avrà sempre grafi "0 based", indipendemente da come era strutturato l'input del problema - il codice sarebbe inconsistente usando a volte "1 based" e altre "0 based", e tra le altre cose questo renderebbe più scomodo riutilizzare codice già implementato (e testato) dei vari algoritmi su grafi, che spesso sono ampiamente riutilizzabili.

La differenza è comunque davvero minima, sentitevi liberi di usare la soluzione che preferite - in queste lezioni e in tutte le soluzioni proposte comunque i grafi saranno sempre convertiti in indici "0 based" :P

Gli indici che ci interessano qui sono i due nodi di partenza e arrivo **H** ed **S**:

```cpp
// leggiamo h, s - di cui ho appena scritto il significato
int h, s;
fin >> h >> s;
// diminuisco per portarli nel range [0, N-1]
h--, s--;
```

e la coppia di nodi **A**, **B** di ciascun arco:

```cpp
// leggiamo gli m archi
for(int i = 0; i < m; i++) {
  int a, b, c;
  cin >> a >> b >> c;
  
  // decrementiamo gli indici
  a--, b--;

  // aggiungiamo l'arco da A a B
  g[a].push_back({b, c});
  // e quello da B ad A
  g[b].push_back({a, c});
}
```

Ok, ora è tempo di ragionare sul testo del problema: sappiamo che Harmony parte dal nodo **H**, e ogni volta si sposta prendendo l'arco meno luminoso... questo è semplice da fare, è una semplice ricerca del minimo, dato che possiamo accedere a tutti gli archi disponibili di qualsiasi nodo, indipendemente da quanti spostamenti abbia già fatto Harmony.

```cpp
// posizione attuale di harmony
int current = h;

// creo un arco migliore fittizio, inizialmente con luminosità infinita
pair<int, int> best = {-1, INT_MAX};
// come arco migliore fittizio un'alternativa potrebbe essere usare il primo arco
// pair<int, int> best = g[current][0]; 

// guardiamo tutti gli archi disponibili
// usiamo auto per comodità, potremmo anche scrivere pair<int, int> invece!
for(auto e : g[current]) {
  // se questa galleria è meno luminosa la salvo
  if(e.second < best.second)
    best = e;
}
```

*Mmmh ok, così però scegliamo solo il primo arco...*

Beh certo, ci basterà ripetere l'operazione dentro un ciclo, fino a quando non raggiungiamo Spike - nel frattempo, manteniamo anche il numero di gallerie percorse e il gioco è fatto!

```cpp
int current = h, galleries = 0;

// finché non arrivo da spike
while(current != s) {
  pair<int, int> best = {-1, INT_MAX};
  for(auto e : g[current])
    if(e.second < best.second)
      best = e;

  // ci spostiamo nell'arco trovato
  galleries++;
  current = best.first;
}
```

E direi che così abbiamo finito.

*Ma aspetta, così cosa succede quando non è possibile arrivare da Spike?*

Giusto, ci manca un'ultima cosa - dobbiamo gestire il caso in cui Harmony non può raggiungere Spike, ed è quindi costretta a girare in un loop infinito.

Anche qui abbiamo diverse scelte, mi limiterò a proporre le 3 "principali":
1. La prima è la più generica, è ottima, richiede un'osservazione semplice ma ci richiede anche di aggiungere abbastanza codice rispetto alle altre: l'osservazione chiave è che ci troviamo in un loop quando visitamo lo stesso nodo per la seconda volta - da lì infatti non potremo che ripetere lo stesso percorso di prima, e non ha quindi senso procedere. 
  Possiamo implementare questa cosa (cycle detection) in modo relativamente semplice, aggiungendo un vettore di booleani:

```cpp
// vettore per cycle detection
vector<bool> visited(n, false);
while(current != s) {
  // segniamo la posizione in cui ci troviamo come visitata
  visited[current] = true;

  pair<int, int> best = {-1, INT_MAX};
  for(auto e : g[current])
    if(e.second < best.second)
      best = e;

  // se stiamo per spostarci in un posto già visitato, terminiamo e segniamo -1 come risposta
  if(visited[best.first]) {
    galleries = -1;
    break; // termina il ciclo for
  }
  galleries++;
  current = best.first;
}
```
  Abbiamo quindi 3 modifiche nel codice, e una memoria extra di **O(N)**

2. Riflettendo su sta cosa del ciclo, ci accorgiamo che quello che succede è in realtà un po' più specifico di così, infatti non è che torniamo in un nodo qualunque tra quelli visitati prima, ma torniamo esattamente nel nodo dal quale siamo arrivati. Per controllare questa cosa, non serve aggiungere nessun vector, solo una singola variabile "previous":

```cpp
// posizione precedente
int previous = -1;
vector<bool> visited(n, false);
while(current != s) {
  pair<int, int> best = {-1, INT_MAX};
  for(auto e : g[current])
    if(e.second < best.second)
      best = e;

  // se stiamo per spostarci in previous, terminiamo e segniamo -1 come risposta
  if(best.first == previous) {
    galleries = -1;
    break; // termina il ciclo for
  }
  galleries++;
  // prima di spostarci, segniamo il nodo attuale come "precedente"
  previous = current;
  current = best.first;
}
```
  Sono sempre 3 aggiunte, ma un po' più semplici ;)

3. Il terzo metodo è indubbiamente il più furbo, pur essendo il più ignorante - l'idea è semplice: se Harmony non arriva da Spike dopo MOLTE gallerie, allora dev'essere impossibile per Harmony arrivarci.
  Sebbene non sia necessario dimostrarlo, dato che come idea sembra intuitivamente corretta, è possibile farlo: un metodo è quello del "pigeon hole principle" - siccome ci sono in totale **N** nodi diversi, è impossibile che dopo aver preso **N** gallerie non si sia visitato uno stesso nodo **2** volte. Possiamo quindi usare **N** come limite per terminare la visita, ma il trucco funziona anche usando un valore più grande, come **10^6** o anche **10^7**, senza bisogno di ragionare tanto :)

```cpp
vector<bool> visited(n, false);
while(current != s) {
  pair<int, int> best = {-1, INT_MAX};
  for(auto e : g[current])
    if(e.second < best.second)
      best = e;
  galleries++;
  current = best.first;

  // se ci siamo spostati troppo, terminiamo e segniamo -1 come risposta
  if(galleries > n) {
    galleries = -1;
    break; // termina il ciclo for
  }
}
```
A seconda del problema che avete di fronte, potrebbe essere più utile una delle tre idee proposte, per questo le ho lasciate tutte e 3.

Questa volta, il problema è davvero risolto: [trovate qui il codice](sunnydale/sunnydale.cpp).

Purtroppo, non credo ci siano altri problemi su training.olinfo.it risolvibili con il solo utilizzo delle liste di adiacenza, anche se è sicuramnete possibile farlo "trasformando" in grafi problemi la cui struttura può essere vista in modo più semplice (cosa che volendo è vera anche per Sunnydale) - non ho quindi da segnalare altri esercizi da svolgere come allenamento.

Tuttavia, per chi avesse voglia di approfondire un ulteriore argomento, vi lascio qualche riga di spiegazione su una delle alternative alle liste di adiacenza...
  

## Matrici di adiacenza

Questo argomento non è stato trattato durante la lezione, pertando non l'ho ancora inserito nei riassunti - sarà aggiunto quando ne avrò il tempo, siccome fortemente correlato alle liste di adiacenza, tuttavia più limitato nei casi d'uso.
