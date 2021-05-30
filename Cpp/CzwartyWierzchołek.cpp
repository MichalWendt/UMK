#include <iostream>

using namespace std;

class wspol
{
    public:
    double x;
    double y;
};

int main()
{
    wspol a,b,c,d;
    cin >> a.x;
    cin >> a.y;
    cin >> b.x;
    cin >> b.y;
    cin >> c.x;
    cin >> c.y;

    if(a.x == b.x)
    {
        d.x=c.x;
        if(a.y==c.y)
        {
            d.y=b.y;
        }
        else
        {
            d.y=a.y;
        }
    }
    else if(a.x == c.x)
    {
        d.x=b.x;
        if(a.y==b.y)
        {
            d.y=c.y;
        }
        else
        {
            d.y=a.y;
        }
    }
    else
    {
        d.x=a.x;
        if(a.y==b.y)
        {
            d.y=c.y;
        }
        else
        {
            d.y=b.y;
        }
    }
    cout << d.x << " " << d.y;
    return 0;
}
