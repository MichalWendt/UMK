#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int rozmiar;
	int *tab;
	int i;
	sscanf(argv[1], "%d", &rozmiar );
	tab = malloc(rozmiar *sizeof(int) );
	printf("Podaj %d elementow tablicy" , rozmiar);
	for( i = 0; i < rozmiar; i++)
	{
		scanf("%d", &tab[i]);
	}
	for( i = 0; i < rozmiar; i++ )
	{ 
		printf("%d\n", tab[i]);
	}
	free(tab);
	return 0;
}

