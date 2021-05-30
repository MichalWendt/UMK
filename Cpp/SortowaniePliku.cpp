#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

struct para
{
    char litera;
    int ile;
};

bool sor(para a, para b)
{
    return(a.ile>b.ile);
}


int main()
{
    vector<para> tab;
    fstream plik;
    char znak;
    para pom;
    pom.litera=0;
    pom.ile=0;
    tab.push_back(pom);
    plik.open("tekst.txt",ios::in);
    while(!plik.eof())
    {
        plik >> znak;
        for(int i=0; i<tab.size();++i)
        {
            if(znak==tab[i].litera)
            {
                tab[i].ile++;
                break;
            }
            if(i==tab.size()-1 && znak!=tab[i].litera)
            {
                pom.litera=znak;
                pom.ile=1;
                tab.push_back(pom);
            }
        }
    }
    sort(tab.begin(),tab.end(),sor);

    for(int i=0; i<tab.size();++i)
    {
        cout << tab[i].litera << " ";
    }
    cout << endl;
    for(int i=0; i<tab.size();++i)
    {
        cout << tab[i].ile-1 << " ";
    }
    plik.close();
    return 0;
}
