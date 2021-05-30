#include <stdio.h>

void f1(int a, int b)
{
	int i;
	for(i = a; i <= b; i++)
	{
		if(i%2 == 0) printf("%d", i);
	}
}

int main(int argc, char **argv)
{
	int a, b;
	if(argc != 3){
		printf("Błędna liczba argumentów \n");
	}
	sscanf(argv[1], "%d", &a);
	sscanf(argv[2], "%d", &b);
	f1(a, b);
	return 0;
}

