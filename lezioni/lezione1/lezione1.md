# Lezione 1
## Indice
* [Introduzione al corso](#introduzione-al-corso)
* [Sondaggio preparazione](#sondaggio-preparazione)
* [Ambiente di sviluppo](#ambiente-di-sviluppo)
* [Piattaforma di allenamento](#piattaforma-di-allenamento)
* [C++: Standard Library](#c-standard-library)
* [C++: I/O da file](#c-io-da-file)
* [C++: Vector](#c-vector)
* [Task: easy1](#task-easy1)
* [Task: ois_streetlights](#task-ois-streetlights)
* [Esercizi da svolgere](#esercizi-da-svolgere)

## Introduzione al corso

L'obiettivo di questo corso è quello di introdurre gli studenti al *competitive programming*, in modo da fornire le competenze necessarie per partecipare alle Olimpiadi di Informatica - sia individuali che a squadre - ma anche per iniziare a migliorare le proprie competenze in algoritmica e problem solving.

Il corso coprirà diversi argomenti, tra cui:
- Complessità computazionale
- Algoritmi greedy
- Teoria dei grafi
- Standard Library C++
- Programmazione dinamica
- Algoritmi di sorting
- Strutture dati "*avanzate*"

Verranno utilizzati principalmente problemi provenienti dal sito **[training.olinfo.it](training.olinfo.it)**.

## Sondaggio preparazione

Per chi non l'avesse ancora fatto, potete rispondere [qui](https://forms.gle/5BmoguKVHrq5qS3F7) ad alcune domande sulla vostra preparazione, in modo da agevolere lo svolgimento del corso:
- [Check conoscenze](https://forms.gle/5BmoguKVHrq5qS3F7)


## Ambiente di sviluppo

Non è richiesto l'utilizzo di uno specifico ambiente di sviluppo / editor di testo per seguire il corso, l'importante è avere a disposizione un compilatore che supporti almeno *C++11*.

Il nostro consiglio per chi non fosse già dotato di compilatore/editor, è quello di utilizzare il sito **[repl.it](repl.it)**. L'ambiente di sviluppo offerto è molto completo, si possono creare file per l'input, ci sono diverse opzioni di condivisione e c'è anche modo di utilizzare il terminale, se siete pratici.

Altrimenti, un mio consiglio personale è di utilizzare *Visual Studio Code*.

## Piattaforma di allenamento

Sul sito training.olinfo.it, troverete una vasta collezione di problemi - utilizzeremo principalmente questi come esempi e esercizi durante il corso. 
Sul sito è possibile sottomettere soluzioni in **C**, **C++** e **Pascal** - ma noi utilizzeremo solo **C++**.

Il sito assegna automaticamente un grado di difficoltà a ciascun problema, in base al punteggio ottenuto dagli utenti che hanno già provato a risolverli. Inoltre, i problemi sono catalogati per categoria e per evento.

## C++: Standard Library

Uno dei vantaggi principali dell'utilizzo del **C++** è il poter utilizzare le *classi* e *funzioni* contenute nella sua *"standard library"*, spesso riferita come *STL* [*[link per i più pignoli](https://stackoverflow.com/questions/5205491/whats-the-difference-between-stl-and-c-standard-library#:~:text=ISO%2014882%20C%2B%2B%20Standard%3A&text=STL%20is%20a%20library%20originally,independent%20of%20the%20C%2B%2B%20standard.&text=But%20of%20course%20the%20C%2B%2B,used%20by%20the%20standards%20documents)*].

Per utilizzare una libreria, sarà necessario includerla con la relativa istruzione `#include`:

```cpp
#include <iostream>
```

Per semplicità, nelle soluzioni proposte includeremo sempre tutte la librerie, in modo da evitare di doverci ricordare dove è inclusa ciascuna funzione/classe e ridurre la quantità di codice da scrivere:

```cpp
#include <bits/stdc++.h>
```

Per evitare di doverlo specificare ogni volta che utilizziamo qualcosa di proveniente dalla libreria standard, specifichiamo anche l'utilizzo del suo namespace:

```cpp
using namespace std;
```

## C++: I/O da file

In **C++**, si utilizzano gli *stream* `cin` e `cout` rispettivamente per input e output da console:

```cpp
// Sintassi approsimativa
cin >> variabile_1 >> variabile_2 >> [...] >> variabile_N;
cout << espressione_1 << espressione_2 << [...] << espressione_N;

// Esempio
int n;
cin >> n;

char a;
double d;
cin >> a >> d;

cout << "d * n: " << d * n << endl;
cout << a+1;
```

Possiamo ottenere degli stream con funzionamento identico, ma che lavorano con i file utilizzando le classi `ifstream` e `ofstream` contenute nella libreria `fstream`:

```cpp
ifstream fin("input.txt");
ofstream fout("output.txt");

int n;
fin >> n;
fout << n;
```

Mettendo input/output da file insieme a quello visto in precedenza, otteniamo questo *template* che possiamo utilizzare come base quando iniziamo a risolvere un problema su *training.olinfo.it**: 

```cpp
#include <bits/stdc++.h>
using namespace std;

ifstream fin("input.txt");
ofstream fout("output.txt");

int main() {

}
```

**non tutti i problemi richiedono input da file, ma la maggiorparte sì* 

## C++: Vector

Una delle classi dello *standard* che più utilizzero è senza dubbio `vector`, un'alternativa ai più semplici `array`, il cui vantaggio principale è la possibilità di aumentarne la dimensione dinamicamente durante l'esecuzione del programma.

```cpp
#include <vector>
```

Per dichiarare un `vector`, è necessario specificare il *tipo* delle variabili che andrà a contenere:

```cpp
// Vettore di interi
vector<int> v;

// Vettore di stringhe
vector<string> parole;

// Vettore di vettori di interi
vector<vector<int>> vettori;
```

Quando viene inizializzato, un `vector` sarà vuoto.
Per aggiungere un elemento in fondo, possiamo utilizzare il metodo `.push_back(value)`:

```cpp
vector<int> v;

v.push_back(3);
v.push_back(5);
```

Possiamo utilizzare un `vector` accedendo ai suoi indici come se fosse un *array*, purché ci limitiamo ad indici validi (compresi tra *0* e *la sua dimensione - 1*):

```cpp
vector<int> v;

v.push_back(3);
fout << v[0]; // stampa 3
fin >> v[0]; // salva in v[0] il valore letto

v.push_back(2);
v[1] = v[2]; // istruzione non valida, v[2] non esiste!
```

È possibile dichiarare `vector` pre inizializzati, specificandone la dimensione utilizzando il costruttore durante la dichiarazione.
In questo caso, tutti i valori saranno inizializzati al valore di *default* del tipo scelto (`0` per gli interi, stringa vuota per le stringhe...); a meno che non venga specificato diversamente:

```cpp
// Crea un vector di 5 elementi, tutti '0'
vector<int> v(5);

// Crea un vector di 3 elementi, tutti '4'
vector<int> quattro(3, 4);
```

Siccome la dimensione di un vector può cambiare a *run-time*, è possibile conoscerla usando il metodo `.size()`:

```cpp
vector<int> v(4, 5);
v.push_back(3);

fout << v.size(); // stampa '5' (4 + 1)
```

Oltre che aggiungere valori al fondo del `vector`, è anche possibile rimuoverne - sempre dal fondo:

```cpp
vector<int> v(3);
v.pop_back();
fout << v.size(); // stampa '2'
```

## Task: easy1

[easy1](https://training.olinfo.it/#/task/easy1/statement) è il problema introduttivo della piattaforma, quello che tutti dovrebbero svolgere per primo :)

Il problema ci chiede di trovare l'intero più grande all'interno di una lista di **N** interi - dopo aver letto l'input in un `vector`, possiamo risolverlo con un ciclo `for`, tenendo traccia man mano dell'elemento più grande:

```cpp
int maxi = -1000; // valore minimo che può assumere un intero nel problema
for(int i = 0; i < n; i++)
    if(v[i] > maxi)
        maxi = v[i];
```

Qui nella repo trovate due possibili implementazioni:
- [quella vista a lezione](easy1/easy1_lezione.cpp)
- [variante con funzioni della STL](easy1/easy1_variante_commentata.cpp)

## Task: ois_streetlights

Il secondo problema che abbiamo svolto durante la lezione è [Antique Streetlights (streetlights)](https://training.olinfo.it/#/task/ois_streetlights/statement):
ci viene data una lista di interi che rappresentano una sequenza di **N** lampioni:
- **1** indica un lampione acceso,
- **0** un lampione spento.

Ci viene chiesto di calcolare il minor numero di lampioni da accendere per far sì che per ciascun segmento di **M** lampioni ce ne siano almeno **K** accesi.

Ci accorgiamo che fissato un segmento di **M** lampioni, se sappiamo che i segmenti precedenti sono già *ok* (ne hanno già almeno *K* accesi), allora se serve accendere dei lampioni la scelta migliore è accendere quelli più a destra possibile (ovviamente, tra quelli spenti).

Ne segue che una possibile soluzione è iterare su tutti i segmenti partendo dal primo, contare i lampioni da accendere e poi accenderli, cercandoli da destra:

```cpp
// provo ogni segmento lungo M, fissando l'inizio i
for(int i = 0; i + m - 1 < n; i++) {
    // conto le luci accese
    int accese = 0;
    for(int j = i; j < i + m; j++)
        accese += v[j];
    // finché non ne ho accese abbastanza, cerco lanterne spente da accendere
    for(int j = i + m - 1; j >= i && accese < k; j--) {
        if(v[j] == 0) {
            v[j] = 1;
            accese++;
            ans++;
        }
    }
}
```

Il problema di [questa soluzione (70 punti)](ois_streetlights/ois_streetlights_70.cpp) è il tempo utilizzato, avendo la soluzione una complessità computazione di **O(N*M)** - scopriremo più avanti esattamente cose vuol dire, quello che ci basta notare è che non possiamo ripetere centomila volte (**N-M**) un ciclo che già di per sé conta fino a 100 mila operazioni (**M**). 

Per velocizzare la nostra soluzione, ci serve velocizzare il metodo con cui contiamo i lampioni accesi in un intervallo: una volta contato il primo, per calcolare quante sono accese nel secondo non ci serve contare tutto da capo, ma ci basta sottrarre il lampione che abbiamo escluso (**i-1**) e aggiungere l'ultimo che abbiamo aggiunto (**i+m-1**).

La soluzione da 100 punti è disponibile sia [qui come file](ois_streetlights/ois_streetlights.cpp), ma anche [direttamente su repl.](https://repl.it/@FilippoSoldati/streetlights#main.cpp)

Una soluzione leggermente più furba, che sfrutta alcune osservazioni per evitare un secondo ciclo (che in realtà non viene davvero ripetuto, se non una volta!) è [consultabile qui](ois_streetlights/ois_streetlights_furba.cpp).


## Esercizi da svolgere

Due esercizi introduttivi che potrebbero essere un bell'allenamento per la prossima lezione sono i due **easy** successivi al primo:
- [easy2](https://training.olinfo.it/#/task/easy2/statement)
- [easy3](https://training.olinfo.it/#/task/easy3/statement)

Puoi trovare alcune soluzioni dentro la cartella `esercizi`.