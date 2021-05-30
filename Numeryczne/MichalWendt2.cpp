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
        cout << "Bledna liczba argumentow" << endl << "Prosze podac: a, b, delta, epsilon, max" << endl;
        return 1;
    }
	double a = atof(argv[1]);
	double b = atof(argv[2]);
	double delta = atof(argv[3]);
	double epsilon = atof(argv[4]);
	double maks = atof(argv[5]);

	if(f(a)==0.0)return a;
	if(f(b)==0.0)return b;

	int k;
	double c,err,yc;
	double ya=f(a);
    double yb=f(b);
    if (f(ya)*f(yb)>0)
    {
        c=-1;err=-1;yc=-1;k=-1;
        cout<<"error: sign(f(a))==sign(f(b))";
        return 1;
    }

	for(k = 1; k <= maks; ++k)
    {
        c=a+(b-a)/2;
        yc=f(c);
        err=abs((b-a)/2);
        if ((err<delta) || (abs(yc)<epsilon))
            break;

        if (f(yb)*f(yc)>0)
        {
            b=c;
            yb=yc;
        }
        else
            a=c;
    }

	cout<<"c = " << c << endl;
	cout<<"err = " << err << endl;
	cout<<"yc = " << yc << endl;
	cout<<"k = " << k << endl;

	return 0;
}
