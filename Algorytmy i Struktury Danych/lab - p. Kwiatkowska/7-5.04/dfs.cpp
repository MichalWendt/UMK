#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void dfs(vector<int> *tab, int *t, char *kolor, int *pi, int &time, int *f, int u)
{
    int pom;
    kolor[u] = 'S';
    time++;
    t[u] = time;
    for(int i = 0; i < tab[u].size(); i++)
        {
            pom = tab[u][i];
            if(kolor[pom] == 'B')
            {
                pi[pom] = u;
                dfs(tab, t, kolor, pi, time, f, pom);
            }
        }
    kolor[u] = 'C';
    time++;
    cout << time << ", ";
    f[u] = time;
}

int main()
{
    int n, m, a, b, pom;

    cout << "Podaj ilosc wierzcholkow: "; cin >> n;
    cout << "Podaj ilosc relacji: "; cin >> m;

    vector<int> tab[n];
    char kolor[n];
    int pi[n];
    int time = 0;
    int f[n];
    int t[n];

    for(int i = 0; i < n; i++)
    {
        kolor[i] = 'B';
        pi[i] = -1;
        f[i] = 0;
        t[i] = 0;
    }

    cout << "Relacje:" << endl;
    for(int i = 0; i < m; i++)
    {
        cin >> a >> b;
        tab[a].push_back(b);
        tab[b].push_back(a);
    }

    for (int i = 0; i < n; i++)
    {
        cout << i << ": ";
        for(int j = 0; j < tab[i].size(); j++)
        {
            cout << tab[i][j] << " ";
        }
        cout << endl;
    }

    cout << "==========" << endl;

    dfs(tab, t, kolor, pi, time, f, 0);

    cout << endl;
    for(int i = 0; i < n; i++)
    {
        cout << kolor[i] << ", ";
    }
    cout << endl;
    for(int i = 0; i < n; i++)
    {
        cout << pi[i] << ", ";
    }
    cout << endl;
    for(int i = 0; i < n; i++)
    {
        cout << t[i] << ", ";
    }
    cout << endl;
    for(int i = 0; i < n; i++)
    {
        cout << f[i] << ", ";
    }
    cout << endl;

    return 0;
}
