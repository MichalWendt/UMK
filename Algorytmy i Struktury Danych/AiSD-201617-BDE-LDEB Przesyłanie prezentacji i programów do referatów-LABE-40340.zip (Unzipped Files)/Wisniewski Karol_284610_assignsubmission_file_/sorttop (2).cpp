#include <iostream>
#include <iomanip>
#include <vector>
#define MAX 10000

using namespace std;
vector <int> graf[MAX]; /// graf, krawedzie (wych.)
int in[MAX]; /// krawedzie wchodzace do wierzcholka
int kol[MAX]; /// kolejka
int pocz = 1;
int kon = 1;

int main(){

	int a, b, n, m;

	cin >> n >> m;

	for(int i = 0 ; i <= n; i++) in[i] = 0;

	for(int i = 0 ; i < m; i++)
	{
    	cin >> a >> b;
    	in[b]++;
	    graf[a].push_back(b);
	}


	for(int i = 1; i <= n ; i++)
    	if(in[i] == 0) kol[kon++] = i;

	for(int i = 1; i <= n; i++)
	{
    	int akt = kol[pocz];
    	pocz++;

    	while(!graf[akt].empty())
    	{
			in[graf[akt].back()]--;
        	if (in[graf[akt].back()] == 0)
            	kol[kon++] = graf[akt].back();
        	graf[akt].pop_back();
    	}
	}


	for(int i = 1; i <= n ; i++)
        cout << setw(2) << kol[i];
	return 0;
}
/*
6 10
1 3
2 1 2 3
4 1 4 2 4 5
5 2 5 3
6 1 6 5
        */


