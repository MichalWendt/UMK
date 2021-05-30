#include<iostream>
#include<vector>
#include<algorithm>
#include <queue>

using namespace std;

void w_l_s(int m, vector<int> *tab){
    int x, y;
    for(int i=0; i<m; i++){
        cin>>x>>y;
        tab[x].push_back(y);
        tab[y].push_back(x);
    }
}
bool odwiedzone(vector<int> odw,int n){
    for(int i=0; i<n; ++i){
        if(odw[i] == 0){
            return false;
        }
    }
    return true;
}
int numerOdw(vector<int> odw,int n){
    for(int i=0; i<n; ++i){
        if(odw[i] == 0){
            return i;
        }
    }
    return -1 ;
}

bool existRoad(int s, int k, vector<int> *skladowe,vector<int> odw){
    int sp=odw[s];
    for(int i=0; i<skladowe[sp].size();++i){
        if(skladowe[sp][i]==k)
            return true;
    }
    return false;
}

int main(){
    int n,m, V;
    cin>>n>>m;
    vector<int> odw(n);
    int ppr[n];
    vector<int> tab[m];
    int spujne[n];
    w_l_s(m,tab);
    int start,koniec;
     for(int i=0; i< n; i++){
       ppr[i]=-1;
    }
    cout<<"Wektor startowy: ";
    cin>>start;
    cout<<"Wektor koncowy: ";
    cin>>koniec;
    bool allOdw=true;
    queue<int> Q;
    Q.push(start);
    V=start;
    odw[V]=1;
    while(!Q.empty()){
        V=Q.front();
        Q.pop();
        for(int i = 0; i< tab[V].size(); ++i  ){
            if(0 == odw[tab[V][i]]){
              Q.push(tab[V][i]);
              odw[tab[V][i]]=1;
              ppr[tab[V][i]]=V;
            }
        }
    }
    int j=1;
    cout<<endl;
    while(!odwiedzone(odw,n)){
        j++;
        V=numerOdw(odw,n);
        Q.push(V);
        odw[V]=j;
        while(!Q.empty()){
            V=Q.front();
            Q.pop();
            for(int i = 0; i< tab[V].size(); ++i  ){
                if(0 == odw[tab[V][i]]){
                  Q.push(tab[V][i]);
                  odw[tab[V][i]]=j;
                  ppr[tab[V][i]]=V;
                }
            }

        }
    }


//Odczytywanie wyników
    for(int i=0; i< n; i++){
        cout<<ppr[i]<<" ";
    }
    cout<<endl;
     for(int i=0; i< n; i++){
        cout<<odw[i]<<" ";
    }
    int spWyni=0,najSpWynik=0,c=0;;
    for(int i=0; i< n; i++){
        spWyni=max(odw[i],spWyni);
    }
    cout<<endl<<"___WYNIKI____"<<endl;
    cout<<endl<<"Skladowe: "<<spWyni<<endl;
    vector<int> skladowe[spWyni+1];
    for(int i=0; i< n; i++){
       skladowe[odw[i]].push_back(i);
    }

       for(int i=1; i <= spWyni; i++){
           for(int j=0; j< skladowe[i].size(); j++){
                cout<<skladowe[i][j]<<" ";

        }
        int tm=skladowe[i].size();
        najSpWynik=max(najSpWynik,tm);
        cout<<endl;
    }
    cout<<"Najliczniejsz skladowa ma: "<<najSpWynik<<" wierzcholkow"<<endl;
 //Znajdowanie najkrutszej drogi;
    if(existRoad(start,koniec,skladowe,odw)==true){
        int z=koniec;
        int drogaStoK=0;
        cout<<"Wierzcholki w drodze( pomiedzy koncaem a startem ): ";
        while(ppr[ppr[z]]!=-1){
            cout<<ppr[z]<<" ";
            z=ppr[z];
            drogaStoK++;
        }
        cout<<endl<<"Dlugosc droki pomiedzy: "<<start<<" - "<<koniec<<" to: "<<drogaStoK+1<<" krawedz( "<<drogaStoK<<" wierzcholkow )"<<endl;
    }
    else
        cout<<"Podane doroga nie istnieje"<<endl;

    return 0;
}
