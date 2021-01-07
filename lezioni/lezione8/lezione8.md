# Lezione 8
## Indice
* [BFS: Breadth-First Search](#bfs-breadth-first-search)
* [Task: ois_monete](#task-ois_monete)
* [Distanza in archi](#distanza-in-archi)
* [SPFA: Shortest Path Faster Algorithm](#spfa-shortest-path-faster-algorithm)

## BFS: Breadth-First Search
L'algoritmo di questa lezione, la **Breadth-First Search** (conosciuto come "visita in ampiezza" in italiano), è indubbiamente lo strumento più versatile e utile per affrontare con la giusta impostazione la maggior parte dei problemi di grafi - questa lezione è probabilmente una delle più utili tra quelle viste fin'ora, e vi consiglio di rileggerla anche se eravate presenti durante la lezione online che abbiamo fatto insieme - se invece vi siete già portati avanti, e avete anche risolto gli esercizi assegnati a fine lezione, l'argomento che potete approfondire è invece quello della *DFS* (*Depth-first Search*), che vedremo nel corso solo più avanti, quando apparirà come subroutine di altri algoritmi. 

NB: tutti i riferimenti che vengono fatti in questa lezione al concetto di componente connessa, sono validi solo per i grafi non-orientati. Nei grafi orientati, si parla invece di "componenti fortemente connesse", e siccome trattarle richiede algoritmi leggermente più complicati, sono affrontate molto raramente nei problemi di competitive programming; quindi non verranno trattate durante il corso.

Nella scorsa lezione, abbiamo visto come utilizzando una lista di adiacenza fosse possibile spostarsi nel grafo di arco in arco, in base alle regole fornite dal problema. Spesso però, potrebbe capitarci di non sapere esattamente come doverci muovere da ciascun nodo e potrebbe essere necessario dover fare dell'"esplorazione", prima di poter risolvere il problema.

Prendiamo come esempio un grafo diverso dall'ultima volta, in cui i nodi sono gli studenti di una scuola superiore e gli archi sono i rapporti di amicizia.
Due studenti possono a loro volta conoscersi/diventare amici se un loro amico in comune li fa incontrare.
Vogliamo sapere se è possibile che un certo studente **X** diventi amico dello studente **Y**, dopo una serie di incontri organizzati tra amici in comune.

Prendiamo questa istanza come esempio:

<img>

È possibile per lo studente X diventare amico dello studente Y?
La risposta è sì, perché tramite lo studente Z, X può conoscere Q, che poi può infine presentargli lo studente Y.

<img>

Quello che stiamo facendo, è equivalente al cercare un percorso nel grafo che connetta il nodo X al nodo Y.

Se l'amicizia è diretta, la soluzione è semplice da trovare: ci basterà iterare su tutti gli amici di X, per vedere se Y è uno di questi.

Se tra X e Y invece c'è esattamente un'altra persona, ci basterà estendere un po' la ricerca : anziché guardare gli amici di X, guarderemo agli amici degli amici di X!

Questo modo di pensare però non si estende bene per gli amici più distanti, e già guardando gli amici di amici ci accorgiamo che c'è un sacco di "overlap": ad esempio, T è amico sia di X, Z e W, e in questo modo lo stiamo controllando già 3 volte. Controllare i suoi amici è necessario per risolvere il problema, però vogliamo farlo una volta sola, dato che la struttura del grafo rimane sempre la stessa.

Ci rendiamo conto del fatto che è quindi importante visitare ciascun nodo una volta sola, il nostro algoritmo potrebbe gestire quindi questa cosa appoggiandosi a un vettore di booleani.

L'altra cosa che abbiamo identificato è che se ci espandiamo prima nei vicini e del nodo di partenza, e poi nei rispettivi vicini, prima o poi riusciremo a raggiungere tutti i nodi raggiungibili - ovvero quelli che fanno parte della stessa "componente connessa".

<img> 
*Esempio di grafo con 3 diverse "componenti connesse"*

Vogliamo trovare un modo per poterci espandere nei vicini del nodo di partenza, uno alla volta, allontandoci man mano dal nodo di partenza, senza visitare due volte lo stesso nodo.

Per farlo, ci viene in aiuto la coda, una struttura dati per gestire valori in modo **"FIFO"** (**First In, First Out**).

Inizialmente, nella nostra coda ci sarà il nodo di partenza, che quindi verrà segnato come visitato.
Continuiamo a processare i nodi in coda, fino a che la coda non sarà del tutto svuotata.
Prendiamo il nodo in testa alla coda, e lo rimuoviamo. Usando la nostra lista di adiacenza, andiamo a vedere quali sono i suoi vicini - se ne troviamo qualcuno che ancora non è stato segnato come visitato, lo segniamo come visitato e lo aggiungiamo alla coda, dato che vogliamo eventualmente aggiungere anche i suoi vicini.

Al termine di questo algoritmo, che prende appunto il nome di **BFS**, avremo segnato come visitati tutti i nodi che sono raggiungibili dal nodo di partenza, quindi tutti i nodi che si trovano nella sua componente connessa.

Il nostro vettore di booleani, dopo aver effettuato la *BFS* dal nodo X, sarà così:

<img>

Siccome il nodo **Y** è segnato come visitato, possiamo rispondere *"Sì"* alla domanda che ci eravamo posti all'inizio: è possibile far conoscere gli studenti X e Y.

Il codice della nostra **BFS** può essere implementato in questo modo:

```cpp
```

### Task: ois_monete

In questo problema, ci viene dato un grafo dove i nodi sono delle piattaforme numerate e collegate tra loro, ciascuna contenente delle monete.
Ci viene chiesto di contare quante monete è possibile raccogliere, partendo dalla piattaforma numero X.

Per farlo, ci basterà visitare la componente connessa di cui X fa parte, cosa che possiamo fare appunto con la BFS - una volta che conosciamo i nodi che fanno parte della componente connessa ci basterà sommare le monete che troviamo su ciascuna piattaforma. Questa cosa si può fare sia man mano che si svolge la BFS, sia al termine, iterando sul vettore di booleani.

```cpp
```

### Distanza in archi

(variante problema con numero di presentazioni)

Un'altra delle proprietà importanti della BFS riguarda l'ordine con cui vengono visitati i nodi: (spiegazione)

(rielaborazione + intuizioni per dimostrazione, poco formale)

(come modificare algoritmo per fare questa cosa)

(codice)

## SPFA: Shortest Path Faster Algorithm

(problema delle strade)

(ricollegamento al problema visto per distanza in archi - con pesi tutti a 1)

(cosa succede se usiamo BFS per distanze)

(cosa possiamo fare per evitare il problema)

(dimostrazione poco formale del funzionamento di questa idea)

(codice SPFA)

(commento su SPFA + accenno all'esistenza di Dijkstra)

(accenno all'esistenza di 0-1 BFS ???)

## Esercizi