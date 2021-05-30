#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{
        srand(time(NULL));
        int maks=0;
        int ile=0;
        int n;
        cout << "ile liczb ";
        cin >> n;
        int a,b;
        cout << "podaj przedzial ";
        cin >> a >> b;
        int tab[n];
        for(int i=0; i<n; ++i)
        {
            tab[i]=rand()%b+a;
        }
        for(int i=0; i<n; ++i)
        {
            cout << tab[i] << " ";
        }
        for(int i=0; i<n; ++i)
        {
            for(int j=i; j<n; ++j)
            {
                if(tab[j-1]<=tab[j])
                {
                    ile++;
                }
                else
                {
                    ile++;
                    if(maks<ile)
                    {
                        maks=ile;
                    }
                    break;
                }
            }
            ile=0;
        }
        cout << endl;
        cout << maks;
        return 0;
}
