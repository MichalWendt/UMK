#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <stack>
#define MAX 10000

using namespace std;

int a, b, w, u;
bool vis[MAX];
stack <int> stos;
vector <int> graf[MAX];

void DFS(int s)
{
	for(int i = 0; i < graf[s].size(); i++)
	{
		if(!vis[graf[s][i]])	DFS(graf[s][i]);
	}
	vis[s] = true;
	stos.push(s);
}

int porownaj(int x, int y)
{
	return x > y;
}

int main()
{

	for(int i = 1; i <= MAX; i++)
	{
		vis[i] = 0;
		graf[i].clear();
	}

	cin >> a >> b;
	for(int i = 0; i < b; i++)
	{
		cin >> u >> w;
		graf[u].push_back(w);
	}
	for(int i = 1; i <= a; i++)
	{
		sort(graf[i].begin(), graf[i].end(), porownaj);
	}
	for(int i = a; i >= 1; i--)
	{
		if(!vis[i])	DFS(i);
		
	}

	cout<<"\n";

	while(!stos.empty())
	{
		cout<<" "<<stos.top();
		stos.pop();
	}
	
	return 0;
}
