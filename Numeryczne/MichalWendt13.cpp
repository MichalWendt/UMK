#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

double f(double a)
{
    return sin(a);
}

int main(int argc, char **argv)
{
    double h,s1 = 0,s2 = 0,s;
    int j;

    vector <double> x,y;
    if(argc != 4)
    {
        cout << "Bledna liczba argumentow" << endl << "Prosze podac: a, b, M" << endl;
        return 1;
    }
	double a = atof(argv[1]);
	double b = atof(argv[2]);
	int M = atof(argv[3]);

    h=(b-a)/(2*M);

    for(double i = a+h; i <= b-h; i = i + 2*h)
    {
        x.push_back(i);
    }
    for(int i = 0; i < x.size(); ++i)
    {
        y.push_back(f(x[i]));
    }
    for(int i = 0; i < y.size(); ++i)
    {
        s1=s1 + y[i];
    }
    x.clear();
    y.clear();

    for(double i = a+2*h; i <= b-2*h; i = i + 2*h)
    {
        x.push_back(i);
    }
    for(int i = 0; i < x.size(); ++i)
    {
        y.push_back(f(x[i]));
    }
    for(int i = 0; i < y.size(); ++i)
    {
        s2=s2 + y[i];
    }
    s=h*(f(a)+f(b)+4*s1+2*s2)/3;

    cout << s;
    return 0;
}
