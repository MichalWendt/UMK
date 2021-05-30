#include <iostream>

using namespace std;

int fibrek(int n)
{
    if(n==1)
    {
        return 1;
    }
    if(n==2)
    {
        return 1;
    }
    else
    {
        return fibrek(n-1)+fibrek(n-2);
    }
}

int main()
{
    int n;
    cout << "ktory wyraz ";
    cin >> n;
    cout << fibrek(n);
    return 0;
}
