#include <iostream>

using namespace std;

// Typy danych

struct slistEl
{
  slistEl * next;
  int v,w;                        // numer wêz³a docelowego i waga krawêdzi
};

const int MAXINT = 2147483647;

int main()
{
  int i,j,m,n,v,u,w,x,y,sptr,*d,*p,*S;
  bool *QS;                       // Zbiory Q i S
  slistEl **graf;                 // Tablica list s¹siedztwa
  slistEl *pw,*rw;

  cin >> v >> n >> m;             // Wêze³ startowy, liczba wierzcho³ków i krawêdzi

  // Tworzymy tablice dynamiczne

  d = new int [n];                // Tablica kosztów dojœcia
  p = new int [n];                // Tablica poprzedników
  QS = new bool [n];              // Zbiory Q i S
  graf = new slistEl * [n];       // Tablica list s¹siedztwa
  S = new int [n];                // Stos
  sptr = 0;                       // WskaŸnik stosu

  // Inicjujemy tablice dynamiczne

  for(i = 0; i < n; i++)
  {
    d[i] = MAXINT;
    p[i] = -1;
    QS[i] = false;
    graf[i] = NULL;
  }

  // Odczytujemy dane wejœciowe

  for(i = 0; i < m; i++)
  {
    cin >> x >> y >> w;           // Odczytujemy krawêdŸ z wag¹
    pw = new slistEl;             // Tworzymy element listy s¹siedztwa
    pw->v = y;                    // Wierzcho³ek docelowy krawêdzi
    pw->w = w;                    // Waga krawêdzi
    pw->next = graf[x];
    graf[x] = pw;                 // Element do³¹czamy do listy
  }

  cout << endl;

  d[v] = 0;                       // Koszt dojœcia v jest zerowy

  // Wyznaczamy œcie¿ki

  for(i = 0; i < n; i++)
  {
    // Szukamy wierzcho³ka w Q o najmniejszym koszcie d

    for(j = 0; QS[j]; j++);
    for(u = j++; j < n; j++)
      if(!QS[j] && (d[j] < d[u])) u = j;

    // Znaleziony wierzcho³ek przenosimy do S

    QS[u] = true;

    // Modyfikujemy odpowiednio wszystkich s¹siadów u, którzy s¹ w Q

    for(pw = graf[u]; pw; pw = pw->next)
      if(!QS[pw->v] && (d[pw->v] > d[u] + pw->w))
      {
        d[pw->v] = d[u] + pw->w;
        p[pw->v] = u;
      }
  }

  // Gotowe, wyœwietlamy wyniki

  for(i = 0; i < n; i++)
  {
    cout << i << ": ";

    // Œcie¿kê przechodzimy od koñca ku pocz¹tkowi,
    // Zapisuj¹c na stosie kolejne wierzcho³ki

    for(j = i; j > -1; j = p[j]) S[sptr++] = j;

    // Wyœwietlamy œcie¿kê, pobieraj¹c wierzcho³ki ze stosu

    while(sptr) cout << S[--sptr] << " ";

    // Na koñcu œcie¿ki wypisujemy jej koszt

    cout << "koszt: " << d[i] << endl;
  }

  // Usuwamy tablice dynamiczne

  delete [] d;
  delete [] p;
  delete [] QS;
  delete [] S;

  for(i = 0; i < n; i++)
  {
    pw = graf[i];
    while(pw)
    {
      rw = pw;
      pw = pw->next;
      delete rw;
    }
  }

  delete [] graf;

  return 0;
}
