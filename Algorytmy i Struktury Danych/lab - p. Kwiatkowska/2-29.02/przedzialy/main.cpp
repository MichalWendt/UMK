#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct przedzial
{
    int a;
    int b;
};

bool cmp(przedzial a, przedzial b)
{
    return a.a<b.a;
}

int main()
{
    int n;
    cin>>n;
    vector <przedzial>w(n);
    for(int i=0; i<n; i++)
    {
        cin>>w[i].a;
        cin>>w[i].b;
    }
    sort(w.begin(), w.end(), cmp);
   /* for(int i=0; i<n; i++)
    {
        cout<<w[i].a<<" "<<w[i].b<<endl;
    } */
    int pocz=w[0].a;
    int kon=w[0].b;
    for(int i=0; i<n; i++)
    {

        if(kon<w[i+1].a);
        else
        {
            if(kon>w[i+1].a) pocz=w[i+1].a;
            {
                if(kon<w[i+1].b) kon=w[i+1].b;
            }

        }
    cout<<pocz<<" "<<kon<<endl;
    }

    return 0;

}
