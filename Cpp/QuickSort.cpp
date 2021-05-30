#include<iostream>
using namespace std;


void quick_sort(int *tab, int lewy, int prawy)
{
	if(prawy <= lewy) return;

	int i = lewy - 1, j = prawy + 1,
	pivot = tab[(lewy+prawy)/2];
	while(1)
	{
		while(pivot>tab[++i]);

		while(pivot<tab[--j]);

		if( i <= j)
			swap(tab[i],tab[j]);
		else
			break;
	}
	if(j > lewy)
	quick_sort(tab, lewy, j);
	if(i < prawy)
	quick_sort(tab, i, prawy);
}

int main()
{
	int *tab, n;
  	cin>>n;
  	tab = new int [n];
  	for(int i=0;i<n;i++)
    	cin>>tab[i];

  	quick_sort(tab,0, n-1);

  	for(int i=0;i<n;i++)
          cout<<tab[i]<<" ";

  	return 0;
}

