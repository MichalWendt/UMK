#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int n, i, argument;
    int min = argv[1];
    int max = argv[1];
    for( i = 1; i <= argc; i++)
    {
		sscanf(argv[i], "%d", &argument);
		if(argument < min) min = argument;
		if(argument > max) max = argument;
	}
	printf("Wartosc minimalna to %d", min);
	printf("Wartosc maksymalna ta %d", max);

    return 0;
}
