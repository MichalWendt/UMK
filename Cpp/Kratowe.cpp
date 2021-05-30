#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

struct pary{
    int x;
    int y;
};

int main()
{
    int n;
    int wynik=0;
    cout << " ile punktow ";
    cin >> n;
    pary punkty[n];
    cout << "podaj punkty";
    for(int i=0; i<n; ++i)
    {
        cin >> punkty[i].x >> punkty[i].y;
    }
    for(int i=0; i<n; ++i)
    {
        wynik=wynik+__gcd(abs(punkty[i].x-punkty[i+1].x),abs(punkty[i].y-punkty[i+1].y));
    }
    wynik=wynik+__gcd(abs(punkty[n-1].x-punkty[0].x),abs(punkty[n-1].y-punkty[0].y));
    cout << wynik-1;
    return 0;
}
