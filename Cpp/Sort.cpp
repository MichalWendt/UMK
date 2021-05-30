#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    int n;
    cin >> n;
    int tab [n][5];
    for(int i=0; i<n; ++i)
    {
        cin >> tab[i][0] >> tab[i][1] >> tab[i][2] >> tab[i][3];
        tab[i][4]=i;
    }
    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<n-1; ++j)
        {
            if(tab[j][0] > tab[j+1][0])
            {
                swap (tab[j][0],tab[j+1][0]);
                swap (tab[j][1],tab[j+1][1]);
                swap (tab[j][2],tab[j+1][2]);
                swap (tab[j][3],tab[j+1][3]);
                swap (tab[j][4],tab[j+1][4]);
            }
            if(tab[j][0] == tab[j+1][0])
            {
                if(tab[j][1] == tab[j+1][1])
                {
                    if(tab[j][2] == tab[j+1][2])
                    {
                        if(tab[j][3] == tab[j+1][3])
                        {
                            break;
                        }
                        if(tab[j][3] > tab[j+1][3])
                        {
                            swap (tab[j][0],tab[j+1][0]);
                            swap (tab[j][1],tab[j+1][1]);
                            swap (tab[j][2],tab[j+1][2]);
                            swap (tab[j][3],tab[j+1][3]);
                            swap (tab[j][4],tab[j+1][4]);
                        }
                    }
                    if(tab[j][2] > tab[j+1][2])
                    {
                        swap (tab[j][0],tab[j+1][0]);
                        swap (tab[j][1],tab[j+1][1]);
                        swap (tab[j][2],tab[j+1][2]);
                        swap (tab[j][3],tab[j+1][3]);
                        swap (tab[j][4],tab[j+1][4]);
                    }
                }
                if(tab[j][1] > tab[j+1][1])
                {
                    swap (tab[j][0],tab[j+1][0]);
                    swap (tab[j][1],tab[j+1][1]);
                    swap (tab[j][2],tab[j+1][2]);
                    swap (tab[j][3],tab[j+1][3]);
                    swap (tab[j][4],tab[j+1][4]);
                }
            }
        }
    }
    for(int i=0; i<n; ++i)
    {
        cout << tab[i][4]+1 << " ";
    }
    cout << endl;
    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<n-1; ++j)
        {
            if(tab[j][1] > tab[j+1][1])
            {
                swap (tab[j][0],tab[j+1][0]);
                swap (tab[j][1],tab[j+1][1]);
                swap (tab[j][2],tab[j+1][2]);
                swap (tab[j][3],tab[j+1][3]);
                swap (tab[j][4],tab[j+1][4]);
            }
            if(tab[j][1] == tab[j+1][1])
            {
                if(tab[j][2] == tab[j+1][2])
                {
                    if(tab[j][3] == tab[j+1][3])
                    {
                        if(tab[j][0] == tab[j+1][0])
                        {
                            break;
                        }
                        if(tab[j][0] > tab[j+1][0])
                        {
                            swap (tab[j][0],tab[j+1][0]);
                            swap (tab[j][1],tab[j+1][1]);
                            swap (tab[j][2],tab[j+1][2]);
                            swap (tab[j][3],tab[j+1][3]);
                            swap (tab[j][4],tab[j+1][4]);
                        }
                    }
                    if(tab[j][3] > tab[j+1][3])
                    {
                        swap (tab[j][0],tab[j+1][0]);
                        swap (tab[j][1],tab[j+1][1]);
                        swap (tab[j][2],tab[j+1][2]);
                        swap (tab[j][3],tab[j+1][3]);
                        swap (tab[j][4],tab[j+1][4]);
                    }
                }
                if(tab[j][2] > tab[j+1][2])
                {
                    swap (tab[j][0],tab[j+1][0]);
                    swap (tab[j][1],tab[j+1][1]);
                    swap (tab[j][2],tab[j+1][2]);
                    swap (tab[j][3],tab[j+1][3]);
                    swap (tab[j][4],tab[j+1][4]);
                }
            }
        }
    }
    for(int i=0; i<n; ++i)
    {
        cout << tab[i][4]+1 << " ";
    }
    cout << endl;
    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<n-1; ++j)
        {
            if(tab[j][2] > tab[j+1][2])
            {
                swap (tab[j][0],tab[j+1][0]);
                swap (tab[j][1],tab[j+1][1]);
                swap (tab[j][2],tab[j+1][2]);
                swap (tab[j][3],tab[j+1][3]);
                swap (tab[j][4],tab[j+1][4]);
            }
            if(tab[j][2] == tab[j+1][2])
            {
                if(tab[j][3] == tab[j+1][3])
                {
                    if(tab[j][0] == tab[j+1][0])
                    {
                        if(tab[j][1] == tab[j+1][1])
                        {
                            break;
                        }
                        if(tab[j][1] > tab[j+1][1])
                        {
                            swap (tab[j][0],tab[j+1][0]);
                            swap (tab[j][1],tab[j+1][1]);
                            swap (tab[j][2],tab[j+1][2]);
                            swap (tab[j][3],tab[j+1][3]);
                            swap (tab[j][4],tab[j+1][4]);
                        }
                    }
                    if(tab[j][0] > tab[j+1][0])
                    {
                        swap (tab[j][0],tab[j+1][0]);
                        swap (tab[j][1],tab[j+1][1]);
                        swap (tab[j][2],tab[j+1][2]);
                        swap (tab[j][3],tab[j+1][3]);
                        swap (tab[j][4],tab[j+1][4]);
                    }
                }
                if(tab[j][3] > tab[j+1][3])
                {
                    swap (tab[j][0],tab[j+1][0]);
                    swap (tab[j][1],tab[j+1][1]);
                    swap (tab[j][2],tab[j+1][2]);
                    swap (tab[j][3],tab[j+1][3]);
                    swap (tab[j][4],tab[j+1][4]);
                }
            }
        }
    }
    for(int i=0; i<n; ++i)
    {
        cout << tab[i][4]+1 << " ";
    }
    cout << endl;
    for(int i=0; i<n; ++i)
    {
        for(int j=0; j<n-1; ++j)
        {
            if(tab[j][3] > tab[j+1][3])
            {
                swap (tab[j][0],tab[j+1][0]);
                swap (tab[j][1],tab[j+1][1]);
                swap (tab[j][2],tab[j+1][2]);
                swap (tab[j][3],tab[j+1][3]);
                swap (tab[j][4],tab[j+1][4]);
            }
            if(tab[j][3] == tab[j+1][3])
            {
                if(tab[j][0] == tab[j+1][0])
                {
                    if(tab[j][1] == tab[j+1][1])
                    {
                        if(tab[j][2] == tab[j+1][2])
                        {
                            break;
                        }
                        if(tab[j][2] > tab[j+1][2])
                        {
                            swap (tab[j][0],tab[j+1][0]);
                            swap (tab[j][1],tab[j+1][1]);
                            swap (tab[j][2],tab[j+1][2]);
                            swap (tab[j][3],tab[j+1][3]);
                            swap (tab[j][4],tab[j+1][4]);
                        }
                    }
                    if(tab[j][1] > tab[j+1][1])
                    {
                        swap (tab[j][0],tab[j+1][0]);
                        swap (tab[j][1],tab[j+1][1]);
                        swap (tab[j][2],tab[j+1][2]);
                        swap (tab[j][3],tab[j+1][3]);
                        swap (tab[j][4],tab[j+1][4]);
                    }
                }
                if(tab[j][0] > tab[j+1][0])
                {
                    swap (tab[j][0],tab[j+1][0]);
                    swap (tab[j][1],tab[j+1][1]);
                    swap (tab[j][2],tab[j+1][2]);
                    swap (tab[j][3],tab[j+1][3]);
                    swap (tab[j][4],tab[j+1][4]);
                }
            }
        }
    }
    for(int i=0; i<n; ++i)
    {
        cout << tab[i][4]+1 << " ";
    }
    return 0;
}
