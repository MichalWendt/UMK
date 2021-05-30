#include <iostream>

using namespace std;

const int MAXINT = 2147483646;

int koszt(int *p){
    int n, q, j, i;
    n = (sizeof p)-1;
    int m[n][n];
    for(i = 1; i <= n; i++){
        m[i][i]=0;
    }
    for(int r = 2; r <= n; r++){
        for(i = 1; i <= n - r + 1; i++){
            j = i + r - 1;
            m[i][j] = MAXINT;
            if(i < j){
                for(int k = i; k <= j - 1; k++){
                    q = m[i][k] + m[k+1][j] + (p[i-1] * p[k] * p[j]);
                    if(q < m[i][j]){
                        m[i][j] = q;
                    }
                }
            }
        }
    }

    return m[1][n];
}

int main()
{
    int ilosc;
    cout<<"Ile macierzy bedziemy mnozyc?"<<endl;
    cin>>ilosc;
    int p[ilosc];
    for(int i = 0; i <= ilosc; i++){
        cin>>p[i];
    }
    cout<<"Macierze maja wymiary"<<endl;
    for(int i = 1; i <= ilosc; i++){
        cout<<"A"<<i<<" "<<p[i-1]<<"x"<<p[i]<<endl;
    }
    cout<<"Koszt mnozenia macierzy"<<endl;
    cout<<koszt(p);
    return 0;
}

