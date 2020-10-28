# Lezione 1
## Indice
* [Esercizi assegnati](#esercizi-assegnati)
    * [ois_streetlights](#ois_streetlights)
    * [easy3](#easy3)
* [Task: ois_negozi](#introduzione-al-corso)
    * [Soluzione *"naive"* - 50/100](#soluzione-naive)
        * [Velocizzare input/output: 80/100](#velocizzare-inputoutput)
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

## Task: ois_negozi

Verrà inserito a breve!