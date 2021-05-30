#include <iostream>

using namespace std;

class Pracownik
{
    public:
    int id;
    string imie;
    string nazwisko;
    int wynagrodzenie;
    int id_przelozonego;
};

class przelozony : public Pracownik
{
};

int main()
{
    int n, j=0;
    cin >> n;
    int suma[n];
    Pracownik lista[n];
    przelozony przel[n];
    for(int i=0; i<n;++i)
    {
        cin >> lista[i].id;
        cin >> lista[i].imie;
        cin >> lista[i].nazwisko;
        cin >> lista[i].wynagrodzenie;
        cin >> lista[i].id_przelozonego;
        suma[i] = 0;
    }
    for(int i=0; i<n;++i)
    {
        for(int k=0; k<n;++k)
        {
            if(lista[i].id == lista[k].id_przelozonego)
            {
                przel[j].id = lista[i].id;
                przel[j].imie = lista[i].imie;
                przel[j].nazwisko = lista[i].nazwisko;
                przel[j].wynagrodzenie = lista[i].wynagrodzenie;
                przel[j].id_przelozonego = lista[i].id_przelozonego;
                j++;
                break;
            }
        }
    }
    for(int k=0; k<j;++k)
    {
            for(int i=0; i<n;++i)
            {
                if(przel[k].id == lista[i].id_przelozonego && przel[k].id != lista[i].id)
                {
                    suma[k] = suma[k] + lista[i].wynagrodzenie;
                }
            }
    }
    for(int k=0; k<j;++k)
    {
        if(suma[k] < 20000)
        {
            cout << przel[k].id << " ";
            cout << przel[k].imie << " ";
            cout << przel[k].nazwisko << " ";
            cout << przel[k].wynagrodzenie / 5;
        }
        cout << endl;
    }
    return 0;
}
