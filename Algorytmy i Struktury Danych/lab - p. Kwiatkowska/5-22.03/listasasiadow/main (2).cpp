#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n, m, x, y;
    cin>>n; //wierzcholki
    cin>>m; //krawedzie
    vector<int> t[n];
    for(int i=0; i<m; i++)
    {
        cin>>x;
        cin>>y;
        t[x].push_back(y); //na miejscu x podwiesc y
        t[y].push_back(x);
    }

    for(int i=0; i<n; i++)
    {
        cout<<"wiersz "<<i<<":";
        for(int j=0; j<t[i].size(); ++j)
        {
            cout<<t[i][j]<<" ";
        }
         cout<<endl;
    }
    return 0;
}
