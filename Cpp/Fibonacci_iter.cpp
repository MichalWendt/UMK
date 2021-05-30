#include <iostream>
using namespace std;
int main()
{
    int a = 0, b = 1;
    int n;
    cin >> n;
    for (int i=0; i<n; ++i)
    {
        b=b+a;
        a=b-a;
    }
    cout << a;
    return 0;
}