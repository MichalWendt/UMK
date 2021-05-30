#include <iostream>

using namespace std;

int horRek(int x, int wsp[], int stopien)
{
    if(stopien==0)
    {
        return wsp[0];
    }
    else
    {
        return horRek(x,wsp,stopien-1)*x+wsp[stopien];
    }
}

int horIte(int x, int wsp[], int stopien)
{
    int wynik=wsp[0];
    for(int i=1; i<=stopien; i++)
    {
        wynik=wynik*x+wsp[i];
    }
    return wynik;
}

int main()
{
    int x,stopien;
    cout << "podaj niewiadoma ";
    cin >> x;
    cout << "podaj stopien ";
    cin >> stopien;
    int wsp[stopien];
    for (int i=stopien; i>=0; --i)
    {
        cout << "podaj wsp przy " << i << " potedze ";
        cin >> wsp[i];
    }
    cout << horRek(x,wsp,stopien) << endl;
    cout << horIte(x,wsp,stopien);
    return 0;
}

