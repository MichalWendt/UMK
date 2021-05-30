#include <iostream>
#include <cmath>

using namespace std;

long long piszA (long long v, long long n, char odp2)
{
    long long pom[n];
    long long licz=0;
    for (int i = n-1; i >= 0; i--)
    {
        pom[i] = ((v >> i) & 1);
        if(odp2 == 't' || odp2 == 'T')
        {
            cout << ((v >> i) & 1);
        }
    }
    for (int j = 0; j < n; ++j)
    {
        if(pom[j+2]==0 && pom[j+1]==0 && pom[j]==1)
        {
            if(odp2 == 't' || odp2 == 'T')
            {
                cout << "--";
            }
            licz++;
            break;
        }
    }
    return licz;
}

long long piszB (long long v, long long n, char odp2)
{
    long long pom[n];
    long long licz=0;
    for (int i = n-1; i >= 0; i--)
    {
        pom[i] = ((v >> i) & 1);
        if(odp2 == 't' || odp2 == 'T')
        {
            cout << ((v >> i) & 1);
        }
    }
    for (int j = 0; j < n; ++j)
    {
        if(pom[j+2]==1 && pom[j+1]==0 && pom[j]==1)
        {
            if(odp2 == 't' || odp2 == 'T')
            {
                cout << "--";
            }
            licz++;
            break;
        }
    }
    return licz;
}

int main()
{
    long long n;
    char odp1, odp2;
    cout << "Prosze podac dlugosc slowa ";
    cin >> n;
    long long pomo=0;
    long long m=pow(2,n);
    long long v = 0x12345678;
    cout << "Ktory z ciagow sprawdzamy? (a/b) ";
    cin >> odp1;
    cout << "Czy wypisywac wszystkie slowa? (t/n) "
    << endl << "uwaga jezeli dlugosc jest wieksza niz 15 wypisywanie wszystkich slow moze chwile zajac ";
    cin >> odp2;
    if(odp1 == 'a' || odp1 == 'A')
    {
        if(odp2 == 't' || odp2 == 'T')
        {
            for (int j = 0; j < m; ++j)
            {
                pomo = pomo + piszA(j,n,odp2);
                cout << endl;
            }
        }
        else
        {
            for (int j = 0; j < m; ++j)
            {
                pomo = pomo + piszA(j,n,odp2);
            }
        }
    }
    if(odp1 == 'b' || odp1 == 'B')
    {
        if(odp2 == 't' || odp2 == 'T')
        {
            for (int j = 0; j < m; ++j)
            {
                pomo = pomo + piszB(j,n,odp2);
                cout << endl;
            }
        }
        else
        {
            for (int j = 0; j < m; ++j)
            {
                pomo = pomo + piszB(j,n,odp2);
            }
        }
    }
    cout << pomo << " niepasujacych" << endl;
    cout << m-pomo << " pasuje";
    return 0;
}
