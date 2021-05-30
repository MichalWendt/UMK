#include <iostream>
#include <string>

using namespace std;

void Rabin_Karp(string Wzorzec, string Tekst)
{
    int m = Wzorzec.length(), n = Tekst.length(), w = 0, t = 0, h = 1, d = 128, q = 787;

    for (int i = 0; i < m; i++)
    {
        w = (d * w + Wzorzec[i]) %q;
        t = (d * t + Tekst[i]) %q;
        
        if(i < m - 1)
        {
            h = (h * d) %q;
        }
    }

    int x;
    
    for (int s = 0; s <= n - m; s++)
    {
        if ( w == t )
        {
            x = 0;
            
            for (int j = 0; j < m; j++)
            {
                if (Tekst[s + j] != Wzorzec[j])
                {
                    x = 1;
                }
            }
            
            if (x == 0)
            {
                cout << "Wzorzec wystepuje z przesunieciem " << s << endl;
            }
        }
        
        t = (d * (t - Tekst[s] * h) + Tekst[s + m]) %q;
        
        if (t < 0)
        {
            t = t + q;
        }
    }
}

int main()
{
    string wzorzec, tekst;
    cout << "Podaj wzorzec: ";
    getline(cin, wzorzec);
    cout << "Podaj tekst: ";
    getline(cin, tekst);
    Rabin_Karp(wzorzec, tekst);
    
    return 0;
}
