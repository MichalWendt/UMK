#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    int A,B;
    cin >> A >> B;
    cout.width(14);
    cout << fixed << setprecision(3) << (float)A/B;
    cout << endl << "----------" << endl;
    cout.width(10);
    cout << setprecision(0);
    cout << hex << A << ":" << oct << B;
    return 0;
}
