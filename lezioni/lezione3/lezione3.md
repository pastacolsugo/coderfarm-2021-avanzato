# Lezione 3
## Indice
* [Task: ois_ruspa](#task-ois_ruspa)
* [Ricerca binaria](#ricerca-binaria)
  * [Soluzione ois_ruspa](#soluzione-ois_ruspa)
* [Esercizi da svolgere](#esercizi-da-svolgere)
* [C++: Sorting](#c-sorting)
* [C++: Pairs](#c-pairs)

## Task: ois_ruspa

L'esercizio sui cui si basa la lezione di oggi è [SmartRuspa](https://training.olinfo.it/#/task/ois_ruspa/statement).
Ci sono **N** muri disposti lungo una linea, di cui ci vengono date le coordinate **M<sub>i</sub>** in ordine crescente.
I muri devono essere abbattuti da una ruspa, che viene posizionata in una coordinata libera (senza muri) e inizia a muoversi in una direzione **D** (**0** indica destra, **1** sinistra) fino a quando:

* sbatte in un muro: in questo caso, il muro viene abbattuto, e la **direzione** della ruspa si **inverte**
* supera la coordinata del muro più a sinistra o quello più a destra: in questo caso, la ruspa viene fermata manualmente da William

Il nostro compito è quello di rispondere ad una serie di query (domande), in cui William ci chiede di aiutarlo a determinare da quale lato uscirebbe una ruspa se posizionata in coordinata **X** con direzione **D**.

#### Simulazione - 30/100

Una prima idea di soluzione per il problema potrebbe essere quella di simulare il comportamento della ruspa per ciascuna query - possiamo simulare lo spostamento della ruspa, segnando come abbattuti i muri che incontriamo.

Questa soluzione non è stata vista durante la lezione, poiché implementarla potrebbe portare via diverso tempo - ed è possibile semplificare di molto l'implementazione ragionando un po' di più su quello che il problema ci chiede :)

Tuttavia, trovate [qui](ois_ruspa/ois_ruspa_simulato.cpp) il codice se volete darci un'occhiata - l'implementazione proposta ha una complessità computazionale di **O(TN<sup>2</sup>)** e ottiene un punteggio di **30/100** - anche se sicuramente possono essere implementate simulazioni migliori.

### Accorgimento - 70/100

Osservando quel che succede simulando alcuni esempi, ci accorgiamo che la posizione di partenza determina il risultato finale: il lato da cui la ruspa esce è sempre quello con meno muri a bloccarla - dato che per ogni muro distrutto da un lato ne viene sempre distrutto uno anche nel lato opposto.

Inoltre, se c'è lo stesso numero di muri sia a destra che a sinistra della ruspa, questa uscirà dal lato verso il quale si muoveva inizialmente: dopo aver distrutto due ruspe, infatti, la ruspa è sempre rivolta verso la direzione "originale" (e avere lo stesso numero di muri sia a sinistra che a destra implica un numero pari di muri totali).

Possiamo quindi semplificare di molto l'implementazione, limitandoci a contare quanti sono i muri a sinistra della ruspa (e di conseguenza, quelli a destra): [questa soluzione](ois_ruspa/ois_ruspa_conteggio.cpp) ha una complessità di **O(NT)** e ci permette di ottenere **70/100**.

Vedremo ora una tecnica che ci permetterà di risolvere con **100/100** questo problema :) 

## Ricerca binaria

Per ora, quando c'è stato bisogno di cercare un valore all'interno di un'array, ci siamo serviti sempre dello stesso metodo, la *ricerca lineare* - o per intenderci, di un ciclo `for`.

Tuttavia, in determinate condizioni, si può fare molto di meglio, basta pensare a quando utilizzi un dizionario per cercare la definizione di una parola:
se stai cercando la parola "*Ruspa*" e apri il dizionario in una pagina che inizia con la parola "*Negozi*", di certo non continuerai a sfogliare al contrario, poiché sai già in che direzione si trova ciò che stai cercando.

Se una lista è **ordinata**, effettivamente possiamo fare molto di meglio che cercare con un ciclo `for` - guardando all'elemento centrale della lista, possiamo eliminare in un colpo solo metà degli elementi di cui voglio sapere il valore: se ad esempio sto cercando il numero **5** e vedo che a metà dell'array è presente il valore **10**, non ho più alcun motivo di cercare nella seconda metà del vettore - ho diminuito lo spazio di ricerca di **N / 2** in un'unica operazione - molto meglio della diminuzione di **1** che avrei ottenuto controllando il primo (o viceversa, l'ultimo) elemento del vettore.

Questo concetto prende il nome di *ricerca binaria* (o dicotomica) ed è di fondamentale importanza in tantissimi problemi e algoritmi.

Ripetendo la logica di sopra fino a quando lo spazio di ricerca non viene ridotto a un singolo elemento, la nostra ricerca si concluderà molto rapidamente - più precisamente, in **log<sub>2</sub>N** passaggi (per una lista di **N** valori).

Che cosa indica **log<sub>2</sub> N**?
*Log* è il logaritmo, l'operazione inversa dell'elevamento a potenza, in questo caso in base 2:
**log<sub>2</sub>(A) = X** significa che **2<sup>X</sup> = A**.

Più in generale si ha:
**log<sub>b</sub>(x) = y** significa che **b<sup>y</sup> = x**, ovvero che il logaritmo in base **b** di **x** è l'esponente a cui elevare **b** per ottenere **x**.

A noi non interessa troppo comprendere a pieno il funzionamento dei logaritmi, ma se siete interessati [trovate qui una spiegazione molto più dettagliata](https://www.youmath.it/lezioni/analisi-matematica/le-funzioni-elementari-e-le-loro-proprieta/83-logaritmi.html) - quel che interessa a noi è sapere che i logaritmi sono funzioni estremamente "lente" (anche uno debolo come quello in base 2!).

Con funzione "lenta" intendiamo che al crescere del parametro **x**, il valore del suo logaritmo cresce molto, molto poco: basta pensare che **log<sub>2</sub>(10) = 3.32**, mentre invece **log<sub>2</sub>(1000) = 9.97** !

E che addirittura, **log<sub>2</sub>(10<sup>6</sup>) = 19.93** e **log<sub>2</sub>(10<sup>9</sup>) = 29.90** :)

Ok, abbiamo capito che questa ricerca binaria può ottimizzare di molto la complessità del nostro codice, ma come facciamo ad implementarla?

Questa è l'idea dell'algoritmo:
* inizialmente, indichiamo con **L** l'indice di inizio dell'array e con **R** l'indice di fine: l'insieme **[L, R]** indica il nostro spazio di ricerca
* fino a quando **L** e **R** non coincidono, procediamo in questo modo:
  * determiniamo **M**, il punto medio dello spazio di ricerca: **M = (L+R) / 2**
  * ci chiediamo se il valore **X** che stiamo cercando si trovi prima di **M**, o tra **M** e **R**
    * se **V[M] < X**, allora **X** non può che trovarsi dopo **M** - vorrà dire che il nostro limite sinistro **L** dovrà aggiornarsi: **L = M + 1**
    * se **V[M] >= X**, allora **X** non può trovarsi dopo **M** - vorrà dire che il nostro limite destro dovrà aggiornarsi: **R = M**
  

Siccome il ragionamento non è subito immediato, vi invito a fare un po' di prove (o a guardare qualche [gif](https://i.pinimg.com/originals/e2/9a/31/e29a31c78bcc0d07c612adc77acc09a0.gif) online), prima a mano seguendo il ragionamento riportato qui sopra, poi anche testando e verificando la correttezza di questo codice:

```cpp
// restituisce l'indice di x in v, o -1 se l'elemento non è presente
int find_in_sorted_vector(vector<int> &v, int x) {
  int l = 0, r = v.size() - 1;
  while(l != r) {
    int m = (l+r)/2;

    if(v[m] < x)
      l = m + 1;
    else
      r = m;
  }
  if(v[l] == x)
    return l;
  return -1;
}
```

**NB<sub>1</sub>**: questo codice non è stato testato - ricompensa speciale a chi dovesse eventualmente trovarci un errore e correggerlo :)
Trovate una versione testata qui: [repl.it scritto a lezione](https://repl.it/@FilippoSoldati/binarysearch#main.cpp).

**NB<sub>2</sub>**: nella firma della funzione troviamo un simbolo di reference nel vector (`&`) - questo serve per evitare di copiare il vector ogni volta che la funzione viene chiamata. Quando parleremo meglio delle funzioni avremo modo di parlarne meglio, per ora vi basta sapere che se il `vector` fosse stato "dichiarato" senza, ad ogni chiamata della funzione `find_in_sorted_vector` ne sarebbe stata creata una copia (con costo **O(N)**!).

### Soluzione ois_ruspa

Ora che conosciamo la *ricerca binaria*, possiamo adattarla al nostro caso: noi vorremmo trovare la coordinata della ruspa nel vettore dei muri, ma sappiamo già che questo valore tuttavia non esiste, ci viene garantito nelle assunzioni del problema.

Quello che però possiamo trovare, è il primo muro a sinistra della ruspa, ovvero l'ultimo valore del vettore ad essere minore di **x** - se effettuiamo la ricerca binaria effettivamente, anche se non troviamo il valore **x** ne troviamo comunque un "*intorno*".

Ci basta un po' di accortezza nel modificare leggermente le condizioni per cui modifichiamo l'intervallo **[L, R]** - infatti se troviamo un valore **<** non possiamo più scartarlo a priori - potrebbe essere proprio quello l'ultimo tra i valori minori!

```cpp
if(v[m] < x)
  l = m;
```
D'altro canto, dobbiamo invece sempre scartare i valori **>** - noi stiamo cercando il più grande valore ad essere **< X**, ma questo non può di certo essere maggiore!

```cpp
else
  r = m - 1;
```

Questo però ci lascia un problema - quando calcoliamo il punto medio **m** usando la divisione per **2**, stiamo arrotondando per difetto. Questo significa che quando rimangono solamente **2** valori, ad **m** viene direttamente assegnato il valore di **l** - quindi se succede che **v[l] < x**, in sostanza ad **l** verrà riassegnato il suo stesso valore, causandso un loop infinito della nostra ricerca - poiché verrà poi ripetuta senza mai variare né **l** che **r**.

Questo problema è facilmente risolvibile però: ci basterà questa volta scegliere di arrotondare per eccesso invece che per difetto, cambiando in questo modo il calcolo di **m**:

```cpp
int m = (l + r + 1) / 2;
```

Sommare **1** prima della divisione, fa sì che solo i valori dispari aumentino di **1** - quelli che effettivamente avremmo voluto arrotondare per eccesso.

Fa attenzione però, arrotondare per eccesso non va sempre bene - solo quando, come in questo caso, nello spostare **l** non ci si sposta da **m**.
La regola è quindi di arrotondare verso la *"posizione"* più conveniente: se è il lato destro quello che si accorcia di più, arrotondiamo per eccesso, se è il lato sinistro quello che si allontana da **m** di **1**, arrotondiamo per difetto.

Questa regola prendetela un po' con le pinze - possono esistere casi leggermente diversi, ed è quindi sempre una buona abitudine controllare a mano che il proprio codice funzioni sempre fino alla fine, anche quando rimangono solamente **2** elementi da controllare.

Trovate il codice che implementa la ricerca binaria sia [qui su github]() che su [repl](https://repl.it/@FilippoSoldati/ruspabinary#main.cpp).


## Esercizi da svolgere

* **[ois_negozi](https://training.olinfo.it/#/task/ois_ruspa/submissions)**
  * abbiamo già visto una soluzoine da **100** punti per *Shopping Stress*, ma riesci a modificarla usando la ricerca binaria per renderla ancora migliore?
* **[ois_annoluce](https://training.olinfo.it/#/task/ois_annoluce/submissions)**
  * problema in cui dobbiamo rispondere ad altre query simili usando la ricerca binaria, consigliato!
* **[fri_terrazzamenti](https://training.olinfo.it/#/task/fri_terrazzamenti/submissions)**
  * problema piuttosto difficile, proposto per chi volesse provare un esercizio più difficile del solito - ottenere anche solo qualche punto è già un buon punto di partenza!
  * una delle soluzioni da **100** punti richiede un utilizzo molto furbo della ricerca binaria - è un problema interessante, ma vi consiglio di non spenderci troppo tempo se vedete che siete a corto di idee! 

## C++: Sorting

Oggi abbiamo parlato di *ricerca binaria*, ma come facciamo ad utilizzarla se non sappiamo come ordinare il nostro vettore?

Fortunatamente, anche qui la *Standard Library* viene in nostro soccorso con la funzione `sort`, della libreria `algorithm` - con una complessità di **O(NlogN)**, ci permette di ordinare in ordine crescente i nostri `vector`:

```cpp
vector<int> v(n);

// [...]

sort(v.begin(), v.end());
```

La funzione ci chiede due parametri: l'inizio del `vector`, che otteniamo con il metodo `.begin()`, e la sua fine - `v.end()`.

Possiamo anche utilizzarlo con gli array:

```cpp
int v[n];
// [...]
sort(v, v + n);
```

Questa volta, dovremo fornire due puntatori - uno all'inizio dell'array e l'altro alla fine - che otteniamo spostandoci in avanti di `n` dal puntatore di partenza.

Possiamo anche sortare tipi diversi dagli interi, purché siano di un tipo che può essere confrontato direttamente con l'operatore `<`:

```cpp
vector<double> x;
sort(x.begin(), x.end());

vector<string> s;
sort(s.begin(), s.end());

// anche due vector possono essere confrontati tra loro
vector<vector<int>> z;
sort(z.begin(), z.end());
```

Se vogliamo sortare in ordine decrescente, abbiamo più opzioni:

```cpp
// sortiamo usando gli iteratori inversi: Rbegin e Rend
sort(v.rbegin(), v.rend());

// sortiamo e poi invertiamo l'array
sort(v.begin(), v.end());
reverse(v.begin(), v.end());

// sortiamo con l'operatore > invece che <
sort(v.begin(), v.end(), greater<int>());
```

## C++: Pairs

Più avanti, vedremo anche come creare i nostri tipi di dato personalizzati - se però ci serve dichiarare una variabile che abbia due valori (anche di tipo diverso tra loro), possiamo utilizzare la classe `pair<T, U>` della standard library:

```cpp
pair<int, double> x;
x.first = 3;
x.second = 3.5;
```

Nell'esempio, abbiamo dichiarato una variabile di nome `x` che contiene due valori:
- il primo di tipo intero, accessibile all'attributo `.first`
- il secondo di tipo double, accessibile invece con `.second`

I `pair` creati in questo modo sono dei tipi a tutti gli effetti, e possono essere usati come ogni altro tipo:

```cpp
// possiamo avere un pair di pair
pair<pair<int,int>, pair<int, int>> piiii;

// possiamo avere un vettore di pair
vector<pair<int, int>> vpii;

// possiamo avere un pair di vector
pair<vector<int>, vector<double>> pvivd;
```

Possiamo inoltre inizializzare un `pair` durante la sua dichiarazione usando le parentesi graffe:

```cpp
pair<int, int> p = {3, 5};
p.first; // 3
p.second; // 5

pair<pair<int, double>, string> q = {{3, 0.14}, "pi"};
```

Due ```pair``` dello stesso tipo possono essere anche confrontati, e di conseguenza un ```vector<pair>``` può essere sortato:

```cpp
pair<int, int> x = {3, 5};
pair<int, int> y = {3, 7};
y > x; // true, perché first è uguale ma second è maggiore in y


vector<pair<int, int>> v;
sort(v.begin(), v.end());
```