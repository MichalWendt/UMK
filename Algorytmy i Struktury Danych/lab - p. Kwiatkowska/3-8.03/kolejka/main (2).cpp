#include <iostream>

using namespace std;

struct element
{
int liczba;
element *wsk;
};

void do_kolejki(int d, element *&kk)
{
element *temp=kk;
kk = new element;
kk->liczba = d;
kk->wsk = NULL;
if (temp != NULL) temp->wsk = kk;
}
void z_kolejki(int &d, element *&pk)
{
element *temp=pk;
d=pk->liczba;
pk=pk->wsk;
delete temp;
}

int main()
{
    int liczba;
    int n;
    element *pk;
    element *kk=NULL;
    element *pom;
    cout <<"Podaj ilosc elementow"<< endl;
    cin>>n;
    for(int i=0; i<n; i++)
    {
        cin>>liczba;
        pom=kk;
        do_kolejki(liczba, kk);
        if(pom==NULL) pk=kk;
    }
    while(pk!=NULL)
    {
        z_kolejki(liczba, pk);
        cout<<liczba;
    }
    return 0;
}
