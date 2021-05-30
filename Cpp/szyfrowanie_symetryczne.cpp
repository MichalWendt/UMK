#include <iostream>

using namespace std;

int main()
{
    string tekst;
    cin>>tekst;

    char w1 ,w2, w3, w4;
    w1=w2=w3=w4=0;
    for(int i=0; i<tekst.length() ; i++){
    w1= tekst[i] & 1;
    w2= tekst[i] & 1<<1;
    w3= tekst[i] & 1<<2;
    w4= tekst[i] & 1<<3;
    tekst[i] = tekst[i] & ~15;
    tekst[i] = tekst[i] | w1<<1;
    tekst[i] = tekst[i] | w2>>1;
    tekst[i] = tekst[i] | w3<<1;
    tekst[i] = tekst[i] | w4>>1;
    }
    cout<<tekst<<endl;
    return 0;
}
