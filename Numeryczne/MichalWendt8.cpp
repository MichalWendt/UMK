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

    int w = (argc-1)/2;
    int n=w-1;

    double X[w+1];
    double Y[w+1];
    double C[w+1];

    for (int i=1; i<=w; ++i) {
        X[i] = atof(argv[i]);
    }

    for (int i=w; i<=2*w; ++i) {
        Y[i - w] = atof(argv[i]);
    }

    double **L = new double *[w+1];
    for(int i=1; i<w+1; i++)
    {
        L[i] = new double[w+1];
    }

    for (int i=1; i<=w; ++i)
    {
        X[i] = atof(argv[i]);
    }

    for (int i=w; i<=2*w; ++i)
    {
        Y[i-w] = atof(argv[i]);
    }
    zeros(L,w,w);

    for(int k=1; k<=n+1; ++k)
    {
        double V[w+1];
        for(int j=1; j<=w; ++j)
        {
            V[j] = 0;
        }
        V[w] = 1;

        for(int j=1; j<=n+1; ++j)
        {
            if(k!=j)
            {
                double Vtmp[w+1];
                for (int i=1; i<=w; ++i)
                {
                    Vtmp[i]=V[i]*(-X[j]);
                }
                for (int i=1; i<=w; ++i)
                {
                    V[i]=(V[i+1]+Vtmp[i])/(X[k]-X[j]);
                }
                for (int i=1; i<=w; ++i)
                {
                    Vtmp[i]=0;
                }
            }
        }

        for(int i=1; i<=n+1; ++i)    //L(k,:)=V;
        {
            L[k][i] = V[i];
        }

    }
    for (int i=1; i<=w; ++i)
    {
        C[i] = 0;
    }

    for (int i=1; i<=w; ++i)
    {
        for (int j=1; j<=w; ++j)
        {
            C[i]+= Y[j]*L[j][i];
        }
    }

    cout << "C=" << endl;
    wypisz(C,w,w);
    cout << endl << "L=" << endl;
    wypisz2(L,w,w);
    for(int i=1; i<=w; i++)
    {
        delete[]L[i];
    }
    delete []L;
    return 0;
}
