#include <iostream>
#include <string>

using namespace std;

int main()
{
    string tab;
    cin >> tab;
    int n, i = 0;
    char *wsk = &tab[0];
    cin >> n;
    while(n!=0)
    {
        i = i + n;
        if(!(i > sizeof(tab)-1 && i < 0))
        {
            wsk = wsk + n;
            cout << *wsk;
            cin >> n;
        }
        else
        {
            i = i - n;
        }
    }
    return 0;
}