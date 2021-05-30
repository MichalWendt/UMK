#include <iostream>

using namespace std;
// jednokrotne wykorzystanie danego przedmiotu, algorytm dynamiczny dla ogólnej sytuacji

int main()
{
    int w; //pojemnosc plecaka
    int n; //ilosc dostepnych przedmiotow
    int pom = 0; //wartosc pomocnicza
    cout << "Podaj pojemnosc plecaka: ";
    cin >> w;
    cout << "Podaj ilosc przedmiotow: ";
    cin >> n;
    int P[n+1][w+1]; //tablica maksymalnej wartosci przedmiotow w plecaku
    int Q[n+1][w+1]; //tablica pomagaj¹ca znalezc przedmioty w³o¿one do plecaka
    for(int i = 0; i <= n; i++)
    {
        for(int j = 0; j <= w; j++)
        {
            P[i][j] = 0;
            Q[i][j] = 0; //wyzerowanie obu tablic
        }
    }

    int waga[n+1];
    int wart[n+1]; //tablice przechowuj¹ce dane o przedmiotach

    cout << "Podaj przedmioty (waga/wartosc): " << endl;
    for(int i = 1; i <= n; i++)
    {
        cin >> waga[i] >> wart[i];
    }

    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= w; j++)
        {
            pom = P[i-1][j-waga[i]];
            pom = pom + wart[i];
            if((j >= waga[i]) && (P[i-1][j] < pom)) //sprawdzanie, czy przedmiot miesci siê do plecaka
            {                                            // i czy ma wartosc mniejsz¹ od wczeœniej wybranej rzeczy
                P[i][j] = pom;
                Q[i][j] = i;
            }
            else                        // jeœli siê nie mieœci, powtórzyæ wartoœæ z poprzedniej linijki
            {
                P[i][j] = P[i-1][j];
                Q[i][j] = Q[i-1][j];
            }
        }
    }


    for(int i = 1; i <= n; i++)         //wyœwietlanie tablic dla sprawdzenia wyników
    {
        for(int j = 1; j <= w; j++)
        {
            cout << P[i][j] << " ";
        }
        cout << endl;
    }
    cout << "==========" << endl;
    for(int i = 1; i <= n; i++)
    {
        for(int j = 1; j <= w; j++)
        {
            cout << Q[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Maksymalna wartosc plecaka: " << P[n][w] << endl;
    cout << "Przedmioty umieszczone w plecaku: ";
    while(w != 0)
    {
        cout << Q[n][w] << " ";
        w = w - waga[Q[n][w]]; // po wyœwietleniu rzeczy nastêpuje cofniêcie siê do rzeczy o adekwatnie mniejszej wadze
    }

    return 0;
}
