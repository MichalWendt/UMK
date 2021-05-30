#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    int n, t=0;
    char spos;
    vector <int> tab;
    cin >> n;
    for(int i=0; i<n; i++)
    {
        cin >> t;
        tab.push_back(t);
    }
    cin >> spos;
    t=0;
    for(int i=0; i<n; i++)
    {
        for(int j=1; j<n-i; j++)
        {
            if(spos == 'A')
            {
                if(tab[j-1]>tab[j])
                {
                    swap(tab[j-1], tab[j]);
                    t++;
                }
            }
            else
            {
                if(tab[j-1]<tab[j])
                {
                    swap(tab[j-1], tab[j]);
                    t++;
                }
            }

        }
    }
    for(int i=0; i<n; i++)
    {
        cout << tab[i] << " ";
    }
    cout << t;
    return 0;
}