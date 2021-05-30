#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

double f(double x)
{
	return sin(x);
}

int main(int argc, char **argv)
{
    if(argc != 6)
    {
        cout << "Bledna liczba argumentow" << endl << "Prosze podac: p0, p1, delta, epsilon, max" << endl;
        return 1;
    }
	double p0 = atof(argv[1]);
	double p1 = atof(argv[2]);
	double delta = atof(argv[3]);
	double epsilon = atof(argv[4]);
	double maks = atof(argv[5]);

	if(f(p0)==0.0)return p0;
	if(f(p1)==0.0)return p1;

	int k;
	double pn,err,ypn;
	/*double ya=f(p0);
    double yb=f(p1);
    if (f(ya)*f(yb)>0)
    {
        pn=-1;err=-1;ypn=-1;k=-1;
        cout<<"error: sign(f(p0))==sign(f(p1))";
        return 1;
    }*/

	for(k = 1; k <= maks; ++k)
    {
        pn=p1-f(p1)*(p1-p0)/(f(p1)-f(p0));
        err=abs(pn-p1);
        p0=p1;
        p1=pn;
        ypn=f(pn);
        if ((err<delta) || (abs(ypn)<epsilon))
            break;
    }

	cout<<"pn = " << pn << endl;
	cout<<"err = " << err << endl;
	cout<<"ypn = " << ypn << endl;
	cout<<"k = " << k << endl;

	return 0;
}
