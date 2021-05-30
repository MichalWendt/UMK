#include <iostream>

using namespace std;

class Z
{
    public:
    double re;
    double im;
};

Z dodaj (Z a, Z b)
{
    Z wynik;
    wynik.re = a.re + b.re;
    wynik.im = a.im + b.im;
    return wynik;
}

Z odejmij (Z a, Z b)
{
    Z wynik;
    wynik.re = a.re - b.re;
    wynik.im = a.im - b.im;
    return wynik;
}

int main()
{
    Z x, y, wynik;
    char znak, pom;
    cin >> x.re >> x.im;
    cin >> pom >> znak;
    cin >> y.re >> y.im >> pom;
    if(znak == '+')
    {
        wynik = dodaj(x,y);
    }
    if(znak == '-')
    {
        wynik = odejmij(x,y);
    }
    if(wynik.im == 0 && wynik.re == 0)
    {
        cout << "0";
    }
    else if(wynik.re == 0)
    {
        cout << wynik.im << "i";
    }
    else if(wynik.im == 0)
    {
        cout << wynik.re;
    }
    else if(wynik.im >= 0)
    {
        cout << wynik.re << "+" << wynik.im << "i";
    }
    else
    {
        cout << wynik.re << wynik.im << "i";
    }
    return 0;
}