#include <iostream>
#include <queue>

using namespace std;

int main()
{
    int n;
    int dlugosc=0;
    string najdluzszy;
    string a;
    queue <string> t[25];
    queue <string> k;
    string slowo;
    cout<<"Podaj liczbe slow"<<endl;
    cin>>n;
    for(int i=0; i<n; i++)
    {
        cin>>a;
        k.push(a);
        if(dlugosc<a.size())
        {
            dlugosc=a.size();
            najdluzszy=a;
        }
    }
   //cout<<najdluzszy;
   while(!k.empty())
    {
    }
    return 0;
}
