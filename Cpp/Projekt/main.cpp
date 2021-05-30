#include <iostream>
#include "biblioteka.h"

using namespace std;

//-----------------------------------------------main
int main()
{
    int *tab;
    int n;
    cout << "podaj ilosc liczb do sortowania:\n";
    cin>>n;
    tab = new int [n];
    int x;

    do{
    cout<<"Wybierz opcje" << endl;
    cout<<"1-Wylosuj dane" << endl;
    cout<<"2-proste wybieranie" << endl;
    cout<<"3-proste wstawiania" << endl;
    cout<<"4-babelkowe" << endl;
    cout<<"5-zliczanie" << endl;
    cout<<"6-scalanie" << endl;
    cout<<"7-szybkie" << endl;
    cout<<"8-na kopcu" << endl;
    cout<<"9-koniec" << endl;

    cin>>x;
    switch(x)
    {
    case 1:
        losowanie ( tab, n);
    cout<<"\nElementy wylosowane:\n";
    for(int i=0; i<n; i++)
    {
        cout<<tab[i]<<" ";
    }
    break;

    case 2:
        proste_wybieranie ( tab, n);
    cout<<"\nElementy posortowane:\n";
    for(int i=0; i<n; i++)
    {
        cout<<tab[i]<<" ";
    }
    break;

    case 3:
        proste_wstawiania ( tab, n);
    cout<<"\nElementy posortowane:\n";
    for(int i=0; i<n; i++)
    {
        cout<<tab[i]<<" ";
    }
    break;

    case 4:
        sortowanie_babelkowe ( tab, n);
    cout<<"\nElementy posortowane:\n";
    for(int i=0; i<n; i++)
    {
        cout<<tab[i]<<" ";
    }
    break;

    case 5:
        sortowanie_zliczanie ( tab, n, 100);
    cout<<"\nElementy posortowane:\n";
    for(int i=0; i<n; i++)
    {
        cout<<tab[i]<<" ";
    }
    break;

    case 6:
        sortowanie_scalanie ( tab,0,n-1);
    cout<<"\nElementy posortowane:\n";
    for(int i=0; i<n; i++)
    {
        cout<<tab[i]<<" ";
    }
    break;

    case 7:
        sortowanie_szybkie ( tab,0, n-1);
    cout<<"\nElementy posortowane:\n";
    for(int i=0; i<n; i++)
    {
        cout<<tab[i]<<" ";
    }
    break;

    case 8:
        int j;
        for(j=n/2; j>=0; --j)
        {
            przywroc(tab,j,n);
        }
        sortowanie_na_kopcu ( tab, n);
    cout<<"\nElementy posortowane:\n";
    for(int i=0; i<n; i++)
    {
        cout<<tab[i]<<" ";
    }
    break;

    case 9:
    cout<<"\nKoniec programu\n";
    break;
    }
    }while (x!=9);

    return 0;
}
