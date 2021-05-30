#include <iostream>

using namespace std;


struct odcinek{
    int x1;
    int y1;
    int x2;
    int y2;
};

int wyznacznik(int x1, int x2, int y1, int y2, int z1, int z2){
    return x1*y2+x2*z1+y1*z2-y2*z1-x2*y1-x1*z2;
}

int sgn(int x){
    if(x>0) return 1;
    else if(x<0) return -1;
    else return 0;
}

int main()
{
    int n;
    int wyz1, wyz2, pom1, pom2;
    cout<<"Podaj ilosc par odcinkow"<<endl;
    cin>>n;
    struct odcinek tab[2*n];
    cout<<"Podaj parami wspolrzedne odcinkow"<<endl;
    for(int i = 0; i < 2*n; i++){
        cin>>tab[i].x1;
        cin>>tab[i].y1;
        cin>>tab[i].x2;
        cin>>tab[i].y2;

    }
  /* for(int i = 0; i < 2*n; i++){
        cout<<tab[i].xa<<" ";
        cout<<tab[i].ya<<" ";
        cout<<tab[i].xb<<" ";
        cout<<tab[i].yb<<endl;
    }
*/
    for(int i = 0; i < 2*n; i += 2){
        if(sgn(wyznacznik(tab[i].x1,tab[i].y1,tab[i].x2,tab[i].y2,tab[i+1].x1,tab[i+1].y1)) != sgn(wyznacznik(tab[i].x1,tab[i].y1,tab[i].x2,tab[i].y2,tab[i+1].x2, tab[i+1].y2)) && sgn(wyznacznik(tab[i+1].x1,tab[i+1].y1,tab[i+1].x2,tab[i+1].y2,tab[i].x1, tab[i].y1)) != sgn(wyznacznik(tab[i+1].x1,tab[i+1].y1,tab[i+1].x2,tab[i+1].y2,tab[i].x2, tab[i].y2))){
            cout<<"t"<<endl;
        }
        else cout<<"n"<<endl;
    }
    return 0;
}
