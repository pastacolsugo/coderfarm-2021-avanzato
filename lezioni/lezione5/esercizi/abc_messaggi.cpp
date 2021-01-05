#include <bits/stdc++.h>
using namespace std;
ifstream fin("input.txt");
ofstream fout("output.txt");

int main() {
  // ottimizzazione input/output
  fin.tie(0);
  fin.sync_with_stdio(0);

  // per risolvere il problema, ci appoggiamo ad una mappa,
  // in cui memorizziamo per ciascun utente la lista
  // dei messaggi da lui inviati;
  // e ad un'ulteriore mappa, in cui invece memorizziamo
  // la lista dei messaggi ricevuti

  int n, r;
  fin >> n >> r;

  map<string, vector<string>> inviati, ricevuti;

  for(int i = 0; i < n; i++) {
    string a, b; 
    fin >> a >> b;
    // aggiungo b agli inviati da a
    inviati[a].push_back(b);
    // aggiungo a ai ricevuti di b
    ricevuti[b].push_back(a);
  }

  for(int i = 0; i < r; i++) {
    string persona, comando;
    fin >> persona >> comando;
    // se devo stampare gli inviati
    if(comando == "INVIATI") {
      // stampo prima la dimensione
      fout << inviati[persona].size() << ' ';
      // poi tutti i destinatari
      for(string x : inviati[persona])
        fout << x << ' ';
      fout << '\n'; // vado a capo
    }
    // se devo stampare i ricevuti
    else {
      // come sopra
      fout << ricevuti[persona].size() << ' ';
      for(string x : ricevuti[persona])
        fout << x << ' ';
      fout << '\n';
    }
  }
  
}