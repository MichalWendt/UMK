#include <stdio.h>
#include <stdlib.h>
#define MAX(X, Y) ((X <= Y)? (Y): (X))
#define MAX3(X, Y, Z) ((X <= Y )? ((Y <= Z)? (Z): (Y)): (X <= Z)? (Z): (X))
#define SGN(X) ((X < 0)? (-1): (X > 0)? (1): 0)

int main(int argc, const char * argv[]) {
    int a, b, c;
    printf("Podaj 3 liczby: ");
    scanf("%d %d %d", &a, &b, &c);

    printf("MAX: %d\n", MAX(a,b));
    printf("MAX3: %d\n", MAX3(a, b, c));
    printf("SGN: %d\n", SGN(a));
    return 0;
}
