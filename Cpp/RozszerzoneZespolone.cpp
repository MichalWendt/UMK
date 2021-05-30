#include <iostream>
#include <string>
#include <strstream>
#include <cstring>
#include <cmath>

using namespace std;

class Z
{
    public:
    double re;
    double im;
    Z(const double r = 0, const double i = 0):re(r),im(i){}
    Z operator+(const Z &z1)
    {
        return Z(this->re+z1.re, this->im+z1.im);
    }
    Z operator-(const Z &z1)
    {
        return Z(this->re-z1.re, this->im-z1.im);
    }
    Z operator*(const Z &z1)
    {
        return Z
        (
            this->re*z1.re - this->im*z1.im ,
            this->re*z1.im + this->im*z1.re
        );
    }
    Z operator/(const Z &z1)
    {
        return Z
        (
            (this->re * z1.re - this->im * (-z1.im)) / ( z1.re * z1.re + z1.im * z1.im ),
            (this->re * (-z1.im) + this->im * z1.re) / ( z1.re * z1.re + z1.im * z1.im )
        );
    }
    bool zero()
    {
        return this->re ==0 && this->im == 0;
    }
    friend istream & operator >> (istream &in,  Z &z);
    friend ostream & operator << (ostream &out,  Z &z);
};

istream & operator >> (istream &in,  Z &z){
    string z1;
    strstream zTmp;
    in >> z1;
    zTmp << z1;
    if(z1[z1.length()-1]=='i')
    {
        if(z1.find("+") !=string::npos || (z1.find("-") != string::npos && z1.find("-") == 1))
        {
            zTmp >>z.re >> z.im ;
        }
        else
        {
            zTmp >> z.im;
        }
    }
    else
    {
        zTmp >>z.re;
    }
    return in;
}

ostream & operator << (ostream &out,  Z &z){
    if(z.re != 0)
    {
        out << round(z.re);
    }
    else
    {
        out <<round( z.im);
    }
    return out;
}

int main()
{
    Z x, y;
    char znak;
    cin >> x;
    cin >> znak;
    cin >> y;

    if(znak == '+')
    {
        x = x+y;
    }
    else if (znak == '-')
    {
        x = x-y;
    }
    else if (znak == '*')
    {
        x = x*y;
    }
    else if (znak == '/')
    {
        x = x/y;
    }
    if(znak == '/' && y.zero())
    {
        cout<<"BLAD";
    }
    else
    {
        cout<<x;
    }
    return 0;
}
