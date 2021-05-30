#include <iostream>

using namespace std;

int main()
{
    string tekst;
    char p, k;
    int c1=0,cmin=100;
    bool czyp;
    cin>>tekst;
    cin>>p>>k;
    for(int i=0; i< tekst.length(); ++i)
    {
        if(tekst[i]==p)
        {
            c1=0;
            czyp = true;
        }
        if(czyp == true && tekst[i+1]==k)
        {
            cmin=min(cmin,c1);
        }
        c1++;
    }
    swap(p,k);
    for(int i=0; i< tekst.length(); ++i)
    {
        if(tekst[i]==p)
        {
            c1=0;
            czyp = true;
        }
        if(czyp == true && tekst[i+1]==k)
        {
            cmin=min(cmin,c1);
        }
        c1++;
    }
    cout<<cmin<<endl;
    return 0;
}
