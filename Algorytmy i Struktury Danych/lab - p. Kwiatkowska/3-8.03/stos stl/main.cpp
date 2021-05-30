#include <iostream>
#include <stack>

using namespace std;

int main()
{
    int n, a;
    stack<int> k;
    cout<<"ile elementow wlozyc?"<<endl;
    cin>>n;
    for(int i=0; i<n; i++)
    {
        cin>>a;
        k.push(a);
    }
    cout<<"liczba elementow stosu "<<k.size()<<endl;
    while(!k.empty())
    {
        a=k.top();
        k.pop();
        cout<<a;
    }
    return 0;
}
