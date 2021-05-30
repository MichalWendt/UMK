#include <iostream>
#include <cmath>
#include <complex>
#include <cstdlib>
#include <vector>

using namespace std;

complex <double> Arr[3];

void ddhorner(vector<complex<double>> W, complex<double> x)
{
	int i;
	int n=W.size();
    complex<double> y=W[0];
    complex<double> z=0;
    complex<double> v=0;
    for(i=1; i<n; ++i)
    {
        v=z+v*x;
        z=y+z*x;
        y=y*x+W[i];
    }
    v=v*complex<double>(2);
    Arr[0] = y; Arr[1] = z; Arr[2] = v;
}

int main(int argc, char **argv)
{
    if(argc < 4)
    {
        cout << "Bledna liczba argumentow" << endl << "Prosze podac: W, p0, delta, max" << endl;
        return 1;
    }

	vector<complex<double>> W;
	for(int i = 1; i < argc-4; i=i+2)
    {
        W.push_back(complex<double>(atof(argv[i]),atof(argv[i+1])));
    }

    double re = atof(argv[argc-4]);
    double im = atof(argv[argc-3]);
    complex<double> p0(re, im);
	double delta = atof(argv[argc-2]);
	int maks = atof(argv[argc-1]);

	complex<double> n=W.size()-1;

	complex<double> pn, err, A, B, T, C, C1;
	int k;
    complex<double> y, z, v;
    for(k = 1; k <= maks; ++k)
    {
        ddhorner(W,p0);
        y = Arr[0]; z = Arr[1]; v = Arr[2];

        if(y == complex<double>(0))
        {
            err=0;
            pn=p0;
            break;
        }

        A=-z/y; B=pow(A,2)-v/y; T=sqrt((n- complex<double>(1))*(n*B-pow(A,2)));
        C1=(A+T)/(n);
        C=(A-T)/(n);
        if(abs(C1)>abs(C))
        {
           C=C1;
        }
        pn=p0+complex<double>(1)/C;
        err=abs(pn-p0);
        p0=pn;
        if (err.real() < delta && err.imag() < delta)
        {
           break;
        }
    }

	cout<<"pn = " << pn.real() << " + "<< pn.imag()<< "i" << endl;
	cout<<"err = " << err.real() << " + " << err.imag()<< "i"  <<  endl;
	cout<<"k = " << k << endl;
    return 0;
}
