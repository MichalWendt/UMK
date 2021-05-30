#include <iostream>
#include <queue>

using namespace std;

int main()
{
    int n, a;
    queue<int> k;
    cout <<"ile elementow dodac do kolejki?"<< endl;
    cin>>n;
    for(int i=0; i<n; i++)
    {
        cin>>a;
        k.push(a);
    }
    for(int i=n; i>0; i--)
    {
        a=k.front();
        k.pop();
        cout<<a;
    }

    return 0;
}
