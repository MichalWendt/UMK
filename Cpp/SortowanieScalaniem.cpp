#include <iostream>

using namespace std;

int *pom;

void scal(int tab[], int l,int s, int p)
{
    int i=l, j=s+1;

    for(int i=l; i<=p; ++i)
    {
        pom[i]=tab[i];
    }
    for(int k=l; k<=p; ++k)
    {
        if(i<=s)
        {
            if(j<=p)
            {
                if(pom[j]<pom[i])
                {
                    tab[k]=pom[j++];
                }
                else
                {
                    tab[k]=pom[i++];
                }
            }
            else
            {
                tab[k]=pom[i++];
            }
        }
        else
        {
            tab[k]=pom[j++];
        }
    }
}

void sorto (int t[], int l, int p)
{
    if(p<=l)return;

    int s=(p+l)/2;
    sorto(t,l,s);
    sorto(t,s+1,p);
    scal(t,l,s,p);
}

int main()
{
    int n;
    cin >> n;
    int *t;
    t=new int[n];
    pom=new int[n];
    for(int i=0; i<n; ++i)
    {
        cin >> t[i];
    }
    sorto(t,0,n-1);
    for(int i=0; i<n; ++i)
    {
       cout << t[i] << " ";
    }
    return 0;
}
