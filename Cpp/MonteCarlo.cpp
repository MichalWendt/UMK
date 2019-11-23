#include <iostream>
#include <random>
#include <cmath>
#include <cstdlib>

using namespace std;

class Punkt
{
    public:
    double x;
    double y;
    Punkt(double x = 0, double y =0);
};

class Kolo
{
    public:
    int promien;
    Punkt punkt;
    Kolo();
    bool czyPunktJestWewnatrz(Punkt* punkt);
};

class MonteCarlo
{
    public:
    Kolo kolko;
    Punkt *pkt;
    void srodek()
    {
        kolko.punkt.x = 0;
        kolko.punkt.y = 0;
    }

    double losowanie(int s,int m, int n)
    {
        int ile;
        srodek();
        default_random_engine e(s);
        uniform_real_distribution<double> dist(0.0,1.0);
        for(int i = 0; i < m; ++i)
        {
            pkt->x = dist(e);
            pkt->y = dist(e);
            if(kolko.czyPunktJestWewnatrz(pkt))
            {
                ile++;
            }
        }
        ile = (ile * 4) / m;
        ile = (double)pow(10,n);
        cout << ile << endl;
        ile = (int)ile%10;
        return ile;
    }

};

Punkt::Punkt()
:x(x),y(y)
{

}

Kolo::Kolo()
:promien(1)
{

}

bool Kolo::czyPunktJestWewnatrz(Punkt* punkt)
{
    if(sqrt(pow(punkt->x,2)+pow(punkt->y,2)) < promien)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main()
{
    int s, m, n;
    cin >> m >> n;
    MonteCarlo x;

    cout << x.losowanie(s,m,n);
    return 0;
}
