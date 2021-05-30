#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	FILE *macierz;
	int rozmiar=0, i, j, tmp, suma;
	int **tab;
	
	macierz = fopen("macierz.txt", "r");
	if(macierz){
	fscanf(macierz, "%d", &rozmiar);
	
	tab = malloc(sizeof(int)*rozmiar);
	for(i=0; i<rozmiar; i++){
		tab[i] =  malloc(sizeof(int)*rozmiar);
		for(j = 0; j < rozmiar; j++){
			fscanf(macierz, "%d", &tmp);
			tab[i][j] = tmp;
		}
	}
	suma = 0;
	for(i = 0; i < rozmiar; i++){
		suma += tab[i][i];
	}
}
	printf("Macierz\n");
	for(i=0; i<rozmiar; i++){
		for(j=0; j<rozmiar; j++){
			printf("%d", tab[i][j]);
			free(tab[i]);
			printf("\n");
		}
	}
	free(macierz);
	printf("Slad macierzy %d\n", suma);
	fclose(macierz);
	return 0;
}

