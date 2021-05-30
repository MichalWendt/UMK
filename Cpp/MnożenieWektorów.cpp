#include <iostream>

using namespace std;

int main()
{
    double *A,*B,*C;
    A=new double[20];
    B=new double[20];
    C=new double[20];
    for (int i=0; i<20; ++i)
    {
        cin >> A[i];
    }
    for (int i=0; i<20; ++i)
    {
        cin >> B[i];
    }
    for (int i=0; i<20; ++i)
    {
            C[i]=A[i]*B[i];
    }
    for (int i=0; i<20; ++i)
    {
        cout << C[i] << " ";
    }
    return 0;
}
