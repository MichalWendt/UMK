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

double f(double a)
{
    return sin(a);
}

int main(int argc, char **argv)
{

    if(argc != 4)
    {
        cout << "Bledna liczba argumentow" << endl << "Prosze podac: a, h, M" << endl;
        //return 1;
    }
	double a = 0;//atof(argv[1]);
	double h = 1;//atof(argv[2]);
	int M = 8;//atof(argv[3]);
    int m = M+1;
    double **D = new double *[m+1];
    for(int i=1; i<m+1; i++)
    {
        D[i] = new double[m+1];
    }
    zeros(D,m,m);
    wypisz2(D,m,m);

    for(int n=0; n <=M; ++n)
    {
        double dh=h/(pow(2,n));
        D[n+1][1]=(f(a+dh)-f(a-dh))/(2*dh);
    }
    for(int k=1; k<=M; ++k)
    {
        for(int n=k; n <=M; ++n)
        {
            D[n+1][k+1]=D[n+1][k]+(D[n+1][k]-D[n][k])/(pow(4,k-1));
        }
    }

    cout << endl << "D=" << endl;
    wypisz2(D,m,m);

    for(int i=1; i<=m; i++)
    {
        delete[]D[i];
    }
    delete []D;

 return 0;
}
