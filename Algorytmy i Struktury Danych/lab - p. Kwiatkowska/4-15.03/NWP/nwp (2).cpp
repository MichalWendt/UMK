#include <iostream>
#include <vector>
#include <string>

using namespace std;

int max(int a, int b)
{
    if(a>b) return a;
    else return b;
}

int main()
{
    string a, b;
    cout <<"Podaj slowo a"<< endl;
    cin>>a;
    cout<<"Podaj slowo b"<<endl;
    cin>>b;

    vector<vector<int> > t;

    for(int i=0; i<=a.size(); i++)
    {
    	t.push_back(vector < int >() );
        for(int j=0; j<=b.size(); j++)
    	{
        	t[i].push_back(0);
    	}	
    }
    
   for(int i=1; i<=a.size(); i++)
    {

        for(int j=1; j<=b.size(); j++)
        {
            if(a[i-1] == b[j-1])
            {
                t[i][j]=t[i-1][j-1]+1;
            }
            else
            {
                t[i][j]=max(t[i-1][j],t[i][j-1]);
            }
            
        }
    }
    int n=b.size();
    int m=a.size();
    cout<<"Najdluzszy mozliwy podciag ma dlugosc "<<t[m][n];
    return 0;
}
