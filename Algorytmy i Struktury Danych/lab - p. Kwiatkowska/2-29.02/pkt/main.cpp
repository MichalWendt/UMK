#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct punkt
{
    int x;
    int y;
};

bool cmp(punkt a, punkt b)
{
    return a.y < b.y;
}
int main()
{
    int n;
    cin>>n;
    vector<punkt> w(n);
    for(int i=0; i<n; ++i)
    {
        cin>>w[i].x;
        cin>>w[i].y;
    }

    sort(w.begin(), w.end(), cmp);
    for(int i=0; i<n; ++i)
    {
        cout<<w[i].x<<w[i].y<<endl;
    }

    return 0;
}
