#include <iostream>

using namespace std;

const int MAX=214748364;

int koszt_mnozen(int *p, int n){
    int m[n][n];
    int dl, j, i, k, q; //dl-dlugosc ciagu macierzy


    for(i=0; i<n; i++){ //zerowanie tablicy
        for(j=0; j<n; j++){
            m[i][j]=0;
        }
    }

    for(dl=2; dl<n; dl++){ //sprawdzam liczbe mnozen dla kolejnych dluzszych podciagow
        for(i=1; i<n-dl+1; i++){ //dla wszystkich podci¹gów danej d³ugoœci
            j=i+dl-1;
            m[i][j]=MAX;

            for(k=i; k<=j-1; k++){
                q=m[i][k]+m[k+1][j]+p[i-1]*p[k]*p[j]; //obliczenie kosztu mnozenia danego podciagu
                if(q<m[i][j]){
                    m[i][j] = q;
                }
            }
        }
    }
   /* for(i=0; i<n; i++){
        for(j=0; j<n; j++){
            cout<<m[i][j]<<"  ";
        }
        cout<<endl;
    }*/
    return m[1][n-1];
}

int main()
{
    int ilosc;
    cout<<"Podaj ilosc macierzy"<<endl;
    cin>>ilosc;

    int p[ilosc+1];

    cout<<"Podaj wymiary macierzy"<<endl;
    for(int i = 0; i < ilosc+1; i++){
        cin>>p[i];
    }

    cout<<"Minimalny koszt pomozenia macierzy "<<koszt_mnozen(p,ilosc+1);

    return 0;
}
