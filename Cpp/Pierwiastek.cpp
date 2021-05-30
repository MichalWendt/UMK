#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    double a,b=1,wynik=0;
    cout << "jaka liczba ";
    cin >> a;
    int n;
    cout << "ile razy ";
    cin >> n;
    for(int i=0; i<n; ++i)
    {
        wynik=(b+a/b)/2;
        b=wynik;
    }
    cout << wynik << endl;
    cout << sqrt(a);
    return 0;
}
