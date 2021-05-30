#include <stdio.h>
#define KWADRAT(x) ((x)*(x))


int main(int argc, char **argv)
{
	int a = 3;
	int b;
	b = KWADRAT(++a);
	/*printf("%d\n", KWADRAT(2+3));*/
	printf("%d\n", b);
	
	return 0;
}

