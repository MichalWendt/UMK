#include <stdio.h>
#define SGN(X) ((X < 0)? (-1): (1))
#define MIN(X, Y) ((X <= Y)? (X): (Y))
#define MAX(X, Y) ((X <= Y)? (Y): (X))
#define AVG(X, Y, Z) ((X + Y + Z)/3)
#define ABS(X) ((X > 0)? (X): (-(X)))


int main(int argc, char **argv)
{
	int a, b, c;
	printf("Podaj 3 liczbY");
	scanf("%d %d %d", &a, &b, &c);
	/*do SGN*/
	if(a == 0) printf("SGN %d", a);
	else{
		printf("SGN %d\n", SGN(a));
	}
	/*do MIN*/
	printf("MIN %d\n", MIN(a, b));
	/*do MAX*/
	printf("MAX %d\n", MAX(a, b));
	/*do AVG*/
	printf("AVG %d\n", AVG(a, b, c));
	/*do ABS*/
	printf("ABS %d\n", ABS(a));
	return 0;
}

