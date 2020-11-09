# Lezione 3
## Indice
* [Task: ois_socks](#task-ois_socks)
* [C++: Map](#c-map)
* [Soluzione ois_socks](#soluzione-ois_socks)
* [Esercizi da svolgere](#esercizi-da-svolgere)
* [C++: Set](#c-set)
* [C++: Unordered Map/Set](#c-unordered-mapset)

## Task: ois_socks

Il problema [Washing Socks](https://training.olinfo.it/#/task/ois_socks/statement) può essere descritto in questo modo: 
* ci viene data una sequenza **S** di **N** calzini, dove **S<sub>i</sub>** indica il colore dell'**i**-esimo calzino
* i calzini della sequenza vengono estratti in ordine dalla lavatrice, e appesi in fondo ad uno "stendino"
* ogni volta che un calzino viene appeso, il robot di William lo scambia (swap) con il calzino precedente, fino a quando il calzino precedente non è dello stesso colore - o fino a che il calzino non sia arrivato all'inizio dello stendino
* una volta inseriti tutti i calzini, stampare il numero totale di swap eseguiti

Esempio illustrato:
<img src="https://i.imgur.com/JEy2NbX.png" alt="spiegazione socks" width="550"/>

Una prima idea di soluzione potrebbe essere quella di implementare una simulazione del comportamento del robot: per ciascun calzino, lo aggiungiamo al vector che rappresenta lo stendino e effettuiamo gli scambi fino a posizionarlo nel posto giusto.

Il problema di [questa soluzione](ois_socks/ois_socks_simulato.cpp) è la complessità computazionale: siccome per ciascun calzino (**N**) nel caso pessimo dobbiamo scorrere tutti i calzini inseriti precedentemente (**N**), abbiamo una complessità di **O(N<sup>2</sup>)**, che abbiamo già visto essere troppo con **N <= 10<sup>5</sup>**.

Dobbiamo quindi trovare un ragionamento che ci permetta di risolvere il problema senza dover simulare gli scambi. Ci chiediamo: da cosa dipende il numero di scambi necessario per inserire un calzino?

Dalla posizione degli elementi del suo colore!
Abbiamo due casi:
* se il colore è già stato inserito, ci basta guardare quando questo inserimento è avvenuto - siccome ogni volta i colori appena inseriti vengono allontanati il più possibile dall'estremità, più un colore è "meno recente" e meno scambi sono necessari - più precisamente, se un colore è stato inserito per **i**-esimo, saranno necessari **i** scambi
* se il colore non è ancora stato inserito, allora dovremo spostarlo in fondo - saranno necessari **x** scambi, dove **x** è il numero di colori attualmente inseriti - inoltre, ora possiamo segnare questo colore come inserito, come **x**-esimo!

Utilizzando un vector grande quanto il numero di colori, possiamo quindi arrivare ad una soluzione che si basa su un principio simile a quello della soluzione che abbiamo usato nel problema [ois_negozi](https://training.olinfo.it/#/task/ois_negozi/statement) - tuttavia, c'è un ultimo problema: il numero di colori **C** non si ferma a 10<sup>5</sup>, ma a **10<sup>9</sup>** - rendendoci quindi impossibile inizializzare un vector così grande!

## C++: Map

Prima di procedere con la soluzione da 100 punti, introduciamo un nuovo tipo di struttura dati, che probabilmente farà al caso nostro - le mappe :)

Una mappa - `map<K, V>` - è una struttura dati che associa a chiavi univoche di tipo `K` valori di tipo `V` - essenzialmente, possiamo vederla come un `vector` in cui possono essere utilizzati indici di diverso tipo, e in cui i valori non sono accessibili in modo sequenziale, ma sono invece mantenuti in ordine per chiave.

Per rendere il tutto più semplice, vediamo un po' di esempi:

```cpp
map<string, int> presenze;
```

La mappa `presenze` che abbiamo dichiarato qui nell'esempio, utilizza chiavi di tipo `string` - ciò significa che a differenza di un vector, per accedere agli elementi dovremo mettere delle stringhe nelle parantesi quadre. Inoltre, la mappa associa a ciascuna di queste stringhe un valore di tipo intero - in questo caso, il numero di presenze.

```cpp
presenze["Vittorio"] = 1;
presenze["Filippo"] = 5;
```

In questo modo, abbiamo associato a `Vittorio` una sola presenza, mentre a `Filippo` cinque.

```cpp
int x = presenze["Filippo"]; // 5
int y = presenze["Gianni"]; // 0
```

Non solo possiamo usare le quadre per inserire valori nella mappa, ma anche per accedervi, come accade anche con i vector. Quando chiediamo alla mappa le presenze di `Filippo`, ci viene restituito `5`, il valore che avevamo associato prima alla chiave.

Tuttavia, quando chiediamo il valore della chiave `Gianni`, ci viene restituito zero, nonostante questa chiave fino a questo momento non esistesse!

Questo accade perché per evitare di causare eccezioni, quando si utilizzano le parentesi quadre per accedere a una chiave non esistente questa viene immediatamente inserita, e ad essa viene associato il valore di default del tipo **V** - `0` per i valori numerici, stringa vuota (`""`) per le stringhe, `vector` vuoto per i `vector`, e così via.

```cpp
presenze.count("Vittorio"); // 1
presenze.count("Gianni"); // 1
presenze.count("Marco"); // 0
```

Con il metodo `.count()`, la mappa ci restituisce **1** se la chiave è esistente (`Vittorio`, `Gianni`) o **0** se non lo è (`Marco`).

```cpp
presenze.size(); // 3
```

Il metodo .size(), come per `vector`, ci restituisce la dimensione della mappa, ovvero il numero di coppie chiave-valore presenti.

```cpp
presenze.count("Vittorio"); // 1
presenze.erase("Vittorio");
presenze.count("Vittorio"); // 0
```

Il metodo `erase` invece ci permette di rimuovere chiavi dalla mappa.

---

Negli esempi fin'ora abbiamo usato stringa come tipo di chiave e intero come tipo di valore, ma ovviamente queste non sono le uniche opzioni disponibili:
- per il tipo di chiave **K**, possiamo scegliere qualsiasi tipo confrontabile, ovvero per cui funzioni l'operatore `<`
- per il tipo **V**, possiamo scegliere qualsiasi tipo <sub>(ad eccezione di tipi senza valore di default)</sub>

Altri esempi validi di mappe sono:
```cpp
map<double, string> valori_noti;
valori_noti[3.14159] = "pi greco";

map<int, vector<int>> negozi;

map<string, vector<string>> sinonimi;
sinonimi["problema"] = {"esercizio", "quesito"};
```

Le mappe hanno però un piccolo svantaggio rispetto ai vettori, e non vanno quindi utilizzate "a casaccio" - oltre ad un utilizzo di memoria più grande per ciascun elemento contenuto, quasi tutte le operazioni di `map` viste fin'ora  ha una complessità di **O(log<sub>2</sub>N)** (dove **N** è il numero di chiavi inserite) - immaginatevi che è come se venisse effettuata una ricerca binaria per ciascuna operazione.

Altri metodi utili:
```cpp
map<K, V> m;
m.begin(); // iteratore al primo elemento della mappa
*m.begin(); // valore del primo elemento della mappa
m.end() - 1; // iteratore all'ultimo elemento della mappa
```

Inoltre, una cosa importantissima per utilizzare le mappe correttamente è il poter iterare sulle chiavi inserite - questo si può fare utilizzando i range-based for, specificando come tipo per l'iterazione un `pair<K, V>` che combaci con i tipi utilizzati per dichiarare la mappa:

```cpp
map<string, int> presenze;
presenze["Vittorio"] = 1;
presenze["Filippo"] = 5;
presenze["Marco"]; // 0

for(pair<string, int> p : presenze)
  cout << p.first << ": " << p.second << '\n';

/*
Output:
  Filippo: 5
  Marco: 0
  Vittorio: 1
*/

// NB: Le chiavi vengono iterate in ordine crescente, l'ordine in cui sono memorizzate! 
```

In alternative ai pair, è anche possibile utilizzare la keyword `auto`:

```cpp
for(auto p : presenze)
  cout << p.first << ": " << p.second << '\n';
```

Il codice ha lo stesso risultato, tuttavia il codice potrebbe risultare più leggibile (e sicuramente è più compatto).

---


Date le similarità di utilizzo con `vector`, un uso comune di `map` è anche quello di funzionare effettivamente da array, con il vantaggio di poter però utilizzare solo la memoria necessaria a memorizzare gli indici effettivamente inseriti, evitando di sprecare memoria per gestire indici vuoti o eventuali "buchi". 

```cpp
map<int, int> array_sparso;
array_sparso[-351] = 4;
array_sparso[1000000000] = 1;
```

### Soluzione ois_socks

---

## Somme prefisse

---

### Task: ois_muffin

---

## Esercizi da svolgere

* **[abc_messaggi](https://training.olinfo.it/#/task/abc_messaggi/statement)**
  * problema che può essere risolto utilizzando `map<string>`, altamente consigliato!
* **[ois_caesar](https://training.olinfo.it/#/task/ois_caesar/statement)**
  * utilizzando le mappe, è anche possibile risolvere in modo molto efficiente questo problema di stringhe
* **[numeri](https://training.olinfo.it/#/task/numeri/statement)**
  * dopo aver visto sia le mappe che le somme prefisse, è possibile anche risolvere parzialmente questo problema - a seconda dell'implementazione, può variare in base all'implementazione ma dovreste ottenere circa **70/100** - è possibile ottenere **100** usando idee leggermente diverse, o aggiungendo qualche trucchetto alla soluzione con map :)
* **[ois_antibiotics](https://training.olinfo.it/#/task/ois_antibiotics/statement)**
  * se avete risolto tutti gli altri esercizi, o se magari siete bloccati ma avete comunque voglia di vedere un ulteriore esercizio, questo è un problema interessante che può essere risolto con map dopo qualche considerazione un po' "matematica" ;)
    * **NB:** questo problema può essere risolto anche senza usare `map`, ma spero che le mappe possano essere un buon punto di partenza per arrivare alla soluzione anche per voi!

## C++: Set

Un'altra struttura della standard library considerabile a `map<K, V>` è `set<T>`:
a differenza di map, usiamo **set** quando vogliamo gestire una collezione di elementi, che sono identificati direttamente dal loro valore, **NON** da una chiave a parte.

```cpp
#include <set>

set<int> numeri;
set<string> appello;
```


Ad esempio, possiamo usare un set per indicare i numeri già estratti durante una tombola, o gli alunni presenti ad una verifica:

Possiamo inserire elementi in con il metodo `.insert()`:

```cpp
set<int> lezioni;
lezioni.insert(3);
lezioni.insert(2);
lezioni.insert(4);
lezioni.insert(1);
```

Eliminarli con `.erase()`:

```cpp
lezioni.erase(2);
```

Verificarne la presenza con `.count()`:

```cpp
lezioni.count(2); // 0
lezioni.count(4); // 1
```

O con `.find()`:

```cpp
lezioni.find(1); // iteratore a 1
lezioni.find(2); // lezioni.end()
```

La dimensione, la otteniamo sempre con `.size()`:

```cpp
lezioni.size(); // 3
```

Possiamo iterare sugli elementi in ordine, usando un range-based for:
```cpp
for(int i : lezioni)
  cout << i << ' ';

// output: "1 3 4 "
```

Sebbene sia vero che possiamo fare tutto quello che faremo con **set** anche usando **map**, l'utilizzo di un set è comunque caldamente consigliato e rende il tutto più semplice in tutti quei casi in cui non ci serve davvero associare valori addizionali alle nostre chiavi.  

## C++: Unordered Map/Set

Sia `set` che `map` dispongono di una variante `unordered`, ovvero non ordinata - si tratta delle cosiddette **hashmap** (anche hashtable) o **hashset** (nel caso del set).

Possiamo dichiararle in questo modo:

```cpp
#include <unordered_map>

unordered_map<string, string> dizionario;

#include <unordered_set>

unordered_set<int> keys;
```

Quando non è rilevante che le chiavi siano mantenute in ordine crescente, utilizzare le versioni `unordered` consente tipicamente di migliorare le performance del nostro codice, avendo una complessità costante invece che logaritmica per le operazioni di inserimento, ricerca e rimozione.

Tuttavia, questo miglioramento non è sempre garantito o comunque non sempre è abbastanza significativo per essere notato.

Inoltre, bisogna tenere a mente un paio di cose quando si utilizza la versione `unordered`:
* siccome non si basa più sull'ordinamento, non è più possibile usare un qualsiasi tipo "confrontabile" come chiave - è comunque possibile usare la maggior parte dei tipi comuni, come `int`, `string`, o `double`; ma non è possibile (senza modifiche ulteriori) usare tipi più complessi, come `pair` o `vector`. 
* siccome i dati non sono più ordinati, iterando sulle chiavi (o sui valori nel caso del set) con un range-based for non ci garantisce più alcun tipo di ordine di accesso ai valori - sebbena sia comunque garantito che vengano iterati tutti i valori inseriti.
  Potrebbe anche capitare che inserendo gli stessi dati, l'ordine di iterazione possa variare, quindi non fate affidamento su ciò - o usate semplicemente una mappa normale se l'ordine delle chiavi vi fa comodo.