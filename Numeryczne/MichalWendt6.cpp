#include <iostream>
#include <cmath>
#include <cstdlib>
#include <algorithm>

using namespace std;

void eye(double **pom, int n, int m)
{
    for(int i = 1; i < n + 1; ++i)
    {
        for(int j = 1; j < m + 1; ++j)
        {
            if(i == j)
            {
                pom[i][j] = 1;
            }
            else
            {
                pom[i][j] = 0;
            }
        }
    }
}

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

void wypisz(double **pom, int n, int m)
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

    if(sqrt(argc-1) != round(sqrt(argc-1)))
    {
        cout << "error:n~=m" << endl << "Prosze podac macierz kwadratowa" << endl;
        return 1;
    }

    int n = sqrt(argc-1);
    int m = sqrt(argc-1);
    double **A;
    A = new double *[m + 1];
    for(int i = 1; i <n +1; i++)
        A[i] = new double[m +1];

    double **A2;
    A2 = new double *[m + 1];
    for(int i = 1; i <n +1; i++)
        A2[i] = new double[m +1];

    double **P2;
    P2 = new double *[m + 1];
    for(int i = 1; i <n +1; i++)
        P2[i] = new double[m +1];


	for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j < m; ++j)
        {
            A[i + 1][j + 1] = (atof(argv[i*n+j+1]));
        }
    }

    double **L;
    L = new double *[m + 1];
    for(int i = 1; i <n + 1; i++)
        L[i] = new double[m + 1];
    eye(L,n,m);

    double **P;
    P = new double *[m + 1];
    for(int i = 1; i <n + 1; i++)
        P[i] = new double[m + 1];
    eye(P,n,m);

    double **U;
    U = new double *[m + 1];
    for(int i = 1; i <n + 1; i++)
        U[i] = new double[m + 1];
    zeros(U,n,m);

    int p[n + 1];
    for(int i = 1; i < n + 1; ++i)
    {
        p[i] = i;
    }
    double s[m + 1];
    double maks = 0;
    for(int i = 1; i < m + 1; ++i)
    {
        for(int j = 1; j < m + 1; ++j)
        {
            if(maks <= abs(A[i][j]))
            maks = abs(A[i][j]);
        }
        s[i] = maks;
        maks = 0;
    }

    int j,t;
    double z;
    double wynik = -1;
    for(int k = 1; k <= n -1; ++k)
    {
        for(int i = k; i < n + 1; ++i)
            {
                if(wynik < abs(A[p[i]][k])/(s[p[i]]))
                {
                    wynik = abs(A[p[i]][k])/(s[p[i]]);
                    j = i - k + 1;
                }
            }
            wynik = -1;

        j=j+k-1;

        t=p[j];
        p[j]=p[k];
        p[k]=t;

        for(int i=k + 1; i<n + 1; ++i)
        {
            z=A[p[i]][k]/A[p[k]][k];
            A[p[i]][k]=z;
            for (int r=k + 1; r<n + 1; ++r)
            {
                A[p[i]][r]=A[p[i]][r]-z*A[p[k]][r];
            }
        }

    }

    for(int i=1; i < n + 1; ++i)
    {
        for(int j=1; j < n + 1; ++j)
        {
            A2[i][j] = A[p[i]][j];
            P2[i][j] = P[p[i]][j];
        }
    }

    for(int i=1; i < n + 1; ++i)
    {
        for(int j=1; j < n + 1; ++j)
        {
            if (i<=j)
            {
                U[i][j]=A2[i][j];
            }
            else
            {
                L[i][j]=A2[i][j];
            }
        }
    }

	cout<< endl << "P = " << endl; wypisz(P2,n,m);
	cout<<"L = " << endl; wypisz(L,n,m);
	cout<<"U = " << endl; wypisz(U,n,m);
    return 0;
}
