# Lezione 3
## Indice
* [Task: ois_socks](#task-ois_socks)
* [C++: Map](#c-map)
* [Soluzione ois_socks](#soluzione-ois_socks)
* [Esercizi da svolgere](#esercizi-da-svolgere)
* [C++: Set](#c-set)
* [C++: Unordered Map/Set](#c-unordered-mapset)

## Task: ois_socks

---

## C++: Map

---

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