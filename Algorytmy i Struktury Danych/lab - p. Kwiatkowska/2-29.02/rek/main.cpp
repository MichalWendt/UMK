#include <iostream>

using namespace std;

void pisz(int n)
{
    if(n>0)
    {
        pisz(n-1);
        cout<<n;

    }
}

int main()
{
    int n;
    cin>>n;
    pisz(n);
    return 0;
}
