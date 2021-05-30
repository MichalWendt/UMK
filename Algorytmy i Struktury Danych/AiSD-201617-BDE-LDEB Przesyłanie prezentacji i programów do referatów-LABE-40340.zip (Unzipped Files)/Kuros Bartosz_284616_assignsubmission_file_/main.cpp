#include <iostream>
#include <fstream>
#include <queue>

using namespace std;
// Algorytm znajdujacy wyjscie z zadanego labiryntu pobranego z pliku
int main()
{
    int x, y;
    int wymlabx, wymlaby;

    cout << "Podaj wymiary labiryntu (x,y):";
    cin >> wymlabx >> wymlaby;

    queue <int> kolejka;
    char lab[wymlabx][wymlaby];

    fstream plik;
    plik.open("labirynt.txt");

    string linia;
    int liczniklinii = 0;
    int startx, starty;
    int wyjsciex, wyjsciey;

    while(plik >> linia)
    {
        for(int i=0;i<linia.length();i++)
        {
            lab[i][liczniklinii] = linia[i];
        }
        liczniklinii++;
    }
    plik.close();

    for(int j=0;j<wymlaby;j++) //wydrukowanie kontrolne z oznaczeniem startu i wyjscia
    {
        for(int i=0;i<wymlabx;i++)
        {
            if(lab[i][j] == 83) //znajdowanie i zapamietywanie Startu
            {
                startx = i;
                starty = j;
            }
            if(lab[i][j] == 87) //znajdowanie i zapamietywanie Wyjscia
            {
                wyjsciex = i;
                wyjsciey = j;
                lab[i][j] = '.';
            }
            cout << lab[i][j] << " ";
        }
        cout << endl;
    }

    kolejka.push(startx); //na poczatek wkladamy do kolejki wspolrzedne startu
    kolejka.push(starty);

    while(x!=wyjsciex || y!=wyjsciey)
    {
        x = kolejka.front();
        kolejka.pop();
        y = kolejka.front();
        kolejka.pop();

        //w prawo
        if(lab[x+1][y] == '.')
        {
            kolejka.push(x+1);
            kolejka.push(y);
            lab[x+1][y] = 'l';
        }
        //w lewo
        if(lab[x-1][y] == '.')
        {
            kolejka.push(x-1);
            kolejka.push(y);
            lab[x-1][y] = 'p';
        }
        //w gore
        if(lab[x][y+1] == '.')
        {
            kolejka.push(x);
            kolejka.push(y+1);
            lab[x][y+1] = 'g';
        }
        //w dol
        if(lab[x][y-1] == '.')
        {
            kolejka.push(x);
            kolejka.push(y-1);
            lab[x][y-1] = 'd';
        }

    }

    while(x!=startx || y!=starty) //rysujemy droge wyjscia tym razem idac od konca
    {
        if(lab[x][y] == 'g')
        {
            lab[x][y] = ' ';
            y--;
        }
        if(lab[x][y] == 'd')
        {
            lab[x][y] = ' ';
            y++;
        }
        if(lab[x][y] == 'l')
        {
            lab[x][y] = ' ';
            x--;
        }
        if(lab[x][y] == 'p')
        {
            lab[x][y] = ' ';
            x++;
        }
    }

    cout << endl;
    for(int j=0;j<wymlaby;j++)
    {
        for(int i=0;i<wymlabx;i++)
        {
            cout << lab[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
