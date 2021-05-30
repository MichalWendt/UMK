#include <iostream>
#include <algorithm>


using namespace std;

int main()
{
    int a,n;
    //cout<<"Podaj maksymalne obciazenie kajaka"<<endl;
    cin>>a;
    cout<<endl;
    //cout<<"Podaj liczbe uczestnikow splywu"<<endl;
    cin>>n;
    int t[n];
    cout<<endl;
    //cout<<"Podaj wage kazdej osoby"<<endl;
    for(int i=0; i<n; i++)
    {
        cin>>t[i];
    }
    sort(&t[0],&t[n-1]);
    int licz=0;
    int y=n-1;
    int x=0;
    while(x<=y)
    {
        if(t[x]+t[y]<=a)
        {
            licz++;
            x++;
            --y;
        }
        else
        {
            licz++;
            --y;
        }
    }
    cout<<licz;
    return 0;
}
