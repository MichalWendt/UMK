#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cmath>

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

double f(double a)
{
    return sin(a);
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

double sum(double a, int n, double h)
{
    double wynik = 0;

    for(int i = 1; i<=pow(2,n-1); ++i)
    {
        wynik = wynik + f(a+(2*i-1)*h);
    }

    return wynik;
}

int main(int argc, char **argv)
{

    if(argc != 4)
    {
        cout << "Bledna liczba argumentow" << endl << "Prosze podac: a, b, M" << endl;
        return 1;
    }
	double a = atof(argv[1]);
	double b = atof(argv[2]);
	int M = atof(argv[3]);
    int x = M+1;

    double h=b-a;

    double **R = new double *[x+1];
    for(int i=1; i<x+1; i++)
    {
        R[i] = new double[x+1];
    }
    zeros(R,x,x);

    R[1][1]=h*(f(a)+f(b))/2;
    for(int n=1; n<=M; ++n)
    {
        h=h/2.0;
        R[n+1][1]=1.0/2.0*R[n][1]+h*sum(a,n,h);
        for(int m=1; m<=n; ++m)
        {
            R[n+1][m+1]=R[n+1][m]+(R[n+1][m]-R[n][m])/(pow(4,m)-1);
        }
    }

    cout << endl << "R =" << endl;
    wypisz2(R,x,x);

    for(int i=1; i<=x; i++)
    {
        delete[]R[i];
    }
    delete []R;

    return 0;
}
