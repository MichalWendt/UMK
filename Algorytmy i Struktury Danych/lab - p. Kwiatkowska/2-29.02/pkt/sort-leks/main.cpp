#include <iostream>
#include <queue>
#include <string>

using namespace std;

int main()
{
    int n;
    queue<string> a;
    queue<string> b;
    string slowo;
    int dlugosc=0;
    cout<<"Podaj liczbe slow do posortowania"<<endl;
    cin>>n;
    cout<<"Podaj "<<n<<" slow"<<endl;
    for(int i=0; i<n; i++)
    {
        cin>>slowo;
        if(dlugosc<slowo.size()) dlugosc=slowo.size();
        a.push(slowo);
    }
    while(!a.empty())
    {
        slowo=a.front();
        a.pop();
        while(slowo.size()<dlugosc) slowo=slowo+" ";
    }
    return 0;
}
