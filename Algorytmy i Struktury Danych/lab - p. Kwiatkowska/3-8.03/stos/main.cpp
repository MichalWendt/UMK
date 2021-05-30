#include <iostream>

using namespace std;

struct element
{
int liczba;
element *wsk;
};

void  na_stos(int d, element *&w)
{ element *temp;
  temp=w;
  w = new element;
  w->liczba = d;
  w->wsk = temp;
}
void  ze_stosu(int &d, element *&w)
{ element *temp=w;
  d=w->liczba;
  w=w->wsk;
  delete temp;
}
int main()
{
    int liczba;
    element *adres=NULL;
    cout <<"Podaj ilosc elementow"<< endl;
    int n;
    cin>>n;
    for(int i=0; i<n; i++)
    {
        cin>>liczba;
        na_stos(liczba, adres);
    }
    for(int i=n; i>0; i--)
    {
        ze_stosu(liczba, adres);
        cout<<liczba;
    }
    return 0;
}
