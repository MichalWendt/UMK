#include <stdio.h>

#define AVG(X) ((X > 0)? (1) : (X < 0)? (-1) : (0))
#define MIN(X, Y) ((X > Y)? (Y) : (X))

int main(int argc, char **argv)
{
	int a = 3;
	int b = -8;
	int c = 0;
	printf("AVG %d\n", AVG(a));
	printf("AVG %d\n", AVG(b));
	printf("AVG %d\n", AVG(c));
	printf("MIN %d\n", MIN(a, c));
	return 0;
}

