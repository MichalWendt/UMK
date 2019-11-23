//Michal Wendt - Skladowe spojnosci i najkrotsze drogi
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

int numerowanie(vector<int> odwiedzone, int n)                                        //numerowanie odwiedzonych wierzcholkow
{
    for(int i = 0; i < n; ++i)
    {
        if(odwiedzone[i] == 0)
        {
            return i;
        }
    }
    return -1 ;
}

bool istnieje(vector<int> *spojnosci, vector<int> odwiedzone, int poczatek, int koniec)         //sprawdzanie czy droga istnieje
{
    int pom = odwiedzone[poczatek];
    for(int i = 0; i < spojnosci[pom].size(); ++i)
    {
        if(spojnosci[pom][i] == koniec)
        {
            return true;
        }
    }
    return false;
}

bool zaznaczony(vector<int> odwiedzone, int n)                                     //sprawdzanie czy wierzcholek byl juz odwiedzany
{
    for(int i = 0; i < n; ++i)
    {
        if(odwiedzone[i] == 0)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int n, m;
    int a, b;                           //zmienne pomocnicze
    int k=1;
    int wierzcholek;
    int pierwszy, ostatni;              //zmienne potrzebne do ustalenia drogi
    int spojny = 0;
    int maxspojnosc = 0;                //zmienne potrzebne do ustalenia spojnosci
    int c = 0;
    cout << "Ile wierzchokow? ";        //pobieranie ilosci wierzcholkow i polaczen
    cin >> n;
    cout << "Ile drog? ";
    cin >> m;
    vector <int> odwiedzone(n);         //odiwedzone wierzcholki
    vector <int> drogi[m];              //drogi w grafie
    queue <int> kolejka;                      //wierzcholki
    int sciezka[n];

    for(int i = 0; i < m; i++)          //wpisywanie drog w grafie
    {
        cout << "Prosze podac [" << i+1 << "] droge ";
        cin >> a >> b;
        drogi[a].push_back(b);
        drogi[b].push_back(a);
    }

    cout << "Z ktorego wierzcholka zaczynamy? ";        //wierzcholek poczatkowy
    cin >> pierwszy;
    cout << "Do ktorego wierzcholka chcemy dojsc? ";    //wierzcholek koncowy
    cin >> ostatni;

    for(int i=0; i< n; i++)                             //ustawianie tablicy naszej sciezki
    {
       sciezka[i]=-1;
    }

    kolejka.push(pierwszy);                   //wpisanie pierwszego wierzcholka do kolejki
    wierzcholek=pierwszy;
    odwiedzone[wierzcholek]=1;          //ustawienie pierwszego wierzcholka na odwiedzony

    while(!kolejka.empty())
    {
        wierzcholek=kolejka.front();
        kolejka.pop();
        for(int i = 0; i < drogi[wierzcholek].size(); ++i)
        {
            if(odwiedzone[drogi[wierzcholek][i]] == 0)
            {
              kolejka.push(drogi[wierzcholek][i]);
              odwiedzone[drogi[wierzcholek][i]]=1;
              sciezka[drogi[wierzcholek][i]]=wierzcholek;
            }
        }
    }

    while(zaznaczony(odwiedzone,n) == false)        //uzupelnianie tablicy spojnych wierzcholkow
    {
        wierzcholek=numerowanie(odwiedzone,n);
        kolejka.push(wierzcholek);
        k++;
        odwiedzone[wierzcholek] = k;
        while(!kolejka.empty())
        {
            wierzcholek = kolejka.front();
            kolejka.pop();
            for(int i = 0; i < drogi[wierzcholek].size(); ++i)
            {
                if(odwiedzone[drogi[wierzcholek][i]] == 0)
                {
                    kolejka.push(drogi[wierzcholek][i]);
                    odwiedzone[drogi[wierzcholek][i]] = k;
                    sciezka[drogi[wierzcholek][i]] = wierzcholek;
                }
            }
        }
    }

    for(int i = 0; i < n; i++)
    {
        spojny = max(odwiedzone[i],spojny);             //szukanie wszystkich spojnosci
    }
    vector<int> spojnosci[spojny+1];

    cout << endl << "Ilosc spojnych skladowych to " << spojny << endl;     //wypisywanie ilosci skladowych
    cout << "Czyli " << endl;
    for(int i = 0; i < n; i++)
    {
       spojnosci[odwiedzone[i]].push_back(i);
    }

    for(int i = 1; i <= spojny; i++)
    {
        for(int j = 0; j < spojnosci[i].size(); j++)
        {
            cout << spojnosci[i][j] << " ";              //wypisywanie skladowych
        }
        int pom = spojnosci[i].size();
        maxspojnosc = max(maxspojnosc,pom);             //obliczanie maksymalnej spojnosci
        cout << endl;
    }

    cout << endl << "Najliczniejsza skladowa spojnosci liczy " << maxspojnosc << " wierzcholkow" << endl << endl;      //wypisywanie najliczniejszej spojnosci

    if(istnieje(spojnosci, odwiedzone, pierwszy, ostatni) == true)                              //Znajdowanie najkrotszej drogi
    {
        int najkrotsza = 0;
        int koniec = ostatni;
        cout << "Droga pomiedzy wierzcholkami " << pierwszy << " oraz " << ostatni << " to" << endl;
        cout << pierwszy << " -> ";
        while(sciezka[sciezka[koniec]] != -1)                                                               //wypisywanie najkrotszej drogi
        {
            najkrotsza++;
            cout << sciezka[koniec] << " -> ";
            koniec = sciezka[koniec];
        }
        cout << ostatni << endl;
        cout << "Dlugosc drogi pomiedzy " << pierwszy << " a " << ostatni << " to " << najkrotsza+1 << " krawedzi" << endl;
        cout << "Czyli " << najkrotsza << " wierzcholkow" <<endl;      //wypisywanie dlugosci najkrotszej drogi
    }
    else
    {
         cout<<"Brak drogi pomiedzy tymi wierzcholkami"<<endl;          //wypisywanie informacji o braku drogi
    }

    return 0;
}
