#include <iostream>

using namespace std;

int query(int a, int b, int *w, int M)
{
    int va = M + a;
    int vb = M + b;
    int mini = 101;

    while(va/2 != vb/2)
    {
        if(va%2 == 0)
        {
            if(w[va+1] < mini)
            {
                mini = w[va+1];
            }
        }
        if(vb%2 == 1)
        {
            if(w[vb-1] < mini)
            {
                mini = w[vb-1];
            }
        }

        va = va/2;
        vb = vb/2;
    }
    return mini;
}

int main()
{
    int M;
    int a, b;
    int mini;
    cout << "Elementy: ";
    cin >> M;
    cout << "Przedzial dla minimum: ";
    cin >> a >> b;
    int w[2*M];
    for(int i = 0; i < 2*M; i++)
    {
        w[i] = 0;
    }
    for(int i = M; i < 2*M; i++)
    {
        cin >> w[i];
    }
    int v = M-1;
    while(v != 0)
    {
        if(w[v*2] < w[(v*2)+1])
        {
            w[v] = w[v*2];
        }
        else
        {
            w[v] = w[(v*2)+1];
        }
        v = v-1;
    }

    for(int i = 1; i < 2*M; i++)
    {
        cout << w[i] << " ";
    }

    mini = query(a, b, w, M);

    cout << endl << "Wynik (minimum dla przedzialu): " << mini;
    return 0;
}
