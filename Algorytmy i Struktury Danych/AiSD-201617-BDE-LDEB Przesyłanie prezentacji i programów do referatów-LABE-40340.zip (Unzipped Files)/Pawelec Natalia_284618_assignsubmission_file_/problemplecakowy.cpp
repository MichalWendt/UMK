#include <iostream>

using namespace std;
// jednokrotne wykorzystanie danego przedmiotu, algorytm zachlanny

void zamienint(int &a, int &b)
{
    int pom = a;
    a = b;
    b = pom;
}

void zamienfloat(float &a, float &b)
{
    float pom = a;
    a = b;
    b = pom;
}

int main()
{
    int w; // pojemnosc plecaka
    int n; // ilosc dostepnych przedmiotow;
    int pom1 = 0;
    int pom2 = 0; // zmienne pomocnicza

    cout << "Podaj pojemnosc plecaka (kg): ";
    cin >> w;
    cout << "Podaj ilosc dostepnych przedmiotow: ";
    cin >> n;

    int waga[n];
    int wart[n]; // tablice zawierajace informacje o wadze i wartosci danych przedmiotow
    float sred[n]; // tablica danych wartosc/waga
    int k[n]; // tablica przechowujaca informacje o tym, ktore przedmioty zostaly wlozone do plecaka
    cout << "Podaj wage i wartosc (zl) przedmiotow:" << endl;
    for(int i = 0; i < n; i++) // petla pobierajaca dane do tablic i zerujaca tablice k
    {
        cin >> waga[i] >> wart[i];
        sred[i] = (float)wart[i]/(float)waga[i];
        k[i] = 0;
    }

    for(int i = 0; i < n; i++) // petla sortujaca przedmioty rosnacp wzgledem sredniej
    {
        for(int j = 0; j < n; j++)
        {
            if(sred[j] > sred[j+1])
            {
                zamienint(waga[j], waga[j+1]);
                zamienint(wart[j], wart[j+1]);
                zamienfloat(sred[j], sred[j+1]);
            }
        }
    }
    cout << "Posortowane wartosci wzgledem sredniej: " << endl;
    for(int i = 0; i < n; i++)
    {
        cout << waga[i] << " " << wart[i] << endl;
    }

    int aktwaga = 0; // aktualna waga przedmiotow w plecaku
    int wartosc = 0; // aktualna wartosc przedmiotow w plecaku
    for(int i = 0; i < n; i++)
    {
        if((waga[i] + aktwaga) <= w)
        {
            k[i] = 1;
            aktwaga = aktwaga + waga[i];
            wartosc = wartosc + wart[i];
        }
    }

    cout << "Wykorzystane przedmioty:" << endl;
    for(int i = 0; i < n; i++)
    {
        cout << i << ": " << k[i] << endl;
    }
    cout << "Wartosc plecaka: " << wartosc;

    return 0;
}
