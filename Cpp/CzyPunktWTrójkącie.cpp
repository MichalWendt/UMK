#include <iostream>
#include <cmath>

using namespace std;

struct punkt
{
    int x,y;
};

double pole(int ax, int ay, int bx, int by, int cx, int cy)
{
    return 0.5 * abs((ax * (by - cy) + bx * (cy - ay) + cx * (ay - by)));
}

bool czywsrodku(int ax, int ay, int bx, int by, int cx, int cy, int pomx, int pomy)
{
    double obszar = pole(ax, ay, bx, by, cx, cy);
    double obszar1 = pole(pomx, pomy, bx, by, cx, cy);
    double obszar2 = pole(ax, ay, pomx, pomy, cx, cy);
    double obszar3 = pole(ax, ay, bx, by, pomx, pomy);
    return (obszar == obszar1 + obszar2 + obszar3);
}

int main()
{
    punkt a,b,c, pom;
    int n;
    cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
    cin >> n;
    punkt tab[n];
    for(int i = 0; i < n; ++i)
    {
        cin >> tab[i].x >> tab[i].y;
    }
    for(int i = 0; i < n; ++i)
    {
        pom.x = tab[i].x;
        pom.y = tab[i].y;
        if(!(czywsrodku(a.x, a.y, b.x, b.y, c.x, c.y, pom.x, pom.y)))
        {
            cout << pom.x << " " << pom.y << endl;
        }
    }
    return 0;
}
