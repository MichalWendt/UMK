#include <iostream>
#include <vector>
#include <queue>

using namespace std;



int main()
{
    int n, m, x, y, pocz, cel, pom;
    cout<<"Podaj ilosc wierzcholkow"<<endl;
    cin>>n; //wierzcholki
    cout<<"Podaj ilosc krawedzi"<<endl;
    cin>>m; //krawedzie
    vector<int> t[n];
    queue<int> kolejka;
    char kolor[n];
    int d[n];
    int ojcowie[n];
   //wypelnianie listy sasiadow
   cout<<"Podaj wierzcholki bedace w relacji"<<endl;
    for(int i=0; i<m; i++)
    {
        cin>>x;
        cin>>y;
        t[x].push_back(y); //na miejscu x podwiesc y
        t[y].push_back(x);
    }

    for(int i=0; i<n; i++)
    {
        cout<<"wiersz "<<i<<":";
        for(int j=0; j<t[i].size(); ++j)
        {
            cout<<t[i][j]<<" ";
        }
         cout<<endl;
    }

    cout<<"====================="<<endl;
    cout<<"Od ktorego wierzcholka szukac?"<<endl;
    cin>>pocz;
    cout<<"Ktorego wierzcholka szukac?"<<endl;
    cin>>cel;


    //wypelniam tablice - stan poczatkowy
    for(int i = 0; i < n; i++){
            kolor[i] = 'B';
            d[i] = 11;
            ojcowie[i] = -1;
        }

    kolor[pocz] = 'S';
    d[pocz] = 0;
    ojcowie[pocz] = -1;
    kolejka.push(pocz);

    while(!kolejka.empty()){
        pocz = kolejka.front();
        for(int i=0; i<t[pocz].size(); i++){
            pom = t[pocz][i];
            if(kolor[pom] == 'B')
            {
                kolor[pom] = 'S';
                d[pom] = d[pocz]+1;
                ojcowie[pom] = pocz;
                kolejka.push(pom);

            }
            kolor[pocz] = 'C';
        }
        kolejka.pop();
    }
    pom = ojcowie[cel];
    cout<<"odleglosc od wierzcholka "<<pocz<<" do wierzcholka " <<cel<<"wynosi"<<endl;
    cout<<d[cel]<<endl;
    cout<<"Droga : "<<cel;
    while(pom != -1){
        cout<< " "<<pom;
        pom = ojcowie[pom];

    }

    return 0;
}
