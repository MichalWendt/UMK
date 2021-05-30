#include <iostream>
#include <cmath>

using namespace std;

class pomoc
{
  public:
  char litera;
  int il_miejsc;
  int il_konimechanicznych;
  double max_predkosc;
};

class Samochod
{
  public:
  int il_miejsc;
  int il_konimechanicznych;
  double max_predkosc;
};

class Audi : public Samochod
{

};

class Maluch : public Samochod
{

};

class Ferrari : public Samochod
{

};

class Citroen : public Samochod
{

};

int main()
{
    int n, j =0;
    cin >> n;
    pomoc tab1[n];
    Samochod sam[n];
    Audi audi[n];
    Maluch maluch[n];
    Ferrari ferr[n];
    Citroen citr[n];
    int suma_miejsc = 0, suma_koni = 0;
    double suma_pred = 0;
    int a =0, b=0, c=0, d=0;
    for(int i=0 ; i < n; ++i)
    {
        cin >> tab1[i].litera;
        cin >> tab1[i].il_miejsc;
        cin >> tab1[i].il_konimechanicznych;
        cin >> tab1[i].max_predkosc;
    }
    for(int i=0 ; i < n; ++i)
    {
        if(tab1[i].litera == 'A')
        {
            audi[a].il_miejsc = tab1[i].il_miejsc;
            audi[a].il_konimechanicznych = tab1[i].il_konimechanicznych;
            audi[a].max_predkosc = tab1[i].max_predkosc;
            sam[j] = audi[a];
            j++;
            a++;
        }
        if(tab1[i].litera == 'M')
        {
            maluch[b].il_miejsc = tab1[i].il_miejsc;
            maluch[b].il_konimechanicznych = tab1[i].il_konimechanicznych;
            maluch[b].max_predkosc = tab1[i].max_predkosc;
            sam[j] = maluch[b];
            j++;
            b++;
        }
        if(tab1[i].litera == 'F')
        {
            ferr[c].il_miejsc = tab1[i].il_miejsc;
            ferr[c].il_konimechanicznych = tab1[i].il_konimechanicznych;
            ferr[c].max_predkosc = tab1[i].max_predkosc;
            sam[j] = ferr[c];
            j++;
            c++;
        }
        if(tab1[i].litera == 'C')
        {
            citr[d].il_miejsc = tab1[i].il_miejsc;
            citr[d].il_konimechanicznych = tab1[i].il_konimechanicznych;
            citr[d].max_predkosc = tab1[i].max_predkosc;
            sam[j] = citr[d];
            j++;
            d++;
        }
    }
    for(int i=0 ; i < n; ++i)
    {
        suma_miejsc = suma_miejsc + sam[i].il_miejsc;
        suma_koni = suma_koni + sam[i].il_konimechanicznych;
        suma_pred = suma_pred + sam[i].max_predkosc;
    }

    cout << suma_miejsc << endl;
    cout << suma_koni << endl;
    suma_pred = suma_pred / n;
    cout.setf( ios::showpoint );
    cout.setf(ios::fixed);
    cout.precision(1);
    cout << suma_pred <<endl;

    return 0;
}
