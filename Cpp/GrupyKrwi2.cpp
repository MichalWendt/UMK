#include <iostream>
#include <map>
#include <vector>
using namespace std;
bool czypas(int biorca, int dawca)
{
    return (~(dawca & ~biorca) & 7) == 7;
}
int main()
{
    vector < pair < int, string> > blood;
        blood.push_back(make_pair(0,"0-"));
        blood.push_back(make_pair(1,"0+"));
        blood.push_back(make_pair(2,"B-"));
        blood.push_back(make_pair(3,"B+"));
        blood.push_back(make_pair(4,"A-"));
        blood.push_back(make_pair(5,"A+"));
        blood.push_back(make_pair(6,"AB-"));
        blood.push_back(make_pair(7,"AB+"));
    string krew;
    cin>>krew;
    int biorca=0;
    for(int i = 0; i < 7 ; ++i)
    {
        if(krew[i]=='A')
        biorca = biorca | 4;
        if(krew[i]=='B')
        biorca = biorca | 2;
        if(krew[i]=='+')
        biorca = biorca | 1;
    }
    for(int i = 7; i >= 0 ; --i)
    {
        if(czypas(biorca, blood[i].first))
            cout << blood[i].second << endl;
    }
    return 0;
}