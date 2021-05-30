#include <iostream>
#include <cmath>
#include <cstdlib>
#include <algorithm>

using namespace std;

void zeros(double **pom, int n, int m)
{
    for(int i = 1; i < n+ 1; ++i)
    {
        for(int j = 1; j < m+ 1; ++j)
        {
            pom[i][j] = 0;
        }
    }
}

void wypisz(double *pom, int n, int m)
{
    for(int i = 1; i < n + 1; ++i)
    {
        cout << pom[i] << "\t";
    }
}

void wypisz2(double **pom, int n, int m)
{
    for(int i = 1; i < n + 1; ++i)
    {
        for(int j = 1; j < m + 1; ++j)
        {
            cout << pom[i][j] << "\t";
        }
        cout << endl;
    }
}

int main(int argc, char **argv)
{
    if ((argc - 1) % 2){
        cout << "error:" << endl << "Prosze podac parzysta ilosc argumentow" << endl;
        return 1;
    }

    int n = (argc-1)/2;

    double X[n+1];
    double Y[n+1];

    for (int i=1; i<=n; ++i) {
        X[i] = atof(argv[i]);
    }

    for (int i=n; i<=2*n; ++i) {
        Y[i - n] = atof(argv[i]);
    }

    double **D = new double *[n+1];
    for(int i=1; i<n+1; i++)
    {
        D[i] = new double[n+1];
    }

    for (int i=1; i<=n; ++i)
    {
        X[i] = atof(argv[i]);
    }

    for (int i=n; i<=2*n; ++i)
    {
        Y[i-n] = atof(argv[i]);
    }
    zeros(D,n,n);

    for(int j=1; j<=n; ++j)
    {
        D[j][1] = Y[j];
    }

    for(int j = 2; j <=n; ++j)
    {
        for(int k=j; k <=n; ++k)
        {
            D[k][j]=(D[k][j-1]-D[k-1][j-1])/(X[k]-X[k-j+1]);
        }
    }

    double C[n+2];
    for(int j=1; j<=n; ++j)
    {
        C[j] = 0;
    }
    C[n] = D[n][n];
    int m;
    for(int k=(n-1); k >=1; --k)
    {
        double Ctmp[n+1];
        for (int i=1; i<=n; ++i)
        {
            Ctmp[i]=C[i]*(-X[k]);
        }
        for (int i=1; i<=n; ++i)
        {
            C[i]=(C[i+1]+Ctmp[i]);
        }
        for (int i=1; i<=n; ++i)
        {
            Ctmp[i]=0;
        }
        C[n]=C[n]+D[k][k];
    }

    cout << "C=" << endl;
    wypisz(C,n,n);
    cout << endl << "D=" << endl;
    wypisz2(D,n,n);
    for(int i=1; i<=n; i++)
    {
        delete[]D[i];
    }
    delete []D;

 return 0;
}
