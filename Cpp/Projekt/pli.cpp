#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
//-----------------------------------------------losowanie liczb
void losowanie (int * tab, int n)
{
    srand(time(NULL));
    for(int i=0;i<n-1;i++)
    {
        tab[i]=rand()%100;
    }
}
//-----------------------------------------------wybieranie
void proste_wybieranie (int* tab, int n)
{
    for(int i=0;i<n-1;i++)
    {
        int minimalny=i;
        for(int j=i; j<n; j++)
        {
            if((tab[j])<tab[minimalny])
            {
                minimalny=j;
            }
        }
    swap(tab[i],tab[minimalny]);
    }
}
//-----------------------------------------------wstawianie
void proste_wstawiania (int* tab, int n)
{
    int s;
    for(int i=1;i<n;++i)
    {
        s=tab[i];
        int j=i-1;
        while(j>=0 && tab[j]<s)
        {
            tab[j+1]=tab[j];
            j=j-1;
        }
        tab[j+1]=s;
    }
}
//-----------------------------------------------babelkowe
void sortowanie_babelkowe (int* tab, int n)
{
    for(int j=0; j<n-1 ;++j)
    {
       for(int i=0; i<n-1; ++i)
       {
          if(tab[i]>tab[i+1])
          {
             swap(tab[i],tab[i+1]);
          }
       }
    }
}
//-----------------------------------------------zliczanie
void sortowanie_zliczanie (int* tab, int n, int zakres)
{
    int zlicz[zakres];
    int x=0;
    int i,k;
    for (i=0; i<100; ++i)
    {
        zlicz[i]=0;
    }
    for(i=0; i<n; ++i)
    {
        zlicz[tab[i]]=zlicz[tab[i]]+1;
    }
    for(i=0; i<100; ++i)
    {
        if (zlicz[i] != 0)
        {
            for(k=0; k<zlicz[i]; ++k)
            {
                tab[x]=i;
                x++;
            }
        }
    }
}
//-----------------------------------------------scalanie
void scal(int* tab, int pocz, int srodek, int koniec)
{
    int *pom;
    pom = new int [koniec+1];
	int i = pocz;
	int j = srodek + 1;

  for(int i = pocz; i<=koniec; i++)
  {
    pom[i] = tab[i];
  }
  for(int k=pocz; k<=koniec; k++)
  {
    if(i <= srodek)
    {
        if(j <= koniec)
        {
            if(pom[j] < pom[i])
            {
                tab[k] = pom[j++];
            }
            else
            {
                 tab[k] = pom[i++];
            }
        }
        else
        {
            tab[k] = pom[i++];
        }
    }
    else
    {
      tab[k] = pom[j++];
    }
  }
}

void  sortowanie_scalanie(int* tab,int pocz, int koniec)
{
	if(koniec <= pocz)
    {
        return;
    }
	int srodek = (koniec+pocz)/2;

    sortowanie_scalanie(tab, pocz, srodek);
    sortowanie_scalanie(tab, srodek+1, koniec);
    scal(tab, pocz, srodek, koniec);
}
//-----------------------------------------------szybkie
void sortowanie_szybkie(int *tab, int pocz, int koniec)
{
	if(koniec <= pocz)
    {
        return;
    }
	int i = pocz - 1;
	int j = koniec + 1;
	int pivot = tab[(pocz+koniec)/2];
	while(true)
	{
		while(pivot > tab[++i]);

		while(pivot < tab[--j]);
        if( i <= j)
        {
			swap(tab[i],tab[j]);
        }
		else
        {
			break;
        }
	}
	if(j > pocz)
    {
        sortowanie_szybkie(tab, pocz, j);
    }
	if(i < koniec)
    {
        sortowanie_szybkie(tab, i, koniec);
	}
}
//-----------------------------------------------kopcowanie
void przywroc(int *tab, int r, int n)
{
    int min = r;
    if(2*r+1<n && tab[min] > tab[2*r+1])
    {
        min=2*r+1;
    }
    if(2*r+2<n && tab[min] > tab[2*r+2])
    {
        min=2*r+2;
    }
    if(min !=r)
    {
        swap(tab[r],tab[min]);
        przywroc(tab,min,n);
    }
}

void sortowanie_na_kopcu(int *tab, int n)
{
    if(n>0)
    {
        swap(tab[0],tab[n-1]);
        przywroc(tab,0,n-1);
        sortowanie_na_kopcu(tab,n-1);
    }
}

//-----------------------------------------------main
int main()
{
    int *tab;
    int n;
    cout << "podaj ilosc liczb do sortowania:\n";
    cin>>n;
    tab = new int [n];
    int x;

    do{
    cout<<"Wybierz opcje" << endl;
    cout<<"1-Wylosuj dane" << endl;
    cout<<"2-proste wybieranie" << endl;
    cout<<"3-proste wstawiania" << endl;
    cout<<"4-babelkowe" << endl;
    cout<<"5-zliczanie" << endl;
    cout<<"6-scalanie" << endl;
    cout<<"7-szybkie" << endl;
    cout<<"8-na kopcu" << endl;
    cout<<"9-koniec" << endl;

    cin>>x;
    switch(x)
    {
    case 1:
        losowanie ( tab, n);
    cout<<"\nElementy wylosowane:\n";
    for(int i=0; i<n; i++)
    {
        cout<<tab[i]<<" ";
    }
    break;

    case 2:
        proste_wybieranie ( tab, n);
    cout<<"\nElementy posortowane:\n";
    for(int i=0; i<n; i++)
    {
        cout<<tab[i]<<" ";
    }
    break;

    case 3:
        proste_wstawiania ( tab, n);
    cout<<"\nElementy posortowane:\n";
    for(int i=0; i<n; i++)
    {
        cout<<tab[i]<<" ";
    }
    break;

    case 4:
        sortowanie_babelkowe ( tab, n);
    cout<<"\nElementy posortowane:\n";
    for(int i=0; i<n; i++)
    {
        cout<<tab[i]<<" ";
    }
    break;

    case 5:
        sortowanie_zliczanie ( tab, n, 100);
    cout<<"\nElementy posortowane:\n";
    for(int i=0; i<n; i++)
    {
        cout<<tab[i]<<" ";
    }
    break;

    case 6:
        sortowanie_scalanie ( tab,0,n-1);
    cout<<"\nElementy posortowane:\n";
    for(int i=0; i<n; i++)
    {
        cout<<tab[i]<<" ";
    }
    break;

    case 7:
        sortowanie_szybkie ( tab,0, n-1);
    cout<<"\nElementy posortowane:\n";
    for(int i=0; i<n; i++)
    {
        cout<<tab[i]<<" ";
    }
    break;

    case 8:
        int j;
        for(j=n/2; j>=0; --j)
        {
            przywroc(tab,j,n);
        }
        sortowanie_na_kopcu ( tab, n);
    cout<<"\nElementy posortowane:\n";
    for(int i=0; i<n; i++)
    {
        cout<<tab[i]<<" ";
    }
    break;

    case 9:
    cout<<"\nKoniec programu\n";
    break;
    }
    }while (x!=9);

    return 0;
}
