#include <iostream>
#include <cmath>

using namespace std;

struct punkt
{
    int x;
    int y;
};

int main()
{
    int N;
    cin >> N;
    punkt tab[N+1];
    for(int i=0; i<=N; i++)
    {
        cin >> tab[i].x >> tab[i].y;
    }
    for(int i=0; i<=N; i++)
    {
        for(int j=1; j<=N; j++)
        {
            if((sqrt((pow(tab[j].x-tab[0].x,2))+(pow(tab[j].y-tab[0].y,2)))) > (sqrt((pow(tab[j+1].x-tab[0].x,2))+(pow(tab[j+1].y-tab[0].y,2)))))
            {
                swap(tab[j].x, tab[j+1].x);
                swap(tab[j].y, tab[j+1].y);
            }
            else if((sqrt((pow(tab[j].x-tab[0].x,2))+(pow(tab[j].y-tab[0].y,2)))) == (sqrt((pow(tab[j+1].x-tab[0].x,2))+(pow(tab[j+1].y-tab[0].y,2)))))
            {
                if(tab[j].x > tab[j+1].x)
                {
                    swap(tab[j].x, tab[j+1].x);
                    swap(tab[j].y, tab[j+1].y);
                }
                else if(tab[j].x == tab[j+1].x && tab[j].y > tab[j+1].y)
                {
                        swap(tab[j].x, tab[j+1].x);
                        swap(tab[j].y, tab[j+1].y);
                }
            }
        }
    }
    for(int i=1; i<=N; i++)
    {
            cout << tab[i].x << " " << tab[i].y << endl;
    }
    return 0;
}
