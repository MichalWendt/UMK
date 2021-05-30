#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <fstream>

using namespace std;

int funk (vector <int> tab,int x,int n)
{
    int pom, suma=0;
    for(int i=0; i<n; ++i)
    {
        pom=i;
        for(int j=i; j<n; ++j)
        {
            suma=suma+tab[j];
            if(suma==x)
            {
                cout << "znalazlem";
                return pom;
            }
            if(suma>x)
            {
                break;
            }
        }
        suma=0;
    }
    cout << "nie znalazlem";
    return 0;
}


int main()
{
    srand(time(NULL));
    int n,a,b,x;
    int pocz,kon;
    int pom;
    int suma=0;
    fstream plik;
    cout << "ile liczb";
    cin >> n;
    cout << "podaj przedzial ";
    cin >> a >> b;
    cout << "podaj x ";
    cin >> x;
    vector<int> liczby;
    plik.open("liczby.txt", ios::out);
    for(int i=0; i<n; ++i)
    {
        pom=rand()%(b-a+1)+a;
        liczby.push_back(pom);
    }
    for(int i=0; i<n; ++i)
    {
        cout << liczby[i] << " ";
    }
    pocz=funk(liczby,x,n);
    int i=pocz;
    while (suma!=x)
    {
        suma=suma+liczby[i];
        kon=i;
        plik << liczby[i] << " ";
        i++;
    }
    cout << pocz << " " << kon;
    plik.close();
    return 0;
}
