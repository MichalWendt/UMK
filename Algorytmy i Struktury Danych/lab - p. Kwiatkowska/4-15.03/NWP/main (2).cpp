#include <iostream>
#include <vector>
#include <string>

using namespace std;

int max(int a, int b)
{
    if(a>b) return a;
    else return b;
}

int main()
{
    string a, b;
    cout <<"Podaj slowo a"<< endl;
    cin>>a;
    cout<<"Podaj slowo b"<<endl;
    cin>>b;

    vector<int> wiersz(b.size()+1);
    vector<vector<int> > t(a.size()+1, wiersz);

    for(int i=0; i<=b.size(); i++)
    {
        t[i][0]=0;
    }
    for(int j=0; j<=a.size(); j++)
    {
        t[0][j]=0;

    }
     /*for(int i=0; i<=a.size(); i++)
    {
        for(int j=0; j<=b.size(); j++)
        {
            cout<<t[i][j]<<" ";
        }
        cout<<endl;
    }
*/
   for(int i=1; i<=a.size(); i++)
    {

        for(int j=1; j<=b.size(); j++)
        {
            if(b[j]!=a[i])
            {
                t[i][j]=max(t[i][j-1],t[i-1][j]);
            }
            else
            {
                t[i][j]//[8]8
            }
        }
    }
  /*  for(int i=0; i<=a.size(); i++)
    {
        for(int j=0; j<=b.size(); j++)
        {
            cout<<t[i][j]<<" ";
        }
        cout<<endl;
    }
*/
    return 0;
}
