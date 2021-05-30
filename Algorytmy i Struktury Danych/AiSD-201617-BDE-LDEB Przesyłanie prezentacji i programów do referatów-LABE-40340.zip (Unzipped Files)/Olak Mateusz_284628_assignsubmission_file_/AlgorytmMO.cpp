#include <iostream>

using namespace std;

const int MAXINT = 2147483647;    // "plus nieskonczonosc"

int main()
{
  int ** d;                       // Macierz minimalnych kosztów dojscia
  int n,m,x,y,w;

  cin >> n >> m;                  // Czytamy liczbe wierzcholków oraz krawedzi

  d = new int * [n];              // Tworzymy dynamiczna macierz d
  for(int i = 0; i < n; i++)
  {
    d[i] = new int [n];           // Tworzymy wiersz macierzy
    for(int j = 0; j < n; j++)
      d[i][j] = MAXINT;           // Wiersz wypelniamy +nieskonczonosc
    d[i][i] = 0;                  // na przek¹tnej wpisujemy 0
  }

  for(int i = 0; i < m; i++)
  {
    cin >> x >> y >> w;           // Czytamy definicje krawedzi
    d[x][y] = w;                  // Wage krawedzi umieszczamy w macierzy d
  }

  // Algorytm Floyda-Warshalla

  for(int k = 0; k < n; k++)
    for(int i = 0; i < n; i++)
      for(int j = 0; j < n; j++)
      {
        if((d[i][k] == MAXINT) || (d[k][j] == MAXINT)) continue;
        w = d[i][k] + d[k][j];
        if(d[i][j] > w) d[i][j] = w;
      }

  cout<<endl<<"Macierz wynikow:"<<endl;

  for(int i = 0; i < n; i++)
  {
    for(int j = 0; j < n; j++)
    {
        cout<<d[i][j]<<" ";
    }
    cout<<endl;
  }

  cout << endl<<"Koszty dojsc:"<<endl;

  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
    {
      cout << "d[" << i << "," << j << "] = ";
      if(d[i][j] == MAXINT) cout << "Brak sciezki:";
      else                  cout << d[i][j];
      cout << endl;
    }
  for(int i = 0; i < n; i++) delete [] d[i];
  delete [] d;

  return 0;
}
