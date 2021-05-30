#include <iostream>
#define INF 1000
using namespace std;

struct EDGE{
    int v, u, w;
};

int V, E;
int *d;
int *p;
EDGE *edge;

bool BF(int);
void wynik(void);

int main(){
    int x;

    cin >> x >> V >> E;

    edge = new EDGE [E];
    d = new int [V];
    p = new int [V];

    for(int i = 0; i < E; i++){
        int a, b, c;
        cin >> a >> b >> c;
        edge[i].v = a;
        edge[i].u = b;
        edge[i].w = c;
    }

    if(BF(x)){
        wynik();
    }
    else
        cout << "Znaleziono ujemny cykl w grafie!";

    delete [] edge;
    delete [] d;
    delete [] p;
    return 0;
}

bool BF(int x){
    for(int i = 0; i < V; i++){
        d[i] = INF;
        p[i] = -1;
    }

    d[x] = 0;
    for (int i = 1; i <= (V - 1); i++){
        for (int j = 0; j < E; j++){
            int u = edge[j].v;
            int v = edge[j].u;
            int w = edge[j].w;
            if ((d[u] != INF) && (d[u] + w < d[v])){
                d[v] = d[u] + w;
                p[v] = u;
            }
        }
    }

    for (int i = 0; i < E; i++){
        int u = edge[i].v;
        int v = edge[i].u;
        int w = edge[i].w;
        if ((d[u] != INF) && (d[u] + w < d[v])){
            return false;
        }
    }

    return true;
}

void wynik(void){
    cout << "\n";
    for(int i = 0; i < V; ++i)
        cout << i << ": " << d[i] << "\n";
}
