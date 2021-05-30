#include <iostream>
#include <vector>

using namespace std;


int main()
{
    int n, m;
    int a, b;

    cout <<"Podaj liczbe wierzcholkow"<< endl;
    cin>>n;
    int st[n];

    vector<int> wiersz(n);
    vector<vector<int> > t(n, wiersz);

    cout<<"Podaj liczbe krawedzi"<< endl;
    cin>>m;

    for(int i=0; i<n; i++)
    {
        st[i] = 0;
    }

    for(int i=0; i<m; i++)
    {

        cout<<"Podaj pare wierzcholkow"<<endl;
        cin>>a>>b;
        t[a][b]=1;
        t[b][a]=1;
        st[a]=st[a]++;
        st[b]=st[b]++;
    }

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            cout<<t[i][j]<<" ";
        }
        cout<<endl;
    }

    for(int i=0; i<n; i++)
    {
        cout<<st[i]<<" ";
    }

    return 0;
}
