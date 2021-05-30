#include <stdio.h>
#include <stdlib.h>

void wyswietl(int *tablica, int n) {
	int i;
	
	for(i = 0; i < n; i++) {
		printf("%d ", *tablica++);
	}
	printf("\n");
}

int main(int argc, char **argv)
{
	int n, i;
	int *table, *p;
	
	
	/* pobieram rozmiar tablicy i alokuje na niego miejsce */
	
	sscanf(argv[1], "%d", &n);
	table = malloc(sizeof(int) * n);
	
	/* zapamietuje miejsce poczatku tablicy */
	
	p = table;
	
	/* wypelnienie tablicy*/
	
	for(i = 0; i < n; i++) {
		*table = i;
		table++;
	}
	
	/* wskaznik na poczatek tablicy */
	
	table = p;
	
	wyswietl(table, n);
	
	/* mnozenie */
	
	for(i = 0; i < n; i++) {
		if(*table % 2 == 0)
			*table++ *= 3;
		else
			table++;
			
	}
	
	table = p;
	
	wyswietl(table, n);

	return 0;
}

