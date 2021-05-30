#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    int n,m,x,y;
    int i,j,k;
    int sasiad;
    cin >> n >> m;
    vector <int> sasiedzi[n];
    queue <int> q;
    int ilesasiadow [n];

    for(i=0; i<n; ++i)
    {
        ilesasiadow[i]=0;
    }
    for(i=0; i<m; ++i)
    {
        cin >> x >> y;
        sasiedzi[x].push_back(y);
        ilesasiadow[y]++;
    }
    for(i=0; i<n; ++i)
    {
        if(ilesasiadow[i] == 0)
        {
            q.push(i);
        }
    }
    while(!q.empty())
    {
        k = q.front();
        cout << k << " ";
        for(i=0; i<sasiedzi[k].size(); ++i)
        {
            sasiad = sasiedzi[k][i];
            if(ilesasiadow[sasiad] >= 0)
            {
                ilesasiadow[sasiad]--;
                if(ilesasiadow[sasiad]==0)
                {
                    q.push(sasiad);
                }
            }
        }
        q.pop();
    }
    return 0;
}
